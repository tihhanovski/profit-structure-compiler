#include <string>
#include <limits>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "../lib/json/single_include/nlohmann/json.hpp"
#include "PascalTypesLibrary.h"
#include "DBOField.h"

using namespace std;
using nlohmann::json;

DBOField::DBOField(json element)
{
    element["name"].get_to(name);
    element["type"].get_to(dbType);
    nameUpper = name;
    boost::to_upper(nameUpper);
    boost::to_lower(name);
    type = getPascalTypeName(dbType);
    defValuePas = getPascalDefValue(dbType);
    try
    {
        element["fkClassName"].get_to(fkClass);
        boost::to_lower(fkClass);
    }
    catch(std::exception& e)
    {
        //ignore exception and set class to ""
        fkClass = "";
    }

    try
    {
        element["size"].get_to(size);
    }
    catch(std::exception& e)
    {
        //ignore exception and set size to
        size = 0;
    }
}

string DBOField::getSCFieldDefinition()
{
    return name + ": " + type + ";";
}

string DBOField::getName()
{
    return name;
}

string DBOField::getType()
{
    return type;
}

string DBOField::getFkClass()
{
    return fkClass;
}

string DBOField::getSizeStr()
{
    //need this to "map-reduce" magic in DBObject
    return to_string(size);
}

string DBOField::getDefValuePas()
{
    return defValuePas;
}
