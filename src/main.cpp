#include <iostream>
#include <string>
#include "DBOGenerator.h"

//More documentation here:
//https://docs.google.com/document/d/163JL1iI60Awt6gYROcpLE2ICf0LXvQxG6jr2o-wDQIs/edit#

//Github project:
//https://github.com/tihhanovski/profit-structure-compiler

using namespace std;

int main(int argc, char *argv[])
{
    //declare generator
    DBOGenerator g = DBOGenerator();

    //read and set given options
    for(int i = 1; i < argc; i++)
    {
        string s = string(argv[i]);
        if(s == "-i")
            g.inputDir = string(argv[i + 1]);
        if(s == "-o")
            g.outputDir = string(argv[i + 1]);

        if(s == "-h")
        {
            cout << "Usage:\n\t" << argv[0] << " -i <input file> -o <output file>" << endl;
            return 0;
        }
    }

    //generate
    g.generate();

    return 0;
}
