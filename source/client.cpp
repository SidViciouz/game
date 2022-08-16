#include "client.h"

void Client::run()
{
    while(!is_game_over)
    {
        renderer.draw();// 따로 스레드를 분리해야할 수도 있음. 
    }
}

int main()
{
    try
    {
        Client client((char*)"127.0.0.1",1234);
        client.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
