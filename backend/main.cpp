
#include "../engine/include/Exchange.hpp"
#include "ApiServer.hpp"

int main()
{
    Exchange exchange(true);//exchange created
    ApiServer server(&exchange);//server created
    server.start();//server started
    
    


    return 0;
}