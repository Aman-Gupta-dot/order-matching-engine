#pragma once
#include "OrderBook.hpp"
class Exchange;

class VerifyIntegrity{

    public:
        bool checkQueue(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook);
        bool checkPriceLevels(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook);
        bool checkOrderBook(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook,int totalBuyQuantities,int totalsellquantities,int activeBuyOrders,int activeSellOrders);
        bool checkMapping(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook);
        int checkExchange(Exchange *exchange);

};