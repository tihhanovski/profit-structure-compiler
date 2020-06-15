#pragma once
#include <string>
#include <iostream>
#include "../lib/json/single_include/nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

class DBObject
{
protected:
    json j;
    string type;
public:
    DBObject(json j);
    void generateSourceCode(ostream& o);
    string getType();
};
