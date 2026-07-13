#include "../include/Node.hpp"

Node::Node(Order order)
{
    this->order=order;
    prev=NULL;
    next=NULL;
}