#pragma once

#include <map>
#include "player.h"

using namespace std;

class Message
{

public:
    static void process(char* buffer,int ident,map<int,Player>& players);
    static void broadcast(map<int,Player>& players);
};