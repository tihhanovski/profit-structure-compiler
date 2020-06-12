#include <string>
#include "../lib/json/single_include/nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

const string TYPES_FILE = "../samples/types.json";

class PascalTypesLibrary
{
private:
    json j;

protected:
    static PascalTypesLibrary* singleton_;
    string getTypeProperty(string dbTypeName, string propName, string defaultValue);

public:
    PascalTypesLibrary();
    PascalTypesLibrary(PascalTypesLibrary &other) = delete;
    void operator=(const PascalTypesLibrary &) = delete;
    static PascalTypesLibrary* GetInstance();

    string getPascalTypeName(string dbName);
    string getPascalDefValue(string dbTypeName);
};

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
    boost::to_upper(ret);
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
