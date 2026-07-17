#include<iostream>
using namespace std;
#include "../include/VerifyIntegrity.hpp"
#include "../include/Exchange.hpp"

bool VerifyIntegrity::checkQueue(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook)
{
    //check 1
    //for every queue if q not empty(definitely not be) front->prev=Null and rear->next=null
    bool check=true;
    for(auto it:buyBook)
    {
        CustomLinkedQueue &que=it.second;
        if(que.getFront()->prev!=NULL || que.getRear()->next!=NULL)
        {
            check=false;
            cout<<"\nError!!\n";
            cout<<"front->prev and rear->next are not NULL for some customLinkedQueue foR buyBook\n";
            //no return as we should diagnose all errors
        }

        //check 2 
        //for each queue traverse fully and nodecount shd be equal to que.getsizE()
        Node*temp=que.getFront();
        int count=0;
        while(temp!=nullptr)
        {
            count++;
            temp=temp->next;
        }
        if(count!=que.getSize())
        {
            check=false;
            cout<<"\nError!!\n";
            cout<<"No of nodes in queue are not equal to,as found by getSize() function for buybook\n";
        }

        //check 3
        //every next->prev shd point back crctly next not null
        temp=que.getFront();
        while(temp->next!=nullptr)
        {
            if(temp->next->prev!=temp)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"prev->next not pointing to current node for buybook";
            }
            temp=temp->next;
        }


    }

     for(auto it:sellBook)
    {
        CustomLinkedQueue &que=it.second;
        if(que.getFront()->prev!=NULL || que.getRear()->next!=NULL)
        {
            check=false;
            cout<<"\nError!!\n";
            cout<<"front->prev and rear->next are not NULL for some customLinkedQueue for sellBook\n";
            //no return as we should diagnose all errors
        }
        Node*temp=que.getFront();
        int count=0;
        while(temp!=nullptr)
        {
            count++;
            temp=temp->next;
        }
        if(count!=que.getSize())
        {
            check=false;
            cout<<"\nError!!\n";
            cout<<"No of nodes in queue are not equal to,as found by getSize() function for sellbook\n";
        }

        temp=que.getFront();
        while(temp->next!=nullptr)
        {
            if(temp->next->prev!=temp)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"prev->next not pointing to current node for buybook";
            }
            temp=temp->next;
        }
    }
    return check;

}

bool VerifyIntegrity::checkPriceLevels(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook)
{
    //for every pricelevel for all nodes in queue shd have same price
    bool check=true;
    for(auto i:buyBook)
    {
        int actualPrice=i.first;
        CustomLinkedQueue &que=i.second;
        Node*temp=que.getFront();

        while(temp!=NULL)
        {
            if(temp->order.price!=actualPrice)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"for a particular pricelevel a queue should have same price for all nodes"<<
                ",This property is violated here for buyBook\n";
                break;
            }
            temp=temp->next;
        }
    }

    for(auto i:sellBook)
    {
        int actualPrice=i.first;
        CustomLinkedQueue &que=i.second;
        Node*temp=que.getFront();

        while(temp!=NULL)
        {
            if(temp->order.price!=actualPrice)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"for a particular pricelevel a queue should have same price for all nodes"<<
                ",This property is violated here for sellBook\n";
                break;
            }
            temp=temp->next;
        }
    }
    return check;
}

bool VerifyIntegrity::checkOrderBook(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook,int totalBuyQuantities,int totalSellQuantities,int activeBuyOrders,int activeSellOrders)
{
    //check 1
    //sum(all buy qts in order book) must be equal to totalBuyQts
    bool check=true;
    int checkTotalBuyQuantities=0;
    int totalOrders=0;
    for(auto i:buyBook)
    {
        CustomLinkedQueue &que=i.second;
        Node*temp=que.getFront();

        while(temp!=NULL)
        {
            checkTotalBuyQuantities+=temp->order.quantity;
            temp=temp->next;
        }

         //check 2
        //sum(queue) sizes must equal ActiveBuyOrders
        
            totalOrders+=que.getSize();
        

        

    }
    if(checkTotalBuyQuantities!=totalBuyQuantities)
    {
        check=false;
        cout<<"\nError!!\n";
        cout<<"total buy qts calculated are not equal to actually calculated for buybook\n";
    }

    if(totalOrders!=activeBuyOrders)
    {
        check=false;
        cout<<"\nError!!\n";
        cout<<"Active buy orders from stats not equal when calculated for buybook\n";
    }

    int checkTotalSellQuantities=0;
    totalOrders=0;
    for(auto i:sellBook)
    {
        CustomLinkedQueue &que=i.second;
        Node*temp=que.getFront();

        while(temp!=NULL)
        {
            checkTotalSellQuantities+=temp->order.quantity;
            temp=temp->next;
        }

        //check 2
        //sum(queue) sizes must equal ActiveBuyOrders
            totalOrders+=que.getSize();
        
    }
    if(checkTotalSellQuantities!=totalSellQuantities)
    {
        check=false;
        cout<<"\nError!!\n";
        cout<<"total buy qts calculated are not equal to actually calculated for sellbook\n";
    }
    if(totalOrders!=activeSellOrders)
    {
        check=false;
        cout<<"\nError!!\n";
        cout<<"Active buy orders from stats not equal when calculated for sellbook\n";
    }
    
    return check;
}

bool VerifyIntegrity::checkMapping(map<int,CustomLinkedQueue,greater<int> >&buyBook,map<int,CustomLinkedQueue >&sellBook)
{
    bool check=true;
    //check1
    //for every node order id must exist in idToOrderMapping and mapped price must equal order.price
    for(auto i:buyBook)
    {
        CustomLinkedQueue &que=i.second;
        const unordered_map<int,Node*> &mapping=que.getIdToOrderMapping();
        Node*temp=que.getFront();
        while(temp!=NULL)
        {
            if(mapping.count(temp->order.orderId)==0)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"id not present in idtoOrderMapping but it exists in current buyBook";
                break;

            }
            temp=temp->next;
        }
        temp=que.getFront();
        while(temp!=NULL)
        {
            if(mapping.count(temp->order.orderId) && mapping.at(temp->order.orderId)->order.price!=temp->order.price)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"mapped price in idToOrderMapping not equal to actualPrice for buybook\n";
                break;
            }
            temp=temp->next;
        }
    }
    for(auto i:sellBook)
    {
        CustomLinkedQueue &que=i.second;
        Node*temp=que.getFront();
        const unordered_map<int,Node*> &mapping=que.getIdToOrderMapping();
        while(temp!=NULL)
        {
            if(mapping.count(temp->order.orderId)==0)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"id not present in idtoOrderMapping but it exists in current sellBook";
                break;

            }
            temp=temp->next;
        }
        temp=que.getFront();
        while(temp!=NULL)
        {
            if(mapping.count(temp->order.orderId) && mapping.at(temp->order.orderId)->order.price!=temp->order.price)
            {
                check=false;
                cout<<"\nError!!\n";
                cout<<"mapped price in idToOrderMapping not equal to actualPrice for buybook\n";
                break;
            }
            temp=temp->next;
        }
    }
    return check;
}

int VerifyIntegrity::checkExchange(Exchange *exchange)
{
    int overallcheck=1;
    const unordered_map<string,OrderBook>&books=exchange->getBooks();
    for(auto i:books)
    {
        // cout<<"Verifying Integrity for : "<<i.second.getStockName()<<endl;
        // cout<<"\n";

        // cout<<"1. Checking Queue Integrity......\n";
         map<int,CustomLinkedQueue,greater<int> >buyBook=i.second.getBuyBook();
         map<int,CustomLinkedQueue >sellBook=i.second.getSellBook();

        bool check=checkQueue(buyBook,sellBook);
        if(check!=true) 
        {
        // cout<<"Queue Check:Failed\n";
        overallcheck=false;

        }

        // cout<<"\n2. Checking Price Level Integrity......\n";
        check=checkPriceLevels(buyBook,sellBook);
        if(check!=true)
        { 
            // cout<<"Price Level Check:Failed\n";
            overallcheck=false;
        }

        
        check=checkOrderBook(buyBook,sellBook,i.second.getBuyVolume(),i.second.getSellVolume(),i.second.getActiveBuyOrders(),i.second.getActiveSellOrders());
        if(check!=true)
        {
            // cout<<"Order Book Check:Failed\n";
            overallcheck=false;

        }

        
        check=checkMapping(buyBook,sellBook);
        if(check!=true) 
        {
        // cout<<"Id Mapping Check:Failed\n";
        overallcheck=false;

        }







    }
    return overallcheck;
}



