//
// Created by 吴子庶 on 2021/10/6.
//

#include "bucket_leap_array.h"

namespace Envoy {
    namespace Http {

        BucketLeapArray::~BucketLeapArray() {}

        MetricBucket *BucketLeapArray::newEmptyBucket(long time) {
            printf("time: %ld", time);
            MetricBucket metricBucket = MetricBucket();
            return &metricBucket;
        }

        WindowWrap<MetricBucket> &BucketLeapArray::resetWindowTo(WindowWrap<MetricBucket> &w,
                                                                 long startTime) {
            w = w.resetTo(startTime);
            w.value().reset();
            return w;
        }
    } // namespace Http

} // namespace Envoy