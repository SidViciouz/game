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
    static void process(char* message,int ident,map<int,Player>& players,Bullet_holder& bullet_holder,Time& time);
    static void broadcast(vector<int>& client_sockets,map<int,Player>& players,Bullet_holder& bullet_holder,Time& time);
    static StringBuffer make(int subject,char* action,int object,Position at,Rotation to);
};