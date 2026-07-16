#include<iostream>
using namespace std;
#include "../include/Exchange.hpp"

Exchange::Exchange(bool value)
{
    
    books.emplace("DairyMilk",OrderBook("DairyMilk"));
    books.emplace("5Star",OrderBook("5Star"));
    books.emplace("FerreroRocher",OrderBook("FerreroRocher"));
    books.emplace("KinderJoy",OrderBook("KinderJoy"));

    for(auto &i: books)
    {
        i.second.setVerbose(value);
    }
}

void Exchange::placeOrder(Order order)
{
    cout << "Exchange::placeOrder() called\n";
cout << "Searching for [" << order.stockName << "]\n";

for (const auto &x : books)
{
    cout << "Book : [" << x.first << "]\n";
}
    auto it = books.find(order.stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return;
    }
    order.orderId=++orderId;
    order.timeStamp=++timestamp;
    it->second.placeOrder(order);
    
}

int Exchange::cancelOrder(int &oid,string &stockName,BuyOrSell side)
{
    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return 0;
    }
    int response=it->second.deleteOrder(oid,side);
    return response;
    
    // books[stockName].deleteOrder(oid,side);
}

void Exchange::viewOrderBook(string &stockName)
{
    
    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return;
    }
    it->second.showOrderBook();
    // books[stockName].showOrderBook();
}

void Exchange::showTrades(string &stockName)
{
    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return;
    }
    it->second.showTrades();

    // books[stockName].showTrades();
}
void Exchange::showStatistics(string &stockName)
{
    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return;
    }
    cout<<"Orders Received : "<<it->second.getOrdersReceived()<<endl;
    cout<<endl;

    cout<<"Orders Cancelled : "<<it->second.getOrdersCancelled()<<endl;
    cout<<endl;

    cout<<"Total Trades executed : "<<it->second.getTradesExecuted()<<endl;
    cout<<endl;

    cout<<"Total Traded Quantity : "<<it->second.getTradedQuantity()<<endl;
    cout<<endl;

    cout<<"Total Traded Value : "<<it->second.getTradedValue()<<endl;
    cout<<endl;

    cout<<"Active Buy Orders : "<<it->second.getActiveBuyOrders()<<endl;
    cout<<endl;

    cout<<"Active Sell Orders : "<<it->second.getActiveSellOrders()<<endl;
    cout<<endl;

    cout<<"Buy Volume : "<<it->second.getBuyVolume()<<endl;
    cout<<endl;

    cout<<"Sell Volume : "<<it->second.getSellVolume()<<endl;
    cout<<endl;

    cout<<"Best Bid : "<<it->second.getBestBid()<<endl;
    cout<<endl;

    cout<<"Best Ask : "<<it->second.getBestAsk()<<endl;
    cout<<endl;

    
    

}
unordered_map<string,OrderBook> Exchange::getBooks() const{
    return books;
}
OrderBookSnapshot Exchange::getOrderBook(string &stockName)const{

    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return {};
    }
    return it->second.getOrderBook();
    
}
TradeBook Exchange::getTradeBook(string &stockName)const{

    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return {};
    }
    return it->second.getTradeBook();
}
StatisticsBook Exchange::getStatisticsBook(string &stockName)const
{
    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return {};
    }
    return it->second.getStatisticsBook();

}


