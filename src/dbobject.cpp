#include <string>
#include <limits>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "../lib/json/single_include/nlohmann/json.hpp"
#include "DBOMethod.cpp"
#include "DBOField.cpp"

using namespace std;
using nlohmann::json;

const string SC_TAB = "    ";

string quotationMethodNoQuotation(string s);
string quotationMethodSingleQuoted(string s);

class DBObject
{
protected:
    json j;
    string type;
public:

    DBObject(json j)
    {
        this->j = j;
        j["type"].get_to(type);
    }

    void generateSourceCode(ostream& o)
    {
        o << "//" << getType();
    }

    string getType()
    {
        return type;
    }
};

class DBOTable : public DBObject
{
protected:
    string table, pk, className;
    int objId;
    vector<DBOMethod*> methods;
    vector<DBOField*> fields;

    void outputFieldVariables(ostream &o)
    {
        //TODO!
        for(DBOField* f : fields)
            o << SC_TAB << SC_TAB << f->getSCFieldDefinition() << endl;
    }

    void outputMethodInterface(ostream& o, DBOVisibility v)
    {
        for (DBOMethod* m : methods)
            if(m->visibility == v)
                o << SC_TAB << SC_TAB << m->signature << endl;
    }

    void outputMethodBodies(ostream& o)
    {
        for (DBOMethod* m : methods)
        {
            string sig = m->signature;
            int p = sig.find(" ");
            int p2 = sig.find(";");
            o << sig.substr(0, p) << " T" << getClassName() << "." << sig.substr(p+1, p2 - p) << endl;

            stringstream ss;
            ss << m->body;
            string l;

            //o << m->signature << endl;
            o << "begin" << endl;
            //o << m->body;

            while(getline(ss, l))
                o << SC_TAB << l << endl;

            o << "end;" << endl << endl;
        }
    }

    void generateSCHead(ostream &o)
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        o << "unit " << getClassName() << "BL;" << endl << endl
            << "//" << getTable() << endl
            << "//Generated automatically." << endl
            << "//Date: " << dt << endl << endl
            << "interface" << endl
            << "uses Classes, MiscFuncs, ProfitObject, DB, IBSQL, SysUtils, Variants;" << endl << endl
            << "type" << endl
            << SC_TAB << "T" << getClassName() << " = class(TProfitObject2)" << endl;
    }

    void addMethod(string signature, string body, DBOVisibility visibility = mvPublic)
    {
        DBOMethod* m = new DBOMethod();
        m->visibility = mvPublic;
        m->body = body;
        m->signature = signature;

        methods.push_back(m);
    }

public:
    DBOTable(json j) : DBObject{j}
    {
        j["table"].get_to(table);
        j["PK"].get_to(pk);
        j["class"].get_to(className);
        j["objId"].get_to(objId);

        for (auto& element : j["fields"])
            fields.push_back(new DBOField(element));

        addMethod("constructor Create; override;", "Clear;\ninherited Create;\n");
        addClearMethod();
        addMethod("function getDBTable: String; override;", "Result := '" + getTable() + "';\n");
        addMethod("function FieldCount: Integer; override;", "Result := " + to_string(fields.size()) + ";\n");
        addMethod("function RegID: Integer; override;", "Result := " + to_string(objId) + ";\n");
        addFieldEnumeratorMethod_fieldNr("function GetFieldName(i: Integer): String; override;", &DBOField::getName);
        addFieldEnumeratorMethod_fieldNr("function GetFieldTypeName(i: Integer): String; override;", &DBOField::getType);
        addFieldEnumeratorMethod_fieldNr("function GetFieldObjectTypeName(i: Integer): String; overload; override;", &DBOField::getFkClass);
        addFieldEnumeratorMethod_fieldNr("function GetFieldSize(i: Integer): Integer; overload; override;", &DBOField::getSizeStr, "0", &quotationMethodNoQuotation);
        addFieldEnumeratorMethod_fieldNr("function GetFieldValue(i: Integer): Variant; overload; override;", &DBOField::getName, "null", &quotationMethodNoQuotation);
        addSetFieldValueMethod();

        //TODO
        /*
        function doLoad: Boolean; override;
        function doSave: Boolean; override;
        function GetDeleteSql: String; override;
        function InnerCanDelete: Boolean; override;
        function IsUnique: Boolean; override;

        procedure GetRplCascades(sl: TStringList); override;
        function DeleteCascades(bSoft: Boolean = true): Boolean; override;
        function doReplicationPost: Boolean; override;
        function IsReplicationExists: Boolean; override;
        procedure ClearReplicationSchedule; override;
        */

        //TODO rewrite in base class to use methods with int param
        /*
        function GetFieldValue(s: String): Variant; overload; override;
        procedure SetFieldValue(s: String; val: Variant); overload; override;
        function GetFieldSize(s: String): Integer; overload; override;
        */

        //TODO later, those methods are not used now
        /*
        function IsFieldOnUI(i: Integer): Boolean; override;
        function GetUIControlTypeName(i: Integer): String; override;
        */

    }

    void addClearMethod()
    {
        stringstream ss;
        for(DBOField* f : fields)
            ss << f->getName() << " := " << f->getDefValuePas() << ";" << endl;
        addMethod("procedure Clear; override;", ss.str());
    }

    void addSetFieldValueMethod()
    {
        stringstream ss;
        ss << "case i of" << endl;
        for(size_t i = 0; i < fields.size(); i++)
            ss << SC_TAB << i << ": " << fields[i]->getName() << " := " << fields[i]->getType() << "(val);" << endl;
        ss << "end;" << endl;
        addMethod("procedure SetFieldValue(i: Integer; val: Variant); overload; override;", ss.str());
    }

    void addFieldEnumeratorMethod_fieldNr(
        string methodName,
        string (DBOField::* fn)(),
        string defaultResult = "",
        string (* quotationMethod)(string s) = &quotationMethodSingleQuoted
    ){
        //thanks to great article by Joel Spolsky for knowledge how to do this map-reduce magic:
        //https://www.joelonsoftware.com/2006/08/01/can-your-programming-language-do-this/

        stringstream ss;
        ss << "case i of" << endl;
        for(size_t i = 0; i < fields.size(); i++)
            ss << SC_TAB << i << ": Result := "
                << quotationMethod((fields[i]->*fn)())
                << ";" << endl;
        ss << SC_TAB << "else Result := "
            << quotationMethod(defaultResult)
            << ";" << endl
            << "end;" << endl;

        addMethod(methodName, ss.str());
    }

    string getTable()
    {
        return table;
    }

    string getPK()
    {
        return pk;
    }

    string getClassName()
    {
        return className;
    }

    int getObjId()
    {
        return objId;
    }

    void outputInterface(ostream &o, DBOVisibility v)
    {
        string mod;
        switch(v)
        {
            case mvPrivate:
                mod = "private";
                break;
            case mvProtected:
                mod = "protected";
                break;
            case mvPublic:
                mod = "public";
                break;
        }
        o << SC_TAB << mod << endl;
        if(v == mvPublic)
            outputFieldVariables(o);
        outputMethodInterface(o, v);
    }

    void generateSourceCode(ostream &o)
    {
        generateSCHead(o);
        outputInterface(o, mvPrivate);
        outputInterface(o, mvProtected);
        outputInterface(o, mvPublic);

        o << SC_TAB << "end;" << endl
            << "implementation" << endl << endl;

        outputMethodBodies(o);

        o << endl << "end." << endl;

    }
};

string quotationMethodNoQuotation(string s)
{
    return s;
}

string quotationMethodSingleQuoted(string s)
{
    return "'" + s + "'";
}
