#pragma once
#include "PriceLevel.hpp"
#include <iostream>
using namespace std;

struct OrderBookSnapshot{

    
    string stockName;
    int bestBid=0;
    int bestAsk=0;
    vector<PriceLevel>buyLevels;
    vector<PriceLevel>sellLevels;
};