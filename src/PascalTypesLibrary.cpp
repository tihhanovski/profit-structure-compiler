#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "util.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
#include "PascalTypesLibrary.h"

using namespace std;
using nlohmann::json;

const string TYPES_FILE = "../samples/types.json";

PascalTypesLibrary* PascalTypesLibrary::singleton_= nullptr;

PascalTypesLibrary* PascalTypesLibrary::GetInstance()
{
    if(singleton_==nullptr)
        singleton_ = new PascalTypesLibrary();
    return singleton_;
}


string PascalTypesLibrary::getTypeProperty(string dbTypeName, string propName, string defaultValue)
{
    string ret = dbTypeName;
    toUpper(ret);
    try
    {
        j[ret][propName].get_to(ret);
        return ret;
    }
    catch(std::exception& e)
    {
        return defaultValue; //error
    }
}

string PascalTypesLibrary::getPascalTypeName(string dbName)
{
    return getTypeProperty(dbName, "namePas", dbName + "// error founding type for this name");
}

string PascalTypesLibrary::getPascalDefValue(string dbTypeName)
{
    return getTypeProperty(dbTypeName, "defValuePas", "{** error!}");
}

PascalTypesLibrary::PascalTypesLibrary()
{
    ifstream i(TYPES_FILE);
    i >> j;
    i.close();
}

string getPascalDefValue(string dbTypeName)
{
    return PascalTypesLibrary::GetInstance()->getPascalDefValue(dbTypeName);
}

string getPascalTypeName(string dbName)
{
    return PascalTypesLibrary::GetInstance()->getPascalTypeName(dbName);
}
