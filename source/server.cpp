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
                // 클라이언트의 연결을 받고, kqueue에 추가하는 과정.
                int client = accept(listening_socket.get_socket(),NULL,NULL);
                if(client == -1)
                {
                    throw runtime_error(string("accept error!"));
                }
                listening.add(client,EVFILT_READ);
                listening.add(client,EVFILT_WRITE);

                //플레이어를 추가하는 과정.
                players[client] = Player::create({0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},string("player")+to_string(client));
                
                for(auto it = players.begin(); it != players.end() ; it++)
                {
                    printf("%s\n",it->second.get_name().c_str());
                }
                
            }
            else if(it->filter == EVFILT_READ)
            {
                char buffer[1024];
                int read_size = recv(it->ident,buffer,sizeof(buffer),0);
                if(read_size != -1 && read_size != 0) // -1인 경우는 받은 메세지가 없는 경우.
                // 0인 경우는 연결이 종료된 경우. 이 둘을 따로 처리하는 것으로 수정해야 함.
                {
                    printf("%s[%d] : %s\n",players[it->ident].get_name().c_str(),read_size,buffer);
                }

                //메세지 해석해서 처리해야함.
                Message::process(buffer,it->ident,players);
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