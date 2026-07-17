#pragma once
class Exchange;
class stressTest{
    public:

        
        void doStressTest(int randomOrders,int &overallOrderId,int &overalltimeStamp,Exchange *exchange);
        void stressCancellationTest(int randomOrders,int &overallOrderId,int &overalltimeStamp,Exchange *exchange);



};