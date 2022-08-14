#include "message.h"

/*
{
    subject: socket(int)
    action: name(string)
    object: socket(int)
    at: position(Position{float,float,float})
}
*/

void Message::process(char* message,int ident,map<int,Player>& players)
{
    Document d;
    d.Parse(message);

    if(d.HasParseError()) return;

    Value& subject = d["subject"];
    Value& action = d["action"];
    Value& object = d["object"];
    Value& at = d["at"];

    if(strcmp(action.GetString(),"move") == 0)
    {
        float p[3];

        for(int i=0; i<3; ++i)
        {
            p[i] = at[i].GetFloat();
        }

        players[subject.GetInt()].set_position({p[0],p[1],p[2]});
    }
}
void Message::broadcast(vector<int>& client_sockets,map<int,Player>& players)
{
    //players의 내용을 모든 플레이어에게 broadcast.
    for(auto it = players.begin(); it != players.end(); it++)
    {
        Position pos = it->second.get_position();

        for(auto client_socket : client_sockets)
        {
            send(client_socket,Message::make(it->first,(char*)"move",0,{pos.x,pos.y,pos.z}),1024,0);
        }
    }
}
const char* Message::make(int subject,char* action,int object,Position at)
{
    
    Document d;
    Value array(kArrayType);
    Value s;
    Document::AllocatorType& allocator = d.GetAllocator();
    d.SetObject();

    s.SetString(action,allocator);
    array.PushBack(at.x,allocator).PushBack(at.y,allocator).PushBack(at.z,allocator);
    
    d.AddMember("subject",subject,allocator);
    d.AddMember("action",s,allocator);
    d.AddMember("object",object,allocator);
    d.AddMember("at",array,allocator);
    
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    d.Accept(writer);

    return strbuf.GetString();
}
