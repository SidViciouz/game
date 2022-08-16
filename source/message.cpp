#include "message.h"
/*
{
    subject: socket(int)
    action: name(string)
    object: socket(int)
    at: position(Position{float,float,float})
    to: rotation(Rotation{float,float,float})
}
*/

void Message::process(char* message,int ident,map<int,Player>& players,Bullet_holder& bullet_holder,Time& time)
{
    Document d;
    d.Parse(message);

    if(d.HasParseError()) return;

    Value& subject = d["subject"];
    Value& action = d["action"];
    Value& object = d["object"];
    Value& at = d["at"];
    Value& to = d["to"];

    if(strcmp(action.GetString(),"move") == 0)
    {
        players[subject.GetInt()].set_position({at[0].GetFloat(),at[1].GetFloat(),at[2].GetFloat()});
    }
    else if(strcmp(action.GetString(),"shot") == 0)
    {
        bullet_holder.create({at[0].GetFloat(),at[1].GetFloat(),at[2].GetFloat()},
        {to[0].GetFloat(),to[1].GetFloat(),to[2].GetFloat()},time.get_current_time());
    }
}
void Message::broadcast(vector<int>& client_sockets,map<int,Player>& players,Bullet_holder& bullet_holder,Time& time)
{
    //players의 내용을 모든 플레이어에게 broadcast.
    for(auto it = players.begin(); it != players.end(); it++)
    {
        Position pos = it->second.get_position();

        for(auto client_socket : client_sockets)
        {
            send(client_socket,Message::make(it->first,(char*)"move",0,{pos.x,pos.y,pos.z},{0,0,0}),1024,0);
        }
    }
    bullet_holder.print();

}
const char* Message::make(int subject,char* action,int object,Position at,Rotation to)
{
    
    Document d;
    Value array1(kArrayType);
    Value array2(kArrayType);
    Value s;
    Document::AllocatorType& allocator = d.GetAllocator();
    d.SetObject();

    s.SetString(action,allocator);
    array1.PushBack(at.x,allocator).PushBack(at.y,allocator).PushBack(at.z,allocator);
    array2.PushBack(to.yaw,allocator).PushBack(to.pitch,allocator).PushBack(to.roll,allocator);
    
    d.AddMember("subject",subject,allocator);
    d.AddMember("action",s,allocator);
    d.AddMember("object",object,allocator);
    d.AddMember("at",array1,allocator);
    d.AddMember("to",array2,allocator);
    
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    d.Accept(writer);

    return strbuf.GetString();
}
