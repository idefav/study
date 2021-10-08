//
// Created by 吴子庶 on 2021/9/25.
//

#include <thread>
#include <iostream>
#include <type_traits>
#include "helloworld.h"

using namespace std;
using namespace concurrency;



void HelloWorld::run() {
//    std::thread t(this->hello());
//    t.join();
}


void HelloWorld::hello() {
    cout << "Hello Concurrency!" << endl;

}
