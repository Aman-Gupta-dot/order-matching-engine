#pragma once
#include "OrderBook.hpp"
#include "ExchangeStatistics.hpp"
#include<unordered_map>
using namespace std;
class Exchange{
    private:
        unordered_map<string,OrderBook>books;
        ExchangeStatistics excStatistics;
        int orderId=100;
        int timestamp=0;
    public:
        Exchange(bool value);
        void placeOrder(Order order);
        int cancelOrder(int &oid,string &stockName,BuyOrSell side);
        void viewOrderBook(string &stockName);
        void showTrades(string &stockName);
        void showStatistics(string &stockName);
        unordered_map<string,OrderBook> getBooks() const;
        

        OrderBookSnapshot getOrderBook(string &stockname)const;
        TradeBook getTradeBook(string &stockName)const;
        StatisticsBook getStatisticsBook(string &stockName)const;
};