#include<iostream>
using namespace std;
#include "../include/Exchange.hpp"

Exchange::Exchange()
{
    
    books.emplace("Dairy Milk",OrderBook("Dairy Milk"));
    books.emplace("5-star",OrderBook("5-star"));
    books.emplace("Ferrero Rocher",OrderBook("Ferrero Rocher"));
    books.emplace("Kinder Joy",OrderBook("Kinder Joy"));
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
