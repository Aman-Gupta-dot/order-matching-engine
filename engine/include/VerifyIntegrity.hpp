#pragma once
#include "OrderBook.hpp"
#include "Exchange.hpp"

class VerifyIntegrity{

    public:
        bool checkQueue(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook);
        bool checkPriceLevels(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook);
        bool checkOrderBook(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook,int totalBuyQuantities,int totalsellquantities,int activeBuyOrders,int activeSellOrders);
        bool checkMapping(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook);
        bool checkExchange(Exchange &exchange);



};