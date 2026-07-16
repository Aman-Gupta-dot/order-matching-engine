#pragma once
#include <string>//we included string only out of iostream
using namespace std;

enum class BuyOrSell{
    BUY,
    SELL
};

enum class OrderType{
    LIMIT,
    MARKET,
    FOK,
    IOC

};

struct Order{
    int orderId;
    BuyOrSell side;
    OrderType type;
    string stockName;
    int price;
    int quantity;
    long long timeStamp;//this timestmp tell when was this order 
    //born or created ,it can become large so we use long long.
};
