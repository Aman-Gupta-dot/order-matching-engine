#include<iostream>
#include "../include/OrderBook.hpp"
#include "../include/menu.hpp"

using namespace std;

int main()
{

    OrderBook *orderBook=new OrderBook("DairyMilk");

    
    // create an order
    // Order order1;
    // order1.orderId=++buyOrderId;
    // order1.side=BuyOrSell::BUY;
    // order1.price=100;
    // order1.quantity=1;
    // order1.stockName=orderBook.getStockName();
    // order1.timeStamp=++overalltimestamp;
    // orderBook->placeOrder(order1);

    // Order order2;
    // order2.orderId=++buyOrderId;
    // order2.side=BuyOrSell::BUY;
    // order2.price=105;
    // order2.quantity=2;
    // order2.stockName=orderBook->getStockName();
    // order2.timeStamp=++overalltimestamp;
    // orderBook->placeOrder(order2);

    // Order order3;
    // order3.orderId=++buyOrderId;
    // order3.side=BuyOrSell::BUY;
    // order3.price=110;
    // order3.quantity=3;
    // order3.stockName=orderBook->getStockName();
    // order3.timeStamp=++overalltimestamp;
    // orderBook->placeOrder(order3);

    // Order order4;
    // order4.orderId=++buyOrderId;
    // order4.side=BuyOrSell::BUY;
    // order4.price=100;
    // order4.quantity=4;
    // order4.stockName=orderBook->getStockName();
    // order4.timeStamp=++overalltimestamp;

    
    // orderBook->placeOrder(order4);

    //  Order order5;
    // order5.orderId=++sellOrderId;
    // order5.side=BuyOrSell::SELL;
    // order5.price=95;
    // order5.quantity=10;
    // order5.stockName=orderBook->getStockName();
    // order5.timeStamp=++overalltimestamp;

    // orderBook->placeOrder(order5);

    // orderBook->showOrderBook();
    // orderBook->showTrades();

    //now lets do it menu based

    vector<pair<int,string>>choiceAndName{{1,"DairyMilk"},{2,"5-star"},{3,"Ferrero Rocher"},{4,"Kinder Joy"}};

    int buyOrderId=100;
    int sellOrderId=200;
    int overalltimestamp=0;
    OrderBook orderBookdm("Dairy Milk");
    OrderBook orderBook5s("5-star");
    OrderBook orderBookFr("Ferrero Rocher");
    OrderBook orderBookKj("Kinder Joy");

    while(true)
    {
        
        cout<<"--------------Welcome to our Order Matcher-------------\n";
        int choice;
        cout<<"--------------------------MENU--------------------------\n";
        cout<<"Different Chocolates on our platform: \n";
        for(int i=0;i<choiceAndName.size();i++)
        {
            cout<<choiceAndName[i].first<<":"<<choiceAndName[i].second<<endl;
        }

        cout<<"For-exit plz press 5 in choice\n";

        cout<<"Please enter your choice : ";
        cin>>choice;
        cout<<endl;

        if(choice==1)
        {
            
            system("cls");
            callMenu(orderBookdm,buyOrderId,sellOrderId,overalltimestamp);
            

        }
        else if(choice==2)
        {
            system("cls");
            callMenu(orderBook5s,buyOrderId,sellOrderId,overalltimestamp);

        }
        else if(choice==3)
        {
            system("cls");
            callMenu(orderBookFr,buyOrderId,sellOrderId,overalltimestamp);
            
        }
        else if(choice==4)
        {
            system("cls");
            callMenu(orderBookKj,buyOrderId,sellOrderId,overalltimestamp);
            
        }
        else if(choice==5)
        {
            system("cls");
            cout<<"Thank you so much for using our engine"<<endl;
            break;
        }
        else{
            system("cls");
            cout<<"Invalid Choice"<<endl;
        }     
    }


}
