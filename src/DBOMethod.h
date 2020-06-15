#pragma once
#include <string>

using namespace std;

/**
 *
 */
enum DBOVisibility {mvPrivate, mvProtected, mvPublic};

/**
 * Method description (function or procedure)
 */
class DBOMethod
{
public:
    DBOVisibility visibility = mvPublic;
    string signature;   //method signature for interface part
    string body;        //method body without first begin and final end
};
