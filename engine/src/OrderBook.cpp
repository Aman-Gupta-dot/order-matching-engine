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
                if(o.type==OrderType::LIMIT || o.type==OrderType::IOC)
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
                            totalSellQuantities-=tradingQuantity;//For FOK orders

                            if(oldest.quantity==0)
                            {
                                idToOrderMappingForSell.erase(oldest.orderId);//these 2 lines in this order only
                                //otherwise if reversed pop will destroy &oldest referenece so can dangle
                                sellQueue.popfront();
                                
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
                    if(o.quantity>0 && o.type==OrderType::LIMIT)
                    {
                        buyBook[o.price].pushback(o);
                        idToOrderMappingForBuy[o.orderId]=o.price;
                        totalBuyQuantities+=o.quantity;//For FOK orders
                        
                    }

                }
                else if(o.type==OrderType::MARKET)
                {
                    // BUY MARKET ORDER
                    int totalRequestedQuantities=o.quantity;
                    while(o.quantity>0 && !sellBook.empty())
                    {
                        auto bestSell=sellBook.begin();//bestsell will be at top of buyBook
                        CustomLinkedQueue &sellQueue=bestSell->second;
                        Order &oldest=sellQueue.start();
                        //match order
                        Trade trade;
                        trade.buyOrderId=o.orderId;
                        trade.sellOrderId=oldest.orderId;
                        
                        int tradingQuantity=min(o.quantity,oldest.quantity);
                        trade.quantity=tradingQuantity;
                        trade.time_stamp=o.timeStamp;
                        trade.tradeId=nextTradeId;
                        nextTradeId++;

                        trade.tradePrice=oldest.price;
                        
                        
                        trade.stockName=stockName;
                        //trade generated
                        executedTrades.push_back(trade);
                        trades.push_back(trade);

                        //now update quantities
                        o.quantity-=tradingQuantity;
                        oldest.quantity-=tradingQuantity;
                        totalSellQuantities-=tradingQuantity;//For FOK orders

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForSell.erase(oldest.orderId);
                            sellQueue.popfront();
                            
                        }

                        if(sellQueue.isEmpty())
                        {
                            sellBook.erase(bestSell);
                        }
                    }
                    if(o.quantity>0)
                    {
                        //no more sellers left
                        //you can display message
                        cout<<"-------MARKET ORDER SUMMARY-------\n";
                        cout<<"requested quantities : "<<totalRequestedQuantities<<"\n";
                        cout<<"Executed quantities : "<<totalRequestedQuantities-o.quantity<<"\n";
                        cout<<"Unfilled quantities : "<<o.quantity<<"\n";

                        cout<<"Reason:\n";
                        cout<<"No more sell orders in sellBook, so remaining quantities are cancelled\n";
                        cout<<"----------------------------------\n";


                    }
                }
                else if(o.type==OrderType::FOK)
                {
                    //Fill or kill
                   if(o.quantity>totalSellQuantities)
                   {
                        cout<<"Order cancelled\n";
                        cout<<"Reason:Insufficient sell quantities\n";
                        return {};
                   }
                   else{
                    //check if all required quantities have price less than equal to as required for this order
                    int qtyTemp=0;
                    for(auto iter:sellBook)
                    {
                        if(qtyTemp>=o.quantity)
                        {
                            break;
                        }
                        if(iter.first>o.price)//cancel order as till now not required qts matched and sell price increased
                        {
                            //kill order
                            cout<<"Order cancelled\n";
                            cout<<"Reason:selling price more than buy price\n";
                            return {};
                        }
                        qtyTemp+=iter.second.getTotalQuantity();
                        
                    }
                    //if came till here, this means order shd be filled for sure
                    while(o.quantity>0)//2nd cond not written as we know this will pass anyway
                    {
                        auto bestSell=sellBook.begin();//bestbuy will be at top of buyBook
                        CustomLinkedQueue &sellQueue=bestSell->second;
                        Order &oldest=sellQueue.start();
                        //match order
                        Trade trade;
                        trade.buyOrderId=o.orderId;
                        trade.sellOrderId=oldest.orderId;
                        
                        int tradingQuantity=min(o.quantity,oldest.quantity);
                        trade.quantity=tradingQuantity;
                        trade.time_stamp=o.timeStamp;
                        trade.tradeId=nextTradeId;
                        nextTradeId++;

                        trade.tradePrice=oldest.price;//resting order price
                        
                        
                        trade.stockName=stockName;
                        //trade generated
                        executedTrades.push_back(trade);
                        trades.push_back(trade);

                        //now update quantities
                        o.quantity-=tradingQuantity;
                        oldest.quantity-=tradingQuantity;
                        totalSellQuantities-=tradingQuantity;//For FOK orders

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForSell.erase(oldest.orderId);
                            sellQueue.popfront();
                            
                        }

                        if(sellQueue.isEmpty())
                        {
                            sellBook.erase(bestSell);
                        }
                    }
                    
                    
                   }
                }
                
            }
            else if(o.side==BuyOrSell::SELL)
            {
                //now came a sell order, buy order resting
                if(o.type==OrderType::LIMIT || o.type==OrderType::IOC)
                {
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
                                totalBuyQuantities-=tradingQuantity;//For FOK orders

                                if(oldestBuy.quantity==0)
                                {
                                    idToOrderMappingForBuy.erase(oldestBuy.orderId);
                                    buyQueue.popfront();
                                    
                                }

                                if(buyQueue.isEmpty())
                                {
                                    buyBook.erase(bestBuy);
                                }
                                

                                
                            }
                            else break;
                        }
                        if(o.quantity>0 && o.type==OrderType::LIMIT)
                        {
                            sellBook[o.price].pushback(o);
                            idToOrderMappingForSell[o.orderId]=o.price;
                            totalSellQuantities+=o.quantity;//For FOK orders
                            
                        }

                }
                else if(o.type==OrderType::MARKET)
                {
                    // SELL MARKET ORDER
                    int totalRequestedQuantities=o.quantity;
                    while(o.quantity>0 && !buyBook.empty())
                    {
                        auto bestBuy=buyBook.begin();//bestbuy will be at top of buyBook
                        CustomLinkedQueue &buyQueue=bestBuy->second;
                        Order &oldest=buyQueue.start();
                        //match order
                        Trade trade;
                        trade.buyOrderId=oldest.orderId;
                        trade.sellOrderId=o.orderId;
                        
                        int tradingQuantity=min(o.quantity,oldest.quantity);
                        trade.quantity=tradingQuantity;
                        trade.time_stamp=o.timeStamp;
                        trade.tradeId=nextTradeId;
                        nextTradeId++;

                        trade.tradePrice=oldest.price;
                        
                        
                        trade.stockName=stockName;
                        //trade generated
                        executedTrades.push_back(trade);
                        trades.push_back(trade);

                        //now update quantities
                        o.quantity-=tradingQuantity;
                        oldest.quantity-=tradingQuantity;
                        totalBuyQuantities-=tradingQuantity;//For FOK orders

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForBuy.erase(oldest.orderId);
                            buyQueue.popfront();
                            
                        }

                        if(buyQueue.isEmpty())
                        {
                            buyBook.erase(bestBuy);
                        }
                    }
                    if(o.quantity>0)
                    {
                        //no more sellers left
                        //you can display message
                        cout<<"-------MARKET ORDER SUMMARY-------\n";
                        cout<<"requested quantities : "<<totalRequestedQuantities<<"\n";
                        cout<<"Executed quantities : "<<totalRequestedQuantities-o.quantity<<"\n";
                        cout<<"Unfilled quantities : "<<o.quantity<<"\n";

                        cout<<"Reason:\n";
                        cout<<"No more sell orders in sellBook so remaining quantities are cancelled\n";
                        cout<<"----------------------------------\n";


                    }
                }
                else if(o.type==OrderType::FOK)
                {
                   //Fill or kill
                   if(o.quantity>totalBuyQuantities)
                   {
                        cout<<"Order cancelled\n";
                        cout<<"Reason:Insufficient buy quantities\n";
                        return {};
                   }
                   else{
                    //check if all required quantities have price less than equal to as required for this order
                    int qtyTemp=0;
                    for(auto iter:buyBook)
                    {
                        if(qtyTemp>=o.quantity)
                        {
                            break;
                        }
                        if(iter.first<o.price)//cancel order as till now not required qts matched and buy price decreased
                        {
                            //kill order
                            cout<<"Order cancelled\n";
                            cout<<"Reason:Buy Price less than selling price\n";
                            return {};
                        }
                        qtyTemp+=iter.second.getTotalQuantity();
                        
                    }
                    //if came till here, this means order shd be filled for sure
                    while(o.quantity>0)//2nd cond not written as we know this will pass anyway
                    {
                        auto bestBuy=buyBook.begin();//bestbuy will be at top of buyBook
                        CustomLinkedQueue &buyQueue=bestBuy->second;
                        Order &oldest=buyQueue.start();
                        //match order
                        Trade trade;
                        trade.buyOrderId=oldest.orderId;
                        trade.sellOrderId=o.orderId;
                        
                        int tradingQuantity=min(o.quantity,oldest.quantity);
                        trade.quantity=tradingQuantity;
                        trade.time_stamp=o.timeStamp;
                        trade.tradeId=nextTradeId;
                        nextTradeId++;

                        trade.tradePrice=oldest.price;//resting price
                        
                        
                        trade.stockName=stockName;
                        //trade generated
                        executedTrades.push_back(trade);
                        trades.push_back(trade);

                        //now update quantities
                        o.quantity-=tradingQuantity;
                        oldest.quantity-=tradingQuantity;
                        totalBuyQuantities-=tradingQuantity;//For FOK orders

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForBuy.erase(oldest.orderId);
                            buyQueue.popfront();
                            
                        }

                        if(buyQueue.isEmpty())
                        {
                            buyBook.erase(bestBuy);
                        }
                    }
                    
                    
                   }
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
       totalBuyQuantities-=buyBook[toBeDeletedprice].getNodeForGivenId(oid)->order.quantity;
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
       totalSellQuantities-=sellBook[toBeDeletedprice].getNodeForGivenId(oid)->order.quantity;
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
    cout<<"Total Buy Quantities : "<<totalBuyQuantities<<endl;
    cout<<"Total Sell Quantities : "<<totalSellQuantities<<endl;
    
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