#pragma once
#include <string>
#include "../lib/json/single_include/nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

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
    void init(string typesFile);
};

string getPascalDefValue(string dbTypeName);
string getPascalTypeName(string dbName);
