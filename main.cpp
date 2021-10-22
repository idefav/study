//
// Created by 吴子庶 on 2021/9/25.
//
#pragma once

#include <iostream>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <type_traits>
#include <random>
#include <time.h>
#include <atomic>

#include "Box.h"
#include "concurrency/helloworld.h"

//#include "benchmark/benchmark.h"


#include "stastic_node.h"

#define MAKE_STR(x) #x
#define MAKE_STR2(x, y) x##y

using namespace shape;
using namespace std;
using namespace Envoy::Http;


void sigHanler(int sig) {
    cout << "捕获到信号" << endl;
    exit(sig);
}

void hello() {
    cout << "hello!" << endl;
}

class A {
private:
    int a;
public:
    A() : a(0) {}
};

template<typename T>
class B {
private:
    const long windowLengthInMs_;
    long windowStart_;
    T value_;
public:
    B(const long windowLengthInMs, long windowStart) : windowLengthInMs_(windowLengthInMs), windowStart_(windowStart) {}

    B(const long windowLengthInMs, long windowStart, T value) : windowLengthInMs_(windowLengthInMs),
                                                                windowStart_(windowStart), value_(value) {}
};

class C {
private:
    atomic_long pass_request_counter;
    atomic_long block_request_counter;
    atomic_long ex_request_counter;
    atomic_long success_request_counter;
    atomic_long rt_counter;
    atomic_long min_rt;
public:
    C();


    void init();
};

C::C() {
    init();
}

void C::init() {
    atomic_init(&pass_request_counter, 0L);
    atomic_init(&block_request_counter, 0L);
    atomic_init(&ex_request_counter, 0L);
    atomic_init(&success_request_counter, 0L);
    atomic_init(&rt_counter, 0L);
    atomic_init(&min_rt, 0L);
}

void test() {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr(100, 1000);

    Envoy::Http::StasticNode node = Envoy::Http::StasticNode();
    node.addPassRequest(1);
    node.increaseExceptionQps(1);
    node.addRtAndSuccess(100 + distr(eng), 1);
    node.increaseThreadNum();
}

//static void BM_test(benchmark::State &state) {
//    for (auto _:state) {
//        test();
//    }
//}

//BENCHMARK(BM_test);

//BENCHMARK_MAIN();

static void testAtomicInt() {
    std::shared_ptr<atomic<int>> ptr = std::make_shared<atomic<int>>(0);

    for (auto i = 0; i < 20; i++) {
        std::thread([&ptr] {
            for (int j = 0; j < 1000; ++j) {
                ptr->fetch_add(1);
//                std::atomic_store(&ptr, std::make_shared<atomic<int>>(*ptr + 1));
            }
//            ptr = make_shared<int>(*ptr + 1);
        }).join();
    }
    cout << "ptr:" << *ptr << endl;
    cout << "ptr is lock free:" << atomic_is_lock_free(ptr.get()) << endl;
}

//void testAtomicClass() {
//
//    atomic<WindowWrap<MetricBucket>> tt = atomic<WindowWrap<MetricBucket>>();
//    shared_ptr<atomic<WindowWrap<MetricBucket>>> ptr = make_shared<atomic<WindowWrap<MetricBucket>>>()
//}

int main() {
    clock_t startTime, endTime;
    startTime = clock();
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr(100, 1000);

    Envoy::Http::StasticNode node = Envoy::Http::StasticNode();

//    node.addPassRequest(1);
//    node.addPassRequest(1);
//
//    node.addPassRequest(100);
//
//    node.addRtAndSuccess(1000, 1);
//    node.increaseThreadNum();
//
//    node.increaseBlockQps(1);
//    node.increaseExceptionQps(1);

    vector<thread> workers;
    workers.reserve(10);
    for (int i = 0; i < 1; ++i) {
        workers.emplace_back([&]() {
            for (int j = 0; j < 100000000; ++j) {
                node.addPassRequest(1);
                node.increaseExceptionQps(1);
                node.addRtAndSuccess(100L + distr(eng), 1);
                node.increaseThreadNum();
                cout << "PassQps:" << node.passQps() << endl;
//                sleep(1);
                this_thread::yield();
//                cout << "ThreadId:" << this_thread::get_id() << endl;
            }
        });
    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t) {
        t.join();
    });


    cout << "mainThreadId:" << this_thread::get_id() << endl;

    cout << "PassQPS:" << long(node.passQps()) << endl;
    cout << "minRT:" << node.minRt() << endl;
    cout << "avgRT:" << node.avgRt() << endl;
    cout << "threadNum:" << node.curThreadNum() << endl;
    cout << "exQPS:" << long(node.exceptionQps()) << endl;

    testAtomicInt();

    endTime = clock();
    cout << "Totle Time : " << (double) (endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
//    concurrency::HelloWorld *helloWorld = new concurrency::HelloWorld();
//    helloWorld->run();
//    std::thread t([] {
//        cout << "-->" << endl;
//    });
//    t.join();
//    static_assert(std::is_trivially_copyable<A>::value, "");
//    cout << "string:" << std::is_trivially_copyable<std::string>::value << endl;
//    cout << "A:" << std::is_trivially_copyable<A>::value << endl;
//    cout << "C:" << std::is_trivially_copyable<C>::value << endl;
//    cout << "B<C>:" << std::is_trivially_copyable<B<C>>::value << endl;
//    cout << "MetricBucket:" << std::is_trivially_copyable<Envoy::Http::MetricBucket>::value << endl;
//    cout << "B<C>:" << std::is_trivially_copyable<Envoy::Http::WindowWrap<Envoy::Http::MetricBucket>>::value << endl;
////    cout << "NULL:" << std::is_trivially_copyable<__null>::value << endl;
}



/*int main() {
    Box *box = new Box(1, 2, 3);
    print(*box);
    cout << "Box:" << box->getVolume() << endl;
    cout << MAKE_STR(make str) << endl;
    int xy = 100;
    cout << MAKE_STR2(x, y) << endl;
    signal(SIGINT | SIGTERM, sigHanler);
    for (;;) {
        cout << "Sleep" << endl;
        sleep(1);
    }
//    delete box;
return 0;
}
 */