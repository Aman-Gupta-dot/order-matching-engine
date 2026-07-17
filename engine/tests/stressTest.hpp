#pragma once
#include "../include/Exchange.hpp"
class stressTest{
    public:
        stressTest();
        void doStressTest(int randomOrders,int &overallOrderId,int &overalltimeStamp,Exchange &exchange);



};