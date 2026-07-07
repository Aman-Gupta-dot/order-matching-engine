#pragma once
#include<string>
using namespace std;

struct Trade{
    int tradeId;
    int buyOrderId;
    int sellOrderId;
    string stockName;
    double tradePrice;
    int quantity;
    long long time_stamp;
    
};