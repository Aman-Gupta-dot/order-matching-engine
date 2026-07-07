#pragma once
#include <string>//we included string only out of iostream
using namespace std;

enum class BuyOrSell{
    BUY,
    SELL
};

struct Order{
    int orderId;
    BuyOrSell side;
    string stockName;
    int price;
    int quantity;
    long long timeStamp;//this timestmp tell when was this order 
    //born or created ,it can become large so we use long long.
};
