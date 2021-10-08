//
// Created by 吴子庶 on 2021/10/6.
//

#pragma once

#include <string>
#include <sstream>

using std::ostringstream;
using std::string;

namespace Envoy {
    namespace Http {
        template<typename T>
        class WindowWrap {
        private:
            /* data */
            long windowLengthInMs_;
            long windowStart_;
            T value_;

        public:
            WindowWrap() = default;

            WindowWrap(long windowLengthInMs, long windowStart, T value)
                    : windowLengthInMs_(windowLengthInMs), windowStart_(windowStart), value_(value) {};

            WindowWrap(long windowLengthInMs, long windowStart)
                    : windowLengthInMs_(windowLengthInMs), windowStart_(windowStart) {};

            WindowWrap(const WindowWrap<T> &win) : windowLengthInMs_(win.windowLengthInMs_),
                                                   windowStart_(win.windowStart_), value_(win.value_) {}

            WindowWrap<T> &operator=(const WindowWrap<T> &o);
//            ~WindowWrap();

            long windowLength();

            long windowStart();

            T &value();

            void setValue(T v);

            WindowWrap<T> &resetTo(long startTime);

            bool isTimeInWindow(long timeMillis);

            string toString();
        };

//        template <typename T> WindowWrap<T>::~WindowWrap() {}

        template<typename T>
        long WindowWrap<T>::windowLength() { return windowLengthInMs_; }

        template<typename T>
        long WindowWrap<T>::windowStart() { return windowStart_; }

        template<typename T>
        T &WindowWrap<T>::value() { return value_; }

        template<typename T>
        void WindowWrap<T>::setValue(T v) { value_ = v; }

        template<typename T>
        WindowWrap<T> &WindowWrap<T>::resetTo(long startTime) {
            windowStart_ = startTime;
            return *this;
        }

        template<typename T>
        bool WindowWrap<T>::isTimeInWindow(long timeMillis) {
            return windowStart_ <= timeMillis && timeMillis < windowStart_ + windowLengthInMs_;
        }

        template<typename T>
        string WindowWrap<T>::toString() {
            ostringstream result;
            result << "WindowWrap{"
                   << "windowLengthInMs=" << windowLengthInMs_ << ", windowStart=" << windowStart_
                   << ", value=" << value_ << "}";
            return result.str();
        }

        template<typename T>
        WindowWrap<T> &WindowWrap<T>::operator=(const WindowWrap<T> &o) {
            windowLengthInMs_ = o.windowLengthInMs_;
            windowStart_ = o.windowStart_;
            value_ = o.value_;
            return *this;
        }

    } // namespace Http
} // namespace Envoy

