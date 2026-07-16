#pragma once
#include "Order.hpp"
#include<unordered_map>
#include "Node.hpp"
using namespace std;


class CustomLinkedQueue
{
    private:
        Node*front;
        Node*rear;
        unordered_map<int,Node*>idToOrderMapping;//for a given id we can get its node address
        int size;
        int totalQuantity;//each queue total quantities present shd be stored
    public:
        
        CustomLinkedQueue();

        //we are not implementing all push and pop backs(doing only required once)
        void pushback(Order order);
        void popfront();
        void popback();

        void pop(int id);//pop this node at the given id,find address from id to address mapping

        Order& start() const;//return order at front
        Order& end() const;//return order at rear
        int isEmpty();//return if queue is empty or not

        int getSize() const;

        Node* getFront()const;
        Node* getRear()const;

        Node* getNodeForGivenId(int &id);

        int getTotalQuantity() const;

        unordered_map<int,Node*> getIdToOrderMapping() const;



};