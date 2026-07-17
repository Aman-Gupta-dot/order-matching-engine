#include<iostream>
#include<cstdlib>//for rand() and srand()
#include<ctime>//for seed to srand()
#include<chrono>
#include "../include/Exchange.hpp"
#include "../include/VerifyIntegrity.hpp"
#include "stressTest.hpp"
using namespace std;

void stressTest::doStressTest(int numOrders,int &overallOrderId,int &overalltimeStamp,Exchange &exchange)
{
    for(int i=1;i<=numOrders;i++)
    {
       
        Order order;
        int randomStockNumber=rand()%4+1;
        
        if(randomStockNumber==1)
        {
            order.stockName="Dairy Milk";
        }
        else if(randomStockNumber==2)
        {
            order.stockName="5 Star";
        }
        else if(randomStockNumber==3)
        {
            order.stockName="Ferrero Rocher";
        }
        else if(randomStockNumber==4)
        {
            order.stockName="Kinder Joy";
        }

       


        order.orderId=++overallOrderId;
        order.timeStamp=++overalltimeStamp;
        order.quantity=rand()%100+1;
        
        int randomSide=rand()%2+1;
        if(randomSide==1)
        {
            order.side=BuyOrSell::BUY;
        }
        else{
            order.side=BuyOrSell::SELL;
        }

        int randomOrderType=rand()%4+1;
        if(randomOrderType==1)
        {
            order.type=OrderType::LIMIT;
        }
        else if(randomOrderType==2)
        {
            order.type=OrderType::MARKET;
        }
        else if(randomOrderType==3)
        {
            order.type=OrderType::FOK;
        }
        else if(randomOrderType==4)
        {
            order.type=OrderType::IOC;
        }

        if(randomOrderType!=2)//price not required for market order
        {
            order.price=50+(rand()%(500-50+1));//generate a random price bw 50 and 500
        }
        
        
        exchange.placeOrder(order);
  }
}

void stressCancellationTest(int &overallOrderId,int &overalltimeStamp,Exchange &exchange)
{
    for(int i=1;i<1000;i++)
    {
        Order order;
    order.type=OrderType::LIMIT;
    order.orderId=++overallOrderId;
    order.timeStamp=overalltimeStamp;

    int randomSide=rand()%2+1;
        if(randomSide==1)
        {
            order.side=BuyOrSell::BUY;
            order.price=5+rand()%(500-5+1);//price bw 5 and 500

        }
        else{
            order.side=BuyOrSell::SELL;
            order.price=600+rand()%(1000-600+1);//price bw 5 and 500

        }
        order.quantity=1+rand()%(100-1+1);//quantity bw 1 and 100

        int randomStockNumber=rand()%4+1;
        
        if(randomStockNumber==1)
        {
            order.stockName="Dairy Milk";
        }
        else if(randomStockNumber==2)
        {
            order.stockName="5 Star";
        }
        else if(randomStockNumber==3)
        {
            order.stockName="Ferrero Rocher";
        }
        else if(randomStockNumber==4)
        {
            order.stockName="Kinder Joy";
        }
        //this way order will never match
        exchange.placeOrder(order);

        if(i%10==0)
        {
            int randomid=100+rand()%(overallOrderId-100+1);
            exchange.cancelOrder(randomid,order.stockName,order.side);
        }

        
        
    }
}
int main()
{
  int overallOrderId=100;
  int overalltimeStamp=0;
  
  Exchange exchange(false);
  srand(time(0));

//   auto start=chrono::high_resolution_clock::now();
//   stressTest(overallOrderId,overalltimeStamp,exchange); 
//   auto end=chrono::high_resolution_clock::now();

//  auto executionTime=(chrono::duration_cast<chrono::milliseconds>)(end-start);
//  cout<<executionTime.count()<<"milli seconds";
// string stock="Dairy Milk";
//  exchange.viewOrderBook(stock);

//   exchange.showTrades(stock);
//  cout<<endl;
//  exchange.viewOrderBook(stock);
//  cout<<endl;

//  exchange.showStatistics(stock);

//  VerifyIntegrity verifier;
//  bool result=verifier.checkExchange(exchange);
//  cout<<"\n";
//  cout<<"\n Congratulations!! Your Order engine holds complete integrity among all its operations\n";
//  cout<<"\n";



 //phase 1:random order generation(done)
 //now we'll include random cancellations but the problem is-->how to find that random id
//  (it might be executed),(it might be cancelled before),(our function has 3 parameters 
//  which are all randomly decided so the probability of such a event happening is very tiny-->
// almost negligible)

//so we'll create a second fn to test stress cancellation
stressCancellationTest(overallOrderId,overalltimeStamp,exchange);

 string stock="Dairy Milk";
 exchange.viewOrderBook(stock);

  exchange.showTrades(stock);
 cout<<endl;
 exchange.viewOrderBook(stock);
 cout<<endl;

 exchange.showStatistics(stock);
 VerifyIntegrity verifier;
 bool result=verifier.checkExchange(exchange);
 cout<<"\n";
 cout<<"\n Congratulations!! Your Order engine holds complete integrity among all its operations\n";
 cout<<"\n";
  

  
    return 0;
}