#include <dirent.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include "../lib/json/single_include/nlohmann/json.hpp"
#include "util.h"
#include "PascalTypesLibrary.h"
#include "DBObject.h"
#include "DBOTable.h"
#include "DBOGenerator.h"

using namespace std;

void DBOGenerator::generate()
{
    cout << "Input dir: " << inputDir << endl
        << "Output dir: " << outputDir << endl;

    string typesFile = inputDir + "/types.json";
    if(!fileExists(typesFile))
    {
        cerr << "types.json does not exist: " << typesFile << endl;
        return;
    }

    PascalTypesLibrary::GetInstance()->init(typesFile);

    string tablesDir = inputDir + "/tables/";

    DIR *dir;
    struct dirent *ent;

    dir = opendir (tablesDir.c_str());
    if (dir != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            string s = string(ent->d_name);
            int i = s.size();
            if(i > 5)
            {
                string suf = s.substr(i - 5, 5);
                toLower(suf);
                if(suf == ".json")
                {
                    cout << s << endl;

                    ifstream i(tablesDir + s);
                    json j;
                    i >> j;
                    i.close();

                    DBOTable* dbo = new DBOTable(j);

                    ofstream output(outputDir + "/" + dbo->getClassName() + "BL.pas");
                    dbo->generateSourceCode(output);
                    output.close();

                    delete dbo;

                }
            }
        }
        closedir (dir);
    }
    else
        cerr << "Cannot open directory " << tablesDir << endl;

}
