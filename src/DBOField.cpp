#include <string>
#include <limits>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "../lib/json/single_include/nlohmann/json.hpp"
#include "dbtypes.cpp"

using namespace std;
using nlohmann::json;

class DBOField
{
public:
    string name, nameUpper, dbType, type, fkClass;
    int size;

    DBOField(json element)
    {
        element["name"].get_to(name);
        element["type"].get_to(dbType);
        nameUpper = name;
        boost::to_upper(nameUpper);
        boost::to_lower(name);
        type = getPascalTypeName(dbType);
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

    string getSCFieldDefinition()
    {
        return name + ": " + type + ";";
    }

    string getName()
    {
        return name;
    }

    string getType()
    {
        return type;
    }

    string getFkClass()
    {
        return fkClass;
    }

    string getSizeStr()
    {
        //need this to "map-reduce" magic in DBObject
        return to_string(size);
    }
};
