#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include <time.h>
#include <cstring>
#include "../lib/json/single_include/nlohmann/json.hpp"
#include "DBObject.h"
#include "DBOTable.h"


using namespace std;
using nlohmann::json;

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        string s = string(argv[1]);

        ifstream i(s);
        json j;
        i >> j;
        i.close();

        DBOTable* dbo = new DBOTable(j);
        //cout << dbo->getName() << endl << dbo->getType() << endl;
        cout << "====================================" << endl;
        dbo->generateSourceCode(cout);
        cout << "====================================" << endl;

        delete dbo;

        cout << endl;

    }
    else
        cout << argv[0] << " <file>" << endl;

    /*
    std::ifstream i("../samples/RIIGID.json");

    string type;
    j["type"].get_to(type);

    cout << "type: " << j["type"]  << endl;
    cout << "type: " << type  << endl;

    //cout << std::setw(4) << j << std::endl;
    */

    return 0;
}
