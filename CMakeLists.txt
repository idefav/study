cmake_minimum_required(VERSION 3.17)
project(study)
find_package(benchmark REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(study main.cpp metric.h metric_event.h metric_bucket.cc metric_bucket.h stastic_node.h stastic_node.cc node.h Shape.h Shape.cpp window_wrap.h leap_array.h bucket_leap_array.h bucket_leap_array.cc Box.h Box.cpp array_metric.h array_metric.cc)

target_link_libraries(study benchmark::benchmark)