#pragma once
#include <string>

using namespace std;

enum DBOVisibility {mvPrivate, mvProtected, mvPublic};
//enum DBOMethodType {mtConstructor, mvProcedure, mvFunction};

class DBOMethod
{
public:
    DBOVisibility visibility = mvPublic;
    string signature, body;
};
