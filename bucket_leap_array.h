//
// Created by 吴子庶 on 2021/10/6.
//

#pragma once


#include "leap_array.h"
#include "metric_bucket.h"

using namespace std;

namespace Envoy {
    namespace Http {

        static MetricBucket emptyMetricBucket;

        class BucketLeapArray : public LeapArray<MetricBucket> {
        private:
            /* data */
        public:
            BucketLeapArray(int sampleCount, int intervalInMs) : LeapArray(sampleCount, intervalInMs) {};

            ~BucketLeapArray();

            MetricBucket *newEmptyBucket(long time) override;

            WindowWrap<MetricBucket> &resetWindowTo(WindowWrap<MetricBucket> &w, long startTime) override;
        };


    } // namespace Http

} // namespace Envoy
