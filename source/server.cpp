#include "server.h"

void Server::run()
{
    while(!is_game_over)
    {
        listening.wait(event_list);

        //event_list에 대한 처리
        for(auto it = event_list.first(); it != event_list.end(); it++)
        {
            if(it->ident == listening_socket.get_socket())
            {
                int client = accept(listening_socket.get_socket(),NULL,NULL);
                if(client == -1)
                {
                    throw runtime_error(string("accept error!"));
                }
                listening.add(client,EVFILT_READ);
                listening.add(client,EVFILT_WRITE);
            }
            else if(it->filter == EVFILT_READ)
            {
                char buffer[1024];
                int read_size = recv(it->ident,buffer,sizeof(buffer),0);
                if(read_size != -1 && read_size != 0)
                {
                    printf("%d[%d] : %s\n",it->ident,read_size,buffer);
                }
            }
        }
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