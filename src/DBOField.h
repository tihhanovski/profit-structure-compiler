#pragma once
#include <string>
#include "../lib/json/single_include/nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

class DBOField
{
public:
    string name, nameUpper, dbType, type, fkClass, defValuePas;
    int size;

    DBOField(json element);
    string getSCFieldDefinition();
    string getName();
    string getType();
    string getFkClass();
    string getSizeStr();
    string getDefValuePas();
};
