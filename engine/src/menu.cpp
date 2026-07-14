#include<iostream>
#include "../include/menu.hpp"
#include "../include/Exchange.hpp"

using namespace std;

void callMenu()
{
    cout<<"Welcome to Our Order Matching Engine\n";
    int overallId=1000;
    
    int overallTimeStamp=0;
    Exchange exchange(true);
    while(true)
    {
        cout<<"================Order Matching Engine================\n";
        cout<<"1.Place Order\n";
        cout<<"2.Cancel Order\n";
        cout<<"3.View Order Book\n";
        cout<<"4.View Trades\n";
        cout<<"5.Exit\n";

        int choice;
        cout<<"Please enter your choice : ";
        cin>>choice;
        cout<<endl;

        system("cls");

        string choice2;
        cout<<"Please enter stock name";
        getline(cin >> ws, choice2);
        if(choice==1)//place order
        {
            Order order;
            order.orderId=++overallId;
            order.stockName=choice2;
            int choice3;
            cout<<"Please enter side(1 for Buy),(2 For Sell) default or invalid-->BUY : ";
            cin>>choice3;
            cout<<endl;
            if(choice3==2) order.side=BuyOrSell::SELL;
            else order.side=BuyOrSell::BUY;
            cout<<endl;

            int choice4;
            cout<<"Please enter Order Type\n";
            cout<<"1.LIMIT\n";
            cout<<"2.MARKET\n";
            cout<<"3.FOK\n";
            cout<<"4.IOC\n";
            cout<<"Please enter(Limit by default for invalid choice) : ";
            cin>>choice4;
            cout<<endl;
            if(choice4==2)
            {
                order.type=OrderType::MARKET;
            }
            else if(choice4==3)
            {
                order.type=OrderType::FOK;
            }
            else if(choice4==4)
            {
                order.type=OrderType::IOC;
            }
            else
            {
                order.type=OrderType::LIMIT;
            }


            if(choice4!=2)//price not required for market order
            {
                cout<<"Please enter price : ";
                cin>>order.price;
                cout<<endl;
            }

            cout<<"Please enter quantity : ";
            cin>>order.quantity;
            cout<<endl;

            order.timeStamp=++overallTimeStamp;

            //Order ready
            exchange.placeOrder(order);
   
        }
        else if(choice==2)//cancel order
        {
            int cancelId;
            cout<<"Please Enter Id you want to delete\n";
            cin>>cancelId;

            int choice3;
            cout<<"Please enter side(1 for Buy),(2 For Sell) default or invalid-->BUY : ";
            if(choice3==2)
            {
                exchange.cancelOrder(cancelId,choice2,BuyOrSell::SELL);
            }
            else exchange.cancelOrder(cancelId,choice2,BuyOrSell::BUY);
            cout<<endl;


        }
        else if(choice==3)
        {
            exchange.viewOrderBook(choice2);
        }
        else if(choice==4)
        {
            exchange.showTrades(choice2);
        }
        else{
            cout<<"Thank you so much for using our engine\n";
            return;
        }
    }
}