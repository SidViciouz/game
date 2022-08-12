#include "server.h"

void Server::run()
{
    while(!is_game_over)
    {
        listening.wait(event_list);

        //event_list에 대한 처리
    }
}

int main(){

    try
    {
        Server my_server((char*)"127.0.0.1",1234,10);
        my_server.run();
    }
    catch(exception e)
    {
        cout << e.what() << "\n";
    }

    return 0;
}