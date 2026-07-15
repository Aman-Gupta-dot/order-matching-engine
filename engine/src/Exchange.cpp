#include<iostream>
using namespace std;
#include "../include/Exchange.hpp"

Exchange::Exchange(bool value)
{
    
    books.emplace("Dairy Milk",OrderBook("Dairy Milk"));
    books.emplace("5 Star",OrderBook("5 Star"));
    books.emplace("Ferrero Rocher",OrderBook("Ferrero Rocher"));
    books.emplace("Kinder Joy",OrderBook("Kinder Joy"));

    for(auto &i: books)
    {
        i.second.setVerbose(value);
    }
}

void Exchange::placeOrder(Order order)
{
    auto it = books.find(order.stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return;
    }
    it->second.placeOrder(order);
    
}

void Exchange::cancelOrder(int &oid,string &stockName,BuyOrSell side)
{
    auto it = books.find(stockName);

    if(it == books.end())
    {
        cout << "Invalid Stock Name\n";
        return;
    }
    it->second.deleteOrder(oid,side);
    
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
unordered_map<string,OrderBook> getBooks() const;

