#include <string>
#include<bits/stdc++.h>

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
