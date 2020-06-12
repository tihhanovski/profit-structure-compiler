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
    string name, nameUpper, dbType, type;

    DBOField(json element)
    {
        element["name"].get_to(name);
        element["type"].get_to(dbType);
        nameUpper = name;
        boost::to_upper(nameUpper);
        boost::to_lower(name);
        type = getPascalTypeName(dbType);
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
};
