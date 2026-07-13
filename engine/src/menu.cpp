#include<iostream>
#include "../include/menu.hpp"

using namespace std;

void callMenu(OrderBook &orderBook,int &buyid,int &sellid,int &timestamp)
{
    
    while(true)
            {
                
                int choice2;
                cout<<"-----MENU-----"<<endl;
                cout<<"1.Place buy order : "<<endl;
                cout<<"2.Place sell order : "<<endl;
                cout<<"3.View order book : "<<endl;
                cout<<"4.View Trade History : "<<endl;
                cout<<"5.Delete ur order if not executed(with orderid if it exists)";

                cout<<"plz enter 6 to go back"<<endl;

                cout<<"Plz enter your choice : ";
                cin>>choice2;
                cout<<endl;

                if(choice2==1)
                {
                    system("cls");
                    int orderTypeInNumberAsChoice;
                    cout<<"press 1 for Limit Order ,2 For Market Order\n";
                    cin>>orderTypeInNumberAsChoice;
                    cout<<endl;

                    Order order;
                    if(orderTypeInNumberAsChoice==1)
                    {
                        order.type=OrderType::LIMIT;
                    }
                    else if(orderTypeInNumberAsChoice==2)
                    {
                        order.type=OrderType::MARKET;
                    }
                    else{
                        //default
                        order.type=OrderType::LIMIT;
                    }
                    order.orderId=++buyid;
                    order.timeStamp=++timestamp;
                    order.stockName=orderBook.getStockName();
                    order.side=BuyOrSell::BUY;
                    cout<<"plz enter the quantity you want to buy: ";
                    cin>>order.quantity;
                    cout<<endl;

                    
                    if(orderTypeInNumberAsChoice==1)
                    {
                        cout<<"plz enter your atmost buying price: ";
                        cin>>order.price;
                        cout<<endl;
                    }

                    orderBook.placeOrder(order);
                }
                else if(choice2==2)
                {
                    system("cls");
                    int orderTypeInNumberAsChoice;
                    cout<<"press 1 for Limit Order ,2 For Market Order\n";
                    cin>>orderTypeInNumberAsChoice;
                    cout<<endl;
                    
                    Order order;
                    if(orderTypeInNumberAsChoice==1)
                    {
                        order.type=OrderType::LIMIT;
                    }
                    else if(orderTypeInNumberAsChoice==2)
                    {
                        order.type=OrderType::MARKET;
                    }
                    else{
                        //default
                        order.type=OrderType::LIMIT;
                    }
                    order.orderId=++sellid;
                    order.timeStamp=++timestamp;
                    order.stockName=orderBook.getStockName();
                    order.side=BuyOrSell::SELL;
                    cout<<"plz enter the quantity you want to sell: ";
                    cin>>order.quantity;
                    cout<<endl;

                    if(orderTypeInNumberAsChoice==1)
                    {
                        cout<<"plz enter your atleast selling price: ";
                        cin>>order.price;
                        cout<<endl;
                    }
                    
                    orderBook.placeOrder(order);

                }
                else if(choice2==3)
                {
                    system("cls");
                    orderBook.showOrderBook();
                }
               else if(choice2==4)
                {
                    system("cls");
                    orderBook.showTrades();
                }
                else if(choice2==5)
                {
                    
                    cout<<"what kind of order you want to delete:(Press 1 for buy),(2 for sell) : ";
                    int num;
                    cin>>num;
                    cout<<endl;
                    int oid;
                    cout<<"enter order id to delete : ";
                    cin>>oid;
                    cout<<endl;
                    if(num==1)
                    {
                        //delete buy order
                        orderBook.deleteOrder(oid,BuyOrSell::BUY);
                    }
                    else if(num==2)
                    {
                        orderBook.deleteOrder(oid,BuyOrSell::SELL);
                    }
                    else{
                        cout<<"Invalid choice\n";
                    }

                }
                else if(choice2==6)
                {
                    system("cls");
                    break;
                }
                else
                {
                    system("cls");
                    cout<<"Invalid choice"<<endl;
                }
            }
}