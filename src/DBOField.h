#pragma once
#include <string>
#include <limits>
#include <vector>
#include "../lib/json/single_include/nlohmann/json.hpp"

#include "util.h"
#include <boost/algorithm/string.hpp>

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
