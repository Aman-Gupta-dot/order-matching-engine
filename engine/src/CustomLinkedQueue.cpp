#include<iostream>
#include "../include/CustomLinkedQueue.hpp"
using namespace std;


CustomLinkedQueue::CustomLinkedQueue()
{
    front=NULL;
    rear=NULL;
    size=0;
    totalQuantity=0;
}

int CustomLinkedQueue::isEmpty()
{
    if(front ==NULL)return true;
    else return false;
}

int CustomLinkedQueue::getSize()const{
    return size;
}

Order& CustomLinkedQueue:: start() const
{
    return front->order;
}

Order& CustomLinkedQueue::end() const
{
    return rear->order;
}

void CustomLinkedQueue::pushback(Order order)
{
    size++;
    Node *newnode=new Node(order);
    totalQuantity+=order.quantity;
    idToOrderMapping[order.orderId]=newnode;//make entry
    if(rear==NULL)
    {
        front=newnode;
        rear=newnode;
    }
    else{
        rear->next=newnode;
        newnode->prev=rear;
        rear=rear->next;
    }
}
void CustomLinkedQueue::popback()
{
    size--;
    if(isEmpty())return;
    totalQuantity-=rear->order.quantity;
    idToOrderMapping.erase(end().orderId);
    if(front==rear)
    {
        Node*del=rear;
        front=NULL;
        rear=NULL;
        delete(del);

    }
    else{
        Node*del=rear;
        rear=rear->prev;
        rear->next=NULL;
        delete(del);
    }
    
}

void CustomLinkedQueue::popfront()
{ 
    size--;
    if(isEmpty())return;
    totalQuantity-=front->order.quantity;
    idToOrderMapping.erase(start().orderId);
    if(front==rear)
    {
        Node*del=front;
        front=NULL;
        rear=NULL;
        delete(del);

    }
    else{
        Node*del=front;
        front=front->next;
        front->prev=NULL;
        delete(del);
    }
}

void CustomLinkedQueue::pop(int id)
{
    //pop this given id
    if(id==start().orderId)
    {
        popfront();
    }
    else if(id==end().orderId)
    {
        popback();
    }
    else{
        if(idToOrderMapping.count(id)==1)
        {
            size--;
            Node*addr=idToOrderMapping[id];//pop this given address
            idToOrderMapping.erase(id);//remove this mapping from map

            totalQuantity-=addr->order.quantity;

            addr->prev->next=addr->next;
            addr->next->prev=addr->prev;
            delete(addr);
        }
        else{
            cout<<"\n No order placed from this id";
        }
    }
}

Node* CustomLinkedQueue::getFront() const
{
    return front;
}

Node* CustomLinkedQueue::getRear() const
{
    return rear;
}

Node* CustomLinkedQueue::getNodeForGivenId(int &id)
{
    return idToOrderMapping[id];
}

int CustomLinkedQueue::getTotalQuantity() const{
    return totalQuantity;
}
unordered_map<int,Node*> CustomLinkedQueue:: getIdToOrderMapping() const{
    return idToOrderMapping;
}
