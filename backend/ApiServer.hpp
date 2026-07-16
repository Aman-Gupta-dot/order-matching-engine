#pragma once
#include "../engine/include/Exchange.hpp"

class ApiServer
{
    private:
        Exchange *exchange;
    
    public:

        ApiServer(Exchange *exchange);
        void start();


};