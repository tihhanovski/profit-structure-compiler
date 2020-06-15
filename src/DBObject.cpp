#include <string>
#include "util.h"
#include "../lib/json/single_include/nlohmann/json.hpp"

#include "DBObject.h"

using namespace std;
using nlohmann::json;

DBObject::DBObject(json j)
{
    this->j = j;
    j["type"].get_to(type);
}

void DBObject::generateSourceCode(ostream& o)
{
    o << "//" << getType();
}

string DBObject::getType()
{
    return type;
}
