#pragma once

#include "Order.hpp"
#include "Trade.hpp"
#include "CustomLinkedQueue.hpp"
#include "OrderBookSnapshot.hpp"//for to model data so it can be sent to server
#include "TradeBook.hpp"
#include "StatisticsBook.hpp"

#include<vector>
#include<map>
#include<unordered_map>
#include<queue>
#include<functional>// *to sort order details on basis of price in map

using namespace std;
class OrderBook{

    private:
        string stockName;//*to know for which stock this order book created
        map<int,CustomLinkedQueue,greater<int> >buyBook;//as we need a mapping of price to queue
        //(if same price) then fcfs implemented through queue for a particular same price 
        //sorted in descending order as we want max price order to be at starting of the map
        
        map<int,CustomLinkedQueue >sellBook;//in ascending order by default

        unordered_map<int,double>idToOrderMappingForBuy;//for deleting buy orders
        unordered_map<int,double>idToOrderMappingForSell;//for deleting sell orders
    
        vector<Trade>trades;//store all trades done till now in order
        
        int nextTradeId=1;//trade matches from this orderBook only

        int totalBuyQuantities=0;//they are needed for FOK orders for instant compares
        int totalSellQuantities=0;//INITIALIZED WITH 0

        bool verbose;//for stresstest to avoid printing

        //for stats
        int totalTrades=0;
        int totalTradedQuantity=0;
        int totalTradedValue=0;
        int activeBuyOrders=0;
        int activeSellOrders=0;
        double buyVolume=0;
        double sellVolume=0;
        int bestBid=0;
        int bestAsk=0;
        int ordersCancelled=0;
        int ordersReceived=0;

        //for data modelling
        unordered_map<int,int>pricelevelToquantityMappingForBuy;
        unordered_map<int,int>pricelevelToquantityMappingForSell;


    public:
        OrderBook(string stockName);
        

        vector<Trade> placeOrder(Order o);//to place order o in this Orderbook if matches then return vector of trades otherwise empty set
        int deleteOrder(int &oid,BuyOrSell side);//delete order from book if oid exists in queue

        void showOrderBook()const;//shows all pending Orders
        void showTrades()const;//show trades done till now


        string getStockName()const;//getter for stockname

        void setVerbose(bool value);//we'll set it true normally to get all prints and false for test
        
        //stats
        int getTradedValue() const;
        int getTradedQuantity() const;
        int getActiveBuyOrders() const;
        int getActiveSellOrders() const;
        int getBuyVolume() const;
        int getSellVolume() const;

        int getTradesExecuted() const;
        int getBestBid() const;
        int getBestAsk() const;

        int getOrdersReceived() const;
        int getOrdersCancelled() const;

        //integrity
        map<int,CustomLinkedQueue,greater<int> > getBuyBook()const;
        map<int,CustomLinkedQueue >getSellBook()const;

        //model data for server
        OrderBookSnapshot getOrderBook() const;
        TradeBook getTradeBook() const;
        StatisticsBook getStatisticsBook()const;
        

        



};

