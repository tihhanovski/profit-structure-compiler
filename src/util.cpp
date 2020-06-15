#include <string>
#include<bits/stdc++.h>
#include <fstream>

using namespace std;

string quotationMethodNoQuotation(string s)
{
    return s;
}

string quotationMethodSingleQuoted(string s)
{
    return "'" + s + "'";
}

void toUpper(string& s)
{
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void toLower(string& s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

bool fileExists(const string& name)
{
    ifstream f(name.c_str());
    return f.good();
}
