#include "message.h"
/*
{
    subject: name(string)
    action: name(string)
    object: socket(int)
    at: position(Position{float,float,float})
    to: rotation(Rotation{float,float,float})
}
*/

void Message::process(vector<int>& client_sockets,char* message,int ident,map<string,Player>& players,Bullet_holder& bullet_holder,Time& time)
{
    Document d;
    d.Parse(message);

    if(d.HasParseError()) return;

    Value& subject = d["subject"];
    Value& action = d["action"];
    Value& object = d["object"];
    Value& at = d["at"];
    Value& to = d["to"];
    int message_type = 0;

    if(strcmp(action.GetString(),"move") == 0)
    {
        players[subject.GetString()].set_position({at[0].GetFloat(),at[1].GetFloat(),at[2].GetFloat()});
    }
    else if(strcmp(action.GetString(),"shot") == 0)
    {
        bullet_holder.create({at[0].GetFloat(),at[1].GetFloat(),at[2].GetFloat()},
        {to[0].GetFloat(),to[1].GetFloat(),to[2].GetFloat()},time.get_current_time());

        message_type = 1;
    }
    else if(strcmp(action.GetString(),"register") == 0)
    {
        printf("register!\n");
        players[subject.GetString()] = Player::create({0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},subject.GetString());

        for(auto it = players.begin(); it != players.end() ; it++)
        {
            printf("%s\n",it->second.get_name().c_str());
        }
    }
    
    broadcast(client_sockets,action.GetString(),players,bullet_holder,time,message_type);
}
void Message::broadcast(vector<int>& client_sockets,const char* action,map<string,Player>& players,Bullet_holder& bullet_holder,Time& time,int message_type)
{
    if(message_type == 0)
    {
        //players의 내용을 모든 플레이어에게 broadcast.
        for(auto it = players.begin(); it != players.end(); it++)
        {
            Position pos = it->second.get_position();

            for(auto client_socket : client_sockets)
            {
                send(client_socket,Message::make(it->first,(char*)action,0,{pos.x,pos.y,pos.z},{0,0,0}).GetString(),1024,0);
            }
        }
    }
    else if(message_type == 1)
    {
        int i=0;
        for(auto it = bullet_holder.begin(); it != bullet_holder.end(); it++)
        {
            Position pos = it->get_location();

            for(auto client_socket : client_sockets)
            {
                send(client_socket,Message::make(to_string(i),(char*)"shot_created",0,{pos.x,pos.y,pos.z},{0,0,0}).GetString(),1024,0);
            }
            ++i;
        }
    }
    
    bullet_holder.print();
    int i = 0;
    for(auto it = bullet_holder.begin(); it != bullet_holder.end(); it++)
    {
        Position pos = it->get_location();
        for(auto client_socket : client_sockets)
        {
            send(client_socket,Message::make(to_string(i),(char*)"shot",0,{pos.x,pos.y,pos.z},{0,0,0}).GetString(),1024,0);
        }
        ++i;
    }

}
StringBuffer Message::make(string subject,char* action,int object,Position at,Rotation to)
{
    
    Document d;
    Value array1(kArrayType);
    Value array2(kArrayType);
    Value s1;
    Value s2;
    Document::AllocatorType& allocator = d.GetAllocator();
    d.SetObject();

    s1.SetString(action,allocator);
    s2.SetString(subject.c_str(),allocator);
    array1.PushBack(at.x,allocator).PushBack(at.y,allocator).PushBack(at.z,allocator);
    array2.PushBack(to.yaw,allocator).PushBack(to.pitch,allocator).PushBack(to.roll,allocator);
    
    d.AddMember("subject",s2,allocator);
    d.AddMember("action",s1,allocator);
    d.AddMember("object",object,allocator);
    d.AddMember("at",array1,allocator);
    d.AddMember("to",array2,allocator);
    
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    d.Accept(writer);

    return strbuf;
}
