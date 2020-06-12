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
public:
    PascalTypesLibrary();
    PascalTypesLibrary(PascalTypesLibrary &other) = delete;
    void operator=(const PascalTypesLibrary &) = delete;
    static PascalTypesLibrary* GetInstance();

    string getPascalTypeName(string dbName);
};

PascalTypesLibrary* PascalTypesLibrary::singleton_= nullptr;

PascalTypesLibrary* PascalTypesLibrary::GetInstance()
{
    if(singleton_==nullptr)
        singleton_ = new PascalTypesLibrary();
    return singleton_;
}

string PascalTypesLibrary::getPascalTypeName(string dbName)
{
    string ret = dbName;
    boost::to_upper(ret);
    try
    {
        j[ret]["namePas"].get_to(ret);
        return ret;
    }
    catch(std::exception& e)
    {
        return dbName + "// error founding type for this name";
    }
}

PascalTypesLibrary::PascalTypesLibrary()
{
    ifstream i(TYPES_FILE);
    i >> j;
    i.close();
}


string getPascalTypeName(string dbName)
{
    return PascalTypesLibrary::GetInstance()->getPascalTypeName(dbName);
}
