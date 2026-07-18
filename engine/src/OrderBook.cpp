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
                ordersReceived++;//stats
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
                            if(pricelevelToquantityMappingForSell[oldest.price]==0)
                            {
                                pricelevelToquantityMappingForSell.erase(oldest.price);
                            }
                            else
                            {
                                pricelevelToquantityMappingForSell[oldest.price] -= tradingQuantity;
                            }

                            //stats
                            totalTradedQuantity+=tradingQuantity;
                            totalTradedValue+=trade.tradePrice*tradingQuantity;
                            

                            if(oldest.quantity==0)
                            {
                                idToOrderMappingForSell.erase(oldest.orderId);//these 2 lines in this order only
                                //otherwise if reversed pop will destroy &oldest referenece so can dangle
                                sellQueue.popfront();
                                //stats
                                activeSellOrders--;//orders reduce when quantity becomes 0
                                
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

                        //stats
                        activeBuyOrders++;
                        

                        //data model
                        pricelevelToquantityMappingForBuy[o.price]+=o.quantity;
                        
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
                         if(pricelevelToquantityMappingForSell[oldest.price]==0)
                            {
                                pricelevelToquantityMappingForSell.erase(oldest.price);
                            }
                            else
                            {
                                pricelevelToquantityMappingForSell[oldest.price] -= tradingQuantity;
                            }
                        totalSellQuantities-=tradingQuantity;//For FOK orders

                        //stats
                        totalTradedQuantity+=tradingQuantity;
                        totalTradedValue+=trade.tradePrice*tradingQuantity;
                        

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForSell.erase(oldest.orderId);
                            sellQueue.popfront();
                            //stats
                                activeSellOrders--;//orders reduce when quantity becomes 0
                            
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
                        if(verbose)
                        {
                            cout<<"-------MARKET ORDER SUMMARY-------\n";
                            cout<<"requested quantities : "<<totalRequestedQuantities<<"\n";
                            cout<<"Executed quantities : "<<totalRequestedQuantities-o.quantity<<"\n";
                            cout<<"Unfilled quantities : "<<o.quantity<<"\n";

                            cout<<"Reason:\n";
                            cout<<"No more sell orders in sellBook, so remaining quantities are cancelled\n";
                            cout<<"----------------------------------\n";
                        }

                    }
                }
                else if(o.type==OrderType::FOK)
                {
                    //Fill or kill
                   if(o.quantity>totalSellQuantities)
                   {
                        if(verbose)
                        {
                            cout<<"Order cancelled\n";
                            cout<<"Reason:Insufficient sell quantities\n";
                        }
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
                            if(verbose)
                            {
                                cout<<"Order cancelled\n";
                                cout<<"Reason:selling price more than buy price\n";
                            }
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
                            if(pricelevelToquantityMappingForSell[oldest.price]==0)
                            {
                                pricelevelToquantityMappingForSell.erase(oldest.price);
                            }
                            else
                            {
                                pricelevelToquantityMappingForSell[oldest.price] -= tradingQuantity;
                            }
                        totalSellQuantities-=tradingQuantity;//For FOK orders

                        //stats
                        totalTradedQuantity+=tradingQuantity;
                        totalTradedValue+=trade.tradePrice*tradingQuantity;
                        

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForSell.erase(oldest.orderId);
                            sellQueue.popfront();
                            //stats
                                activeSellOrders--;//orders reduce when quantity becomes 0
                            
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
                ordersReceived++;//stats
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
                                if(pricelevelToquantityMappingForBuy[oldestBuy.price]==0)
                                {
                                    pricelevelToquantityMappingForBuy.erase(oldestBuy.price);
                                }
                                else
                                {
                                    pricelevelToquantityMappingForBuy[oldestBuy.price] -= tradingQuantity;
                                }
                                totalBuyQuantities-=tradingQuantity;//For FOK orders

                                //stats
                                totalTradedQuantity+=tradingQuantity;
                                totalTradedValue+=trade.tradePrice*tradingQuantity;
                                

                                if(oldestBuy.quantity==0)
                                {
                                    idToOrderMappingForBuy.erase(oldestBuy.orderId);
                                    buyQueue.popfront();
                                    //stats
                                activeBuyOrders--;//orders reduce when quantity becomes 0
                                    
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

                            //stats
                            activeSellOrders++;
                            

                            //data model

                            pricelevelToquantityMappingForSell[o.price]+=o.quantity;
                            
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
                                if(pricelevelToquantityMappingForBuy[oldest.price]==0)
                                {
                                    pricelevelToquantityMappingForBuy.erase(oldest.price);
                                }
                                else
                                {
                                    pricelevelToquantityMappingForBuy[oldest.price] -= tradingQuantity;
                                }
                        totalBuyQuantities-=tradingQuantity;//For FOK orders

                        //stats
                        totalTradedQuantity+=tradingQuantity;
                        totalTradedValue+=trade.tradePrice*tradingQuantity;
                        

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForBuy.erase(oldest.orderId);
                            buyQueue.popfront();
                            //stats
                            activeBuyOrders--;//orders reduce when quantity becomes 0
                            
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
                        if(verbose)
                        {
                            cout<<"-------MARKET ORDER SUMMARY-------\n";
                            cout<<"requested quantities : "<<totalRequestedQuantities<<"\n";
                            cout<<"Executed quantities : "<<totalRequestedQuantities-o.quantity<<"\n";
                            cout<<"Unfilled quantities : "<<o.quantity<<"\n";

                            cout<<"Reason:\n";
                            cout<<"No more sell orders in sellBook so remaining quantities are cancelled\n";
                            cout<<"----------------------------------\n";
                        }


                    }
                }
                else if(o.type==OrderType::FOK)
                {
                   //Fill or kill
                   if(o.quantity>totalBuyQuantities)
                   {
                        if(verbose)
                        {
                            cout<<"Order cancelled\n";
                            cout<<"Reason:Insufficient buy quantities\n";
                        }
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
                            if(verbose){
                                cout<<"Order cancelled\n";
                                cout<<"Reason:Buy Price less than selling price\n";
                            }
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
                                if(pricelevelToquantityMappingForBuy[oldest.price]==0)
                                {
                                    pricelevelToquantityMappingForBuy.erase(oldest.price);
                                }
                                else
                                {
                                    pricelevelToquantityMappingForBuy[oldest.price] -= tradingQuantity;
                                }
                        totalBuyQuantities-=tradingQuantity;//For FOK orders

                        //stats
                        totalTradedQuantity+=tradingQuantity;
                        totalTradedValue+=trade.tradePrice*tradingQuantity;
                        

                        if(oldest.quantity==0)
                        {
                            idToOrderMappingForBuy.erase(oldest.orderId);
                            buyQueue.popfront();
                            //stats
                            activeBuyOrders--;//orders reduce when quantity becomes 0
                            
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

int OrderBook::deleteOrder(int &oid,BuyOrSell side)
{

    if(side==BuyOrSell::BUY)
    {
        if(idToOrderMappingForBuy.count(oid)==0)
        {
            cout<<"No such id in buy order book currently\n";
            return 0;
        }
        
       cout<<"cancelled oid : "<<oid<<endl;
       double toBeDeletedprice=idToOrderMappingForBuy[oid];
       totalBuyQuantities-=buyBook[toBeDeletedprice].getNodeForGivenId(oid)->order.quantity;//for stats also

        //data model
       pricelevelToquantityMappingForBuy[toBeDeletedprice]-=buyBook[toBeDeletedprice].getNodeForGivenId(oid)->order.quantity;

       buyBook[toBeDeletedprice].pop(oid);
       if(buyBook[toBeDeletedprice].isEmpty())
       {
        buyBook.erase(toBeDeletedprice);
       }

       idToOrderMappingForBuy.erase(oid);    
       //stats
       activeBuyOrders--;
       ordersCancelled++;

       return 1;

    }
    else
    {
         if(idToOrderMappingForSell.count(oid)==0)
        {
            cout<<"No such id in sell order book currently\n";
            return 0;
        }
        
       cout<<"cancelled oid : "<<oid<<endl;
       double toBeDeletedprice=idToOrderMappingForSell[oid];

        //data model
       pricelevelToquantityMappingForSell[toBeDeletedprice]-=sellBook[toBeDeletedprice].getNodeForGivenId(oid)->order.quantity;

       totalSellQuantities-=sellBook[toBeDeletedprice].getNodeForGivenId(oid)->order.quantity;//also for stats
       sellBook[toBeDeletedprice].pop(oid);
       if(sellBook[toBeDeletedprice].isEmpty())
       {
        sellBook.erase(toBeDeletedprice);
       }
       idToOrderMappingForSell.erase(oid); 
       //stats
       activeSellOrders--;   
       ordersCancelled++;

       return 1;
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
void OrderBook::setVerbose(bool value)
{
    verbose=value;
}
int OrderBook::getTradesExecuted() const
{
    return trades.size();
}
int OrderBook::getTradedQuantity() const
{
    return totalTradedQuantity;
}
int OrderBook::getTradedValue() const
{
    return totalTradedValue;
}
int OrderBook::getActiveBuyOrders() const
{
    return activeBuyOrders;
}
int OrderBook::getActiveSellOrders() const
{
    return activeSellOrders;
}
int OrderBook::getBuyVolume() const
{
    return totalBuyQuantities;
}
int OrderBook::getSellVolume() const
{
    return totalSellQuantities;
}
int OrderBook::getBestBid() const
{
    if(buyBook.empty())
    {
        return 0;//i.e no best bid
    }
    else
    {
        auto bestBuy=buyBook.begin();
        return bestBuy->second.start().price;//highest buy price in order book
    }
}
int OrderBook::getBestAsk() const
{
    if(sellBook.empty())
    {
        return 0;//i.e no best Ask
    }
    else
    {
        auto bestSell=sellBook.begin();
        return bestSell->second.start().price;//lowest sell price in order book
    }
}
int OrderBook::getOrdersReceived() const
{
    return ordersReceived;
}
int OrderBook::getOrdersCancelled() const
{
    return ordersCancelled;
}

//verify Integrity
map<int,CustomLinkedQueue,greater<int> > OrderBook::getBuyBook()const{
    return buyBook;
}

map<int,CustomLinkedQueue > OrderBook::getSellBook()const{
    return sellBook;
}

//model data
OrderBookSnapshot OrderBook::getOrderBook() const{
    OrderBookSnapshot Obs;
    Obs.stockName=stockName;
    Obs.bestAsk=this->getBestAsk();
    Obs.bestBid=this->getBestBid();
    for(auto i:buyBook)
    {
        //each i is pricetoCustomQ mapping
        //this price must lie in price to its qty mapping
        int price=i.first;
        int totalQuantity=pricelevelToquantityMappingForBuy.at(price);
        
        PriceLevel Pl;
        Pl.priceLevel=price;
        Pl.quantity=totalQuantity;
        Obs.buyLevels.push_back(Pl);
        

        
    }
    for(auto i:sellBook)
    {
        //each i is pricetoCustomQ mapping
        //this price must lie in price to its qty mapping
        int price=i.first;
        int totalQuantity=pricelevelToquantityMappingForSell.at(price);
        
        PriceLevel Pl;
        Pl.priceLevel=price;
        Pl.quantity=totalQuantity;
        
        Obs.sellLevels.push_back(Pl);
        

        
    }
    return Obs;
}
TradeBook OrderBook::getTradeBook() const{
    TradeBook tb;
    
    tb.totalTrades=trades.size();
    tb.Trades=trades;
    return tb;
}

StatisticsBook OrderBook::getStatisticsBook()const{
    StatisticsBook sb;
    sb.totalTrades=trades.size();
    sb.activeBuyOrders=activeBuyOrders;
    sb.activeSellOrders=activeSellOrders;
    sb.bestAsk=this->getBestAsk();
    sb.bestBid=this->getBestBid();
    sb.buyVolume=totalBuyQuantities;
    sb.ordersCancelled=ordersCancelled;
    sb.ordersReceived=ordersReceived;
    sb.sellVolume=totalSellQuantities;
    sb.totalTradedQuantity=totalTradedQuantity;
    sb.totalTradedValue=totalTradedValue;
    return sb;
}