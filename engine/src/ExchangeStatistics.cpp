#include<iostream>
using namespace std;

#include "../include/ExchangeStatistics.hpp"

ExchangeStatistics::ExchangeStatistics()
{
    ordersReceived=0;
    ordersCancelled=0;
    
    tradesExecuted=0;



}

void ExchangeStatistics::incrementOrdersReceived()
{
    ordersReceived++;
}
void ExchangeStatistics::incrementOrdersCancelled()
{
    ordersCancelled++;
}

void ExchangeStatistics::setTradesExecuted(int &value)
{
    tradesExecuted=value;
}
void ExchangeStatistics::setTradedQuantity(int &value)
{
    tradedQuantity=value;
}

