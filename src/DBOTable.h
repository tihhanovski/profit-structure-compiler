#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "util.h"
#include "../lib/json/single_include/nlohmann/json.hpp"

#include "DBOField.h"
#include "DBOMethod.h"
#include "DBObject.h"

/**
 * Table class
 */
class DBOTable : public DBObject
{
protected:
    string table, pk, className;    //DB table name, Primary key and class name
    int objId;  //obj id - used to identify document type in Profit
    vector<DBOMethod*> methods; //methods array
    vector<DBOField*> fields;   //fields array

    /**
     * 
     */
    void outputFieldVariables(ostream &o);
    void outputMethodInterface(ostream& o, DBOVisibility v);
    void outputMethodBodies(ostream& o);
    void generateSCHead(ostream &o);
    void addMethod(string signature, string body, DBOVisibility visibility = mvPublic);
    void addDoLoadMethod();


public:
    DBOTable(json j);
    void addClearMethod();
    void addSetFieldValueMethod();
    void addFieldEnumeratorMethod_fieldNr(
        string methodName,
        string (DBOField::* fn)(),
        string defaultResult = "",
        string (* quotationMethod)(string s) = &quotationMethodSingleQuoted
    );

    string getTable();
    string getPK();
    string getClassName();
    int getObjId();
    void outputInterface(ostream &o, DBOVisibility v);
    void generateSourceCode(ostream &o);
};
