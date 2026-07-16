#pragma once
#include "Order.hpp"

class Node{
    public:
        Order order;
        Node*next;
        Node*prev;
        Node(Order order);


};
 