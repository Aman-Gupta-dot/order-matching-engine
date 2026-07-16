#pragma once

using namespace std;

struct StatisticsBook{
        int totalTrades;
        int totalTradedQuantity;
        int totalTradedValue;
        int activeBuyOrders;
        int activeSellOrders;
        double buyVolume;
        double sellVolume;
        int bestBid;
        int bestAsk;
        int ordersCancelled;
        int ordersReceived;
};