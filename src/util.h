#pragma once
#include <string>
using namespace std;

const string SC_TAB = "    ";   //tab for .pas source code  //TODO move elsewhere

/**
 * returns s unchanged
 */
string quotationMethodNoQuotation(string s);

/**
 * returns s quoted in single quotes xxx -> 'xxx'
 */
string quotationMethodSingleQuoted(string s);

/**
 * converts to upper case
 */
void toUpper(string& s);

/**
 * converts to lower case
 */
void toLower(string& s);

/**
 * checks does file exists
 */
bool fileExists(const string& name);
