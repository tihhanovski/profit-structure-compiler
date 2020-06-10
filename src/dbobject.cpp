#include <string>
#include <limits>
#include <vector>
#include "../lib/json/single_include/nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

enum DBOMethodVisibility {mvPrivate, mvProtected, mvPublic};
//enum DBOMethodType {mtConstructor, mvProcedure, mvFunction};

class DBOMethod
{
public:
    DBOMethodVisibility visibility = mvPublic;
    string signature, body;
};

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

    void outputMethodInterface(ostream& o, DBOMethodVisibility v)
    {
        for (DBOMethod* m : methods)
            if(m->visibility == v)
                o << "        " << m->signature << endl;
    }

    void outputMethodBodies(ostream& o)
    {
        for (DBOMethod* m : methods)
        {
            string sig = m->signature;
            int p = sig.find(" ");
            o << sig.substr(0, p) << " T" << getClassName() << "." << sig.substr(p+1) << endl;

            //o << m->signature << endl;
            o << "begin" << endl
                << m->body
                << "end;" << endl << endl;
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
            << "    T" << getClassName() << " = class(TProfitObject)" << endl;
    }

    void addMethod(string signature, string body, DBOMethodVisibility visibility = mvPublic)
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

        addMethod("constructor Create; override;", "Clear;\ninherited Create;\n");
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

    void outputInterface(ostream &o, DBOMethodVisibility v)
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
        o << "    " << mod << endl;
        outputMethodInterface(o, v);
    }

    void generateSourceCode(ostream &o)
    {
        generateSCHead(o);
        outputInterface(o, mvPrivate);
        outputInterface(o, mvProtected);
        outputInterface(o, mvPublic);

        o << "    end;" << endl
            << "implementation" << endl << endl;

        outputMethodBodies(o);

    }
};
