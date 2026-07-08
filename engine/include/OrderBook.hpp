#pragma once

#include "Order.hpp"
#include "Trade.hpp"

#include<vector>
#include<map>
#include<queue>
#include<functional>// *to sort order details on basis of price in map

using namespace std;
class OrderBook{

    private:
        string stockName;//*to know for which stock this order book created
        map<int,queue<Order>,greater<int> >buyBook;//as we need a mapping of price to queue
        //(if same price) then fcfs implemented through queue for a particular same price 
        //sorted in descending order as we want max price order to be at starting of the map
        
        map<int,queue<Order> >sellBook;//in ascending order by default
    
        vector<Trade>trades;//store all trades done till now in order
        
        int nextTradeId=1;//trade matches from this orderBook only

    public:
        OrderBook( string stockName);
        

        vector<Trade> placeOrder(Order o);//to place order o in this Orderbook if matches then return vector of trades otherwise empty set

        void showOrderBook()const;//shows all pending Orders
        void showTrades()const;//show trades done till now


        string getStockName()const;//getter for stockname



};

