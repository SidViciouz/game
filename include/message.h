#pragma once

#include <map>
#include <vector>
#include "player.h"
#include <string>
#include <cstring>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <sys/socket.h>
#include "bullet.h"
#include "my_time.h"

using namespace std;
using namespace rapidjson;

class Message
{

public:
    static void process(vector<int>& client_sockets,char* message,int ident,map<string,Player>& players,Bullet_holder& bullet_holder,Time& time);
    static void broadcast(vector<int>& client_sockets,const char* action,map<string,Player>& players,Bullet_holder& bullet_holder,Time& time,int message_type);
    static StringBuffer make(string subject,char* action,int object,Position at,Rotation to);
};