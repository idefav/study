//
// Created by 吴子庶 on 2021/10/7.
//
#pragma once


#include "node.h"
#include "array_metric.h"

namespace Envoy {
    namespace Http {
        class StasticNode : public Node {
        private:
            /* data */
            ArrayMetric *rollingCounterInSecond_;
            ArrayMetric *rollingCounterInMinute_;
            atomic_long curThreadNum_;

        public:
            StasticNode();

            StasticNode(const StasticNode &o);

            ~StasticNode();

            // read
            inline void reset() override;

            inline long totalRequest() override;

            inline long blockRequest() override;

            inline double blockQps() override;

            inline double previousBlockQps() override;

            inline double previousPassQps() override;

            inline double totalQps() override;

            inline long totalSuccess() override;

            inline double exceptionQps() override;

            long totalException() override;

            double passQps() override;

            long totalPass() override;

            double successQps() override;

            double maxSuccessQps() override;

            double avgRt() override;

            inline double minRt() override;

            int curThreadNum() override;

            // write
            void addPassRequest(int count) override;

            void addRtAndSuccess(long rt, int successCount) override;

            void increaseBlockQps(int count) override;

            void increaseExceptionQps(int count) override;

            void increaseThreadNum() override;

            void decreaseThreadNum() override;
        };


    } // namespace Http

} // namespace Envoy

