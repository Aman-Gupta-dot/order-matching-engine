
#include "../engine/include/Exchange.hpp"
#include "ApiServer.hpp"

int main()
{
    Exchange exchange(false);//exchange created
    ApiServer server(&exchange);//server created
    server.start();//server started
    
    


    return 0;
}