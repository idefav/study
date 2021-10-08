//
// Created by 吴子庶 on 2021/9/25.
//
#pragma once

#include <iostream>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <type_traits>

#include "Box.h"
#include "concurrency/helloworld.h"


#include "stastic_node.h"

#define MAKE_STR(x) #x
#define MAKE_STR2(x, y) x##y

using namespace shape;
using namespace std;


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


int main() {

    Envoy::Http::StasticNode node = Envoy::Http::StasticNode();

    node.addPassRequest(1);
    node.addPassRequest(1);
//
//    node.addPassRequest(100);
//
    cout << "PassQPS:" << node.passQps() << endl;

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