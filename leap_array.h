//
// Created by 吴子庶 on 2021/10/6.
//

#pragma once

#include <vector>
#include <array>
#include <thread>

#include <atomic>
#include <mutex>
#include <chrono>

#include "window_wrap.h"

using namespace std;
using namespace chrono;
using std::atomic;
using std::mutex;
using std::string;

namespace Envoy {
    namespace Http {

//        template<typename T>
//        struct WindowWrapAtomic {
//            std::atomic<T> atomic;
//
//            WindowWrapAtomic() : atomic(T()) {}
//
//            WindowWrapAtomic(T &v) : atomic(v) {}
//
//            explicit WindowWrapAtomic(T const &v) : atomic(v) {}
//
//            explicit WindowWrapAtomic(std::atomic<T> const &a) : atomic(a.load()) {}
//
//            WindowWrapAtomic(WindowWrapAtomic const &other) : atomic(other.atomic.load()) {}
//
//            WindowWrapAtomic &operator=(WindowWrapAtomic const &other) {
//                atomic.store(other.atomic.load());
//                return *this;
//            }
//
//            T get() { return atomic.load(); }
//
//            bool compare_exchange_weak(T oldV, T newV) {
//                return atomic.compare_exchange_weak(oldV, newV, memory_order_relaxed);
//            }
//        };

        template<typename T>
        class LeapArray {
        private:
            mutex updateLock_;

            /* data */
            int calculateTimeIdx(long timeMillis);

        protected:
            int windowLengthInMs_;
            int sampleCount_;
            int intervalInMs_;
            double intervalInSecond_;

            vector<WindowWrap<T>> *array_;

            long calculateWindowStart(long timeMillis);

            virtual WindowWrap<T> &resetWindowTo(WindowWrap<T> &windowWrap, long startTime) = 0;

        public:
            LeapArray(int sampleCount, int intervalInMs);

            virtual ~LeapArray() { delete array_; };

            WindowWrap<T> *currentWindow();

            WindowWrap<T> *currentWindow(long timeMillis);

            virtual T *newEmptyBucket(long timeMillis) = 0;

            WindowWrap<T> *getPreviousWindow(long timeMillis);

            WindowWrap<T> *getPreviousWindow();

            T *getWindowValue(long timeMillis);

            bool isWindowDeprecated(WindowWrap<T> &windowWrap);

            bool isWindowDeprecated(long time, WindowWrap<T> &windowWrap);

            vector<WindowWrap<T>> *list();

            vector<WindowWrap<T>> *list(long validTime);

            vector<WindowWrap<T>> *listAll();

            vector<T> *values();

            vector<T> *values(long timeMillis);

            WindowWrap<T> *getValidHead(long timeMillis);

            WindowWrap<T> *getValidHead();

            int getSampleCount();

            int getIntervalInMs();

            double getIntervalInSecond();
        };


        template<typename T>
        LeapArray<T>::LeapArray(int sampleCount, int intervalInMs) {
//            if (sampleCount <= 0)
//                throw string("bucket count is invalid:") + std::to_string(sampleCount);
//            if (intervalInMs <= 0)
//                throw string("total time interval of the sliding window should be positive");
//            if (intervalInMs % sampleCount == 0)
//                throw string("time span needs to be evenly divided");

            windowLengthInMs_ = intervalInMs / sampleCount;
            intervalInMs_ = intervalInMs;
            intervalInSecond_ = intervalInMs / 1000;
            sampleCount_ = sampleCount;
            array_ = new vector<WindowWrap<T>>();
            for (int i = 0; i < sampleCount_; i++) {
                WindowWrap<T> win = WindowWrap<T>(windowLengthInMs_, 0L, T());
//
                array_->push_back(win);
//                test_->push_back(i);
            }
        }

//        template<typename T>
//        LeapArray<T>::~LeapArray() {}

        template<typename T>
        int LeapArray<T>::calculateTimeIdx(long timeMillis) {
            long timeId = timeMillis / windowLengthInMs_;
            // Calculate current index so we can map the timestamp to the leap array.
            return timeId % sampleCount_;
        }

        template<typename T>
        long LeapArray<T>::calculateWindowStart(long timeMillis) {
            return timeMillis - timeMillis % windowLengthInMs_;
        }

        template<typename T>
        WindowWrap<T> *LeapArray<T>::currentWindow() {
            auto ts = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            return currentWindow(ts);
        }

        template<typename T>
        WindowWrap<T> *LeapArray<T>::currentWindow(long timeMillis) {

            if (timeMillis < 0) {
                return NULL;
            }

            int idx = calculateTimeIdx(timeMillis);
            // Calculate current bucket start time.
            long windowStart = calculateWindowStart(timeMillis);

            /*
             * Get bucket item at given time from the array.
             *
             * (1) Bucket is absent, then just create a new bucket and CAS update to circular array.
             * (2) Bucket is up-to-date, then just return the bucket.
             * (3) Bucket is deprecated, then reset current bucket and clean all deprecated buckets.
             */
            while (true) {
                WindowWrap<T> old = array_->at(idx);
//                if (&old == NULL) {
//                    WindowWrap<T> window =
//                            WindowWrap<T>(windowLengthInMs_, windowStart, *newEmptyBucket(timeMillis));
//                    array_->push_back(WindowWrap<T>(window));
//                    return &window;
//                }
                if (&old == NULL) {
                    /*
                     *     B0       B1      B2    NULL      B4
                     * ||_______|_______|_______|_______|_______||___
                     * 200     400     600     800     1000    1200  timestamp
                     *                             ^
                     *                          time=888
                     *            bucket is empty, so create new and update
                     *
                     * If the old bucket is absent, then we create a new bucket at {@code windowStart},
                     * then try to update circular array via a CAS operation. Only one thread can
                     * succeed to update, while other threads yield its time slice.
                     */
                    WindowWrap<T> window =
                            WindowWrap<T>(windowLengthInMs_, windowStart, *newEmptyBucket(timeMillis));
                    array_->at(idx) = window;
                    return &window;
//                    if (old.compare_exchange_weak(old, window)) {
//                        return window;
//                    } else {
//                        std::this_thread::yield();
//                    }
                } else if (windowStart == old.windowStart()) {
                    /*
                     *     B0       B1      B2     B3      B4
                     * ||_______|_______|_______|_______|_______||___
                     * 200     400     600     800     1000    1200  timestamp
                     *                             ^
                     *                          time=888
                     *            startTime of Bucket 3: 800, so it's up-to-date
                     *
                     * If current {@code windowStart} is equal to the start timestamp of old bucket,
                     * that means the time is within the bucket, so directly return the bucket.
                     */
                    return &old;
                } else if (windowStart > old.windowStart()) {
                    /*
                     *   (old)
                     *             B0       B1      B2    NULL      B4
                     * |_______||_______|_______|_______|_______|_______||___
                     * ...    1200     1400    1600    1800    2000    2200  timestamp
                     *                              ^
                     *                           time=1676
                     *          startTime of Bucket 2: 400, deprecated, should be reset
                     *
                     * If the start timestamp of old bucket is behind provided time, that means
                     * the bucket is deprecated. We have to reset the bucket to current {@code windowStart}.
                     * Note that the reset and clean-up operations are hard to be atomic,
                     * so we need a update lock to guarantee the correctness of bucket update.
                     *
                     * The update lock is conditional (tiny scope) and will take effect only when
                     * bucket is deprecated, so in most cases it won't lead to performance loss.
                     */
                    lock_guard<mutex> lock(updateLock_);
                    WindowWrap<T> wrap = resetWindowTo(old, windowStart);
                    return &wrap;
                } else if (windowStart < old.windowStart()) {
                    // Should not go through here, as the provided time is already behind.
                    WindowWrap<T> wrap = WindowWrap<T>(windowLengthInMs_, windowStart,
                                                       *newEmptyBucket(timeMillis));
                    return &wrap;
                }
            }
        }

        template<typename T>
        WindowWrap<T> *LeapArray<T>::getPreviousWindow(long timeMillis) {
            if (timeMillis < 0) {
                return NULL;
            }
            int idx = calculateTimeIdx(timeMillis - windowLengthInMs_);
            timeMillis = timeMillis - windowLengthInMs_;
            WindowWrap<T> wrap = array_->at(idx);

            if (&wrap == NULL || isWindowDeprecated(wrap)) {
                return NULL;
            }

            if (wrap.windowStart() + windowLengthInMs_ < (timeMillis)) {
                return NULL;
            }

            return &wrap;
        }

        template<typename T>
        WindowWrap<T> *LeapArray<T>::getPreviousWindow() {
            auto ts = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            return getPreviousWindow(ts);
        }

        template<typename T>
        T *LeapArray<T>::getWindowValue(long timeMillis) {
            if (timeMillis < 0) {
                return NULL;
            }
            int idx = calculateTimeIdx(timeMillis);

            WindowWrap<T> bucket = array_->at(idx);

            if (&bucket == NULL || !bucket.isTimeInWindow(timeMillis)) {
                return NULL;
            }

            return &bucket.value();
        }

        template<typename T>
        bool LeapArray<T>::isWindowDeprecated(WindowWrap<T> &windowWrap) {
            auto ts = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            return isWindowDeprecated(ts, windowWrap);
        }

        template<typename T>
        bool LeapArray<T>::isWindowDeprecated(long time, WindowWrap<T> &windowWrap) {
            return time - windowWrap.windowStart() > intervalInMs_;
        }

        template<typename T>
        vector<WindowWrap<T>> *

        LeapArray<T>::list(long validTime) {
            int size = array_->size();
            vector<WindowWrap<T>>
                    result(size);

            for (int i = 0; i < size; i++) {
                WindowWrap<T> windowWrap = array_->get(i).get();
                if (windowWrap == NULL || isWindowDeprecated(validTime, windowWrap)) {
                    continue;
                }
                result.add(windowWrap);
            }

            return result;
        }

        template<typename T>
        vector<WindowWrap<T>> *

        LeapArray<T>::list() {
            auto ts = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            return list(ts);
        }

        template<typename T>
        vector<WindowWrap<T>> *

        LeapArray<T>::listAll() {
            int size = array_->size();
            vector<WindowWrap<T>>
                    result(size);

            for (int i = 0; i < size; i++) {
                WindowWrap<T> windowWrap = array_->get(i);
                if (windowWrap == NULL) {
                    continue;
                }
                result.add(windowWrap);
            }

            return result;
        }

        template<typename T>
        vector<T> *LeapArray<T>::values(long timeMillis) {
            if (timeMillis < 0) {
                return NULL;
            }
            int size = array_->size();
            vector<T> result = vector<T>(size);

            for (int i = 0; i < size; i++) {
                WindowWrap<T> windowWrap = array_->at(i);
                if (&windowWrap == NULL || isWindowDeprecated(timeMillis, windowWrap)) {
                    continue;
                }
                result.push_back(windowWrap.value());
            }
            return &result;
        }

        template<typename T>
        vector<T> *LeapArray<T>::values() {
            auto ts = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            return values(ts);
        }

        template<typename T>
        WindowWrap<T> *LeapArray<T>::getValidHead(long timeMillis) {
            // Calculate index for expected head time.
            int idx = calculateTimeIdx(timeMillis + windowLengthInMs_);

            WindowWrap<T> wrap = array_->get(idx).get();
            if (wrap == NULL || isWindowDeprecated(wrap)) {
                return NULL;
            }

            return wrap;
        }

        template<typename T>
        WindowWrap<T> *LeapArray<T>::getValidHead() {
            auto ts = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            return getValidHead(ts);
        }

        template<typename T>
        int LeapArray<T>::getSampleCount() { return sampleCount_; }

        template<typename T>
        int LeapArray<T>::getIntervalInMs() { return intervalInMs_; }

        template<typename T>
        double LeapArray<T>::getIntervalInSecond() { return intervalInSecond_; }

    } // namespace Http
} // namespace Envoy
