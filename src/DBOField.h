#pragma once
#include <string>
#include "../lib/json/single_include/nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

/**
 * DB object field definition
 */
class DBOField
{
public:
    string name, nameUpper, dbType, type, fkClass, defValuePas;
    int size;

    /**
     * Constructs field from JSON object
     */
    DBOField(json element);

    /**
     * Returns field def for source code
     */
    string getSCFieldDefinition();

    /**
     * Returns field name
     */
    string getName();

    /**
     * Returns field type
     */
    string getType();

    /**
     * Returns field Foreign key type
     */
    string getFkClass();

    /**
     * Returns field size as string, need it for DBOTable::addFieldEnumeratorMethod_fieldNr magic
     */
    string getSizeStr();


    /**
     * Returns field default value
     */
    string getDefValuePas();
};
