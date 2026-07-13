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
        while(o.quantity>0 && !sellBook.empty())//try to match maximum sell orders thru buy orders
        {
            auto bestSell=sellBook.begin();//it give a pointer to iterator over the map start as ascending so best sell is at start only
            if(bestSell->first<=o.price)
            {
                //trade will happen
                //at what trade price
                CustomLinkedQueue &sellQueue=bestSell->second;
                //this queue has selling orders aligned in this queue for this particular price
                Order &oldest=sellQueue.start();//to make changes to original q we used &
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
                    sellQueue.popfront();
                    idToOrderMappingForSell.erase(oldest.orderId);
                }

                if(sellQueue.isEmpty())
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
            buyBook[o.price].pushback(o);
            idToOrderMappingForBuy[o.orderId]=o.price;
            
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
                CustomLinkedQueue &buyQueue=bestBuy->second;

                Order &oldestBuy=buyQueue.start();

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
                    buyQueue.popfront();
                    idToOrderMappingForBuy.erase(oldestBuy.orderId);
                }

                if(buyQueue.isEmpty())
                {
                    buyBook.erase(bestBuy);
                }
                

                
            }
            else break;
        }
        if(o.quantity>0)
        {
            sellBook[o.price].pushback(o);
            idToOrderMappingForSell[o.orderId]=o.price;
            
        }


    }
    return executedTrades;//to return vector of trades
}

void OrderBook::deleteOrder(int &oid,BuyOrSell side)
{
    if(side==BuyOrSell::BUY)
    {
        if(idToOrderMappingForBuy.count(oid)==0)
        {
            cout<<"No such id in buy order book currently\n";
            return;
        }
        
       
       double toBeDeletedprice=idToOrderMappingForBuy[oid];
       buyBook[toBeDeletedprice].pop(oid);
       if(buyBook[toBeDeletedprice].isEmpty())
       {
        buyBook.erase(toBeDeletedprice);
       }

       idToOrderMappingForBuy.erase(oid);    
    }
    else
    {
         if(idToOrderMappingForSell.count(oid)==0)
        {
            cout<<"No such id in sell order book currently\n";
            return;
        }
        
       
       double toBeDeletedprice=idToOrderMappingForSell[oid];
       sellBook[toBeDeletedprice].pop(oid);
       if(sellBook[toBeDeletedprice].isEmpty())
       {
        sellBook.erase(toBeDeletedprice);
       }
       idToOrderMappingForSell.erase(oid);    
    }
}


//now display current orderBook
//just display all pending orders(both buy sise and sell side)
void OrderBook::showOrderBook() const
{
    cout<<"==============================================================================================\n";
    cout<<"                                  ORDER-BOOK-"<<stockName<<"                                  ";
    cout<<"==============================================================================================\n";
    cout<<"\nBuy Orders:\n";

    cout<<"----------------------------------------------------------------------------------------------\n";
    for(auto &priceLevel:buyBook)//&used so copy not created again and again costing us memory
    {
        cout<<"Price : "<<priceLevel.first<<endl;
        cout<<" | Waiting Orders at this price : "<<priceLevel.second.getSize()<<endl;
        
        cout<<"OrderId"<<"  "<<"Price"<<"  "<<"quantity"<<endl;
        cout<<"----------------------------------------------------------------------------------------------\n";
        Node*temp=priceLevel.second.getFront();//temp to print this customQueue
        while(temp!=nullptr)
        {
            cout<<temp->order.orderId<<"      "<<temp->order.price<<"      "<<temp->order.quantity<<endl;
            temp=temp->next;
        }
    

    cout<<"----------------------------------------------------------------------------------------------\n";

    }

    cout<<"\nSell Orders:\n";

    for(auto &priceLevel:sellBook)
    {
        cout<<"Price : "<<priceLevel.first
        <<" | Waiting Orders at this price : "<<priceLevel.second.getSize()<<endl;
        
        cout<<"OrderId"<<"  "<<"Price"<<"  "<<"quantity"<<endl;
    cout<<"----------------------------------------------------------------------------------------------\n";
        Node*temp=priceLevel.second.getFront();//temp to print this customQueue
        while(temp!=nullptr)
        {
            cout<<temp->order.orderId<<"      "<<temp->order.price<<"      "<<temp->order.quantity<<endl;
            temp=temp->next;
        }
    cout<<"----------------------------------------------------------------------------------------------\n";


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