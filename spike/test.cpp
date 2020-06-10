#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include <time.h>
#include <cstring>
#include <cmath>
#include "../lib/json/single_include/nlohmann/json.hpp"


using namespace std;
using nlohmann::json;

void simpleConstruct()
{
    //construct JSON
    json j2 = {
      {"pi", 3.141},
      {"happy", true},
      {"name", "Niels"},
      {"nothing", nullptr},
      {"answer", {
        {"everything", 42}
      }},
      {"list", {1, 0, 2}},
      {"object", {
        {"currency", "USD"},
        {"value", 42.99}
      }}
    };

    //serialize our JSON
    string s = j2.dump();

    cout << setw(4) << j2 << endl;
}

void prettifyJson()
{
    // read a JSON file
    std::ifstream i("../samples/MYYGITELLIMUSED.json");
    json j;
    i >> j;

    // write prettified JSON to another file
    //std::ofstream o("pretty.json");
    cout << std::setw(4) << j << std::endl;
}

int main()
{
    std::ifstream i("../samples/RIIGID.json");
    json j;
    i >> j;

    string type;
    j["type"].get_to(type);

    cout << "type: " << j["type"]  << endl;
    cout << "type: " << type  << endl;

    //cout << std::setw(4) << j << std::endl;

    return 0;
}
