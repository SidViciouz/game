#include "client.h"

void Client::receive()
{
    char buffer[1024];
    int read_size = recv(socket.get_socket(),buffer,sizeof(buffer),0);
    if(read_size == -1) // get no message
    {
        return;
    }
    else if(read_size == 0)
    {
        close(socket.get_socket());
        runtime_error(string("lose connection!"));
    }
    else
    {
        //message 처리.
    }
}

void Client::run()
{
    while(!is_game_over)
    {
        input.send_change(socket.get_socket());
        receive();
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
