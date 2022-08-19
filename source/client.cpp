#include "client.h"

void Client::run()
{
    while(!is_game_over)
    {
        renderer.draw();
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
