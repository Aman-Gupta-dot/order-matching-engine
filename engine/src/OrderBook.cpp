#include "../include/OrderBook.hpp"

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

OrderBook::OrderBook(string name)//OrderBook:: this means this constructor belongs to that class that is why this private variable is not giving error
{
    this->stockName=name;
}

vector<Trade> OrderBook::placeOrder(Order o)//one order may generate 0,1 or many orders at one
{
    vector<Trade>executedTrades;//ans to return for current buy order that came
    if(o.side==BuyOrSell::BUY)
    {
        //*add entry to buyBook
        while(o.quantity>0 && !sellBook.empty())//try to mach maximum sell orders thru buy orders
        {
            auto bestSell=sellBook.begin();//it give a pointer to iterator over the map start as ascending so best sell is at start only
            if(bestSell->first<=o.price)
            {
                //trade will happen
                //at what trade price
                queue<Order>&sellQueue=bestSell->second;
                //this queue has selling orders aligned in this queue for this particular price
                Order &oldest=sellQueue.front();//to make changes to original q we used &

                int tradingQuantity=min(oldest.quantity,o.quantity);

                Trade trade;
                trade.tradeId=nextTradeId;
                nextTradeId++;

                trade.buyOrderId=o.orderId;
                trade.sellOrderId=oldest.orderId;
                trade.quantity=tradingQuantity;
                trade.stockName=stockName;
                
                trade.tradePrice=oldest.price;//resting order price;
                trade.time_stamp=o.timeStamp;//new order time stamp if trade happened
                
                executedTrades.push_back(trade);
                trades.push_back(trade);//in this vector push_back all trades

                //update changes to quantity
                o.quantity-=tradingQuantity;//can't become -ve as min(o,oldest)
                oldest.quantity-=tradingQuantity;

                if(oldest.quantity==0)
                {
                    sellQueue.pop();
                }

                if(sellQueue.empty())
                {
                    sellBook.erase(bestSell);
                    //remove this key value pair
                    //in map either feed key to erase or whole iterator object it has both implementations
                }

            }
            else break;//buyer is not willing to pay that much amount
        }
        if(o.quantity>0)
        {
            sellBook[o.price].push(o);
        }
    }
    else if(o.side==BuyOrSell::SELL)
    {
        //now came a sell order, buy order resting
        while(o.quantity>0 && !buyBook.empty())//order has some qty left and sell book not empty
        {
            auto bestBuy=buyBook.begin();
            if(bestBuy->first>=o.price)
            {

                //match the order
                queue<Order>&buyQueue=bestBuy->second;

                Order &oldestBuy=buyQueue.front();

                Trade trade;
                trade.buyOrderId=oldestBuy.orderId;
                trade.sellOrderId=o.orderId;
                trade.stockName=stockName;
                
                int tradingQuantity=min(o.quantity,oldestBuy.quantity);
                trade.quantity=tradingQuantity;
                trade.tradeId=nextTradeId;
                nextTradeId++;

                trade.time_stamp=o.timeStamp;
                trade.tradePrice=oldestBuy.price;//resting order price

                executedTrades.push_back(trade);
                trades.push_back(trade);

                //change quantities

                oldestBuy.quantity-=trade.quantity;
                o.quantity-=trade.quantity;

                if(oldestBuy.quantity==0)
                {
                    buyQueue.pop();
                }

                if(buyQueue.empty())
                {
                    buyBook.erase(bestBuy);
                }
                

                
            }
            else break;
        }
        if(o.quantity>0)
        {
            buyBook[o.price].push(o);
        }


    }
    return executedTrades;//to return vector of trades
}


//now display current orderBook
//just display all pending orders(both buy sise and sell side)
void OrderBook::showOrderBook() const
{
    cout<<"================================ORDER-BOOK-"<<stockName<<"================================";
    cout<<"\nBuy Orders:\n";

    for(auto &priceLevel:buyBook)//&used so copy not created again and again costing us memory
    {
        cout<<"Price : "<<priceLevel.first
        <<" | Waiting Orders at this price : "<<priceLevel.second.size()<<endl;
    }

    cout<<"\nSell Orders:\n";

    for(auto &priceLevel:sellBook)
    {
        cout<<"Price : "<<priceLevel.first
        <<" | Waiting Orders at this price : "<<priceLevel.second.size()<<endl;
    }
}

//now display all executed trades which we stored in trades vector
void OrderBook::showTrades() const{
    cout<<"================================All-Trades : "<<stockName<<" ================================";
    cout<<"\nTotal Trades Happened : "<<trades.size()<<endl;

    for(int i=0;i<trades.size();i++)
    {
        cout<<"Trade id : "<<trades[i].tradeId<<endl;
        cout<<" | Buy Order Id : "<<trades[i].buyOrderId<<endl;
        cout<<" | Sell Order Id : "<<trades[i].sellOrderId<<endl;
        cout<<" | Price: "<<trades[i].tradePrice<<endl;
        cout<<" | Quantity : "<<trades[i].quantity<<endl;
        cout<<" | Trade time stamp : "<<trades[i].time_stamp<<endl;
        
    }
}
string OrderBook::getStockName()const{
    return stockName;
}