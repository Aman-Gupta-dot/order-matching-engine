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

                cout<<"plz enter 5 to go back"<<endl;

                cout<<"Plz enter your choice : ";
                cin>>choice2;
                cout<<endl;

                if(choice2==1)
                {
                    system("cls");
                    Order order;
                    order.orderId=++buyid;
                    order.timeStamp=++timestamp;
                    order.stockName=orderBook.getStockName();
                    order.side=BuyOrSell::BUY;
                    cout<<"plz enter the quantity you want to buy: ";
                    cin>>order.quantity;
                    cout<<endl;

                    cout<<"plz enter your atmost buying price: ";
                    cin>>order.price;
                    cout<<endl;

                    orderBook.placeOrder(order);
                }
                else if(choice2==2)
                {
                    system("cls");
                    Order order;
                    order.orderId=++sellid;
                    order.timeStamp=++timestamp;
                    order.stockName=orderBook.getStockName();
                    order.side=BuyOrSell::SELL;
                    cout<<"plz enter the quantity you want to sell: ";
                    cin>>order.quantity;
                    cout<<endl;

                    cout<<"plz enter your atleast selling price: ";
                    cin>>order.price;
                    cout<<endl;
                    
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