#include <string>
using namespace std;

string quotationMethodNoQuotation(string s)
{
    return s;
}

string quotationMethodSingleQuoted(string s)
{
    return "'" + s + "'";
}
