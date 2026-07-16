#pragma once
using namespace std;

class ExchangeStatistics{
    private:

        int ordersReceived;
        int ordersCancelled;
        int tradedQuantity;
        int tradesExecuted;
        
    public:
        ExchangeStatistics();
        void incrementOrdersReceived();
        void incrementOrdersCancelled();
        void setTradesExecuted(int &value);
        void setTradedQuantity(int &value);



};