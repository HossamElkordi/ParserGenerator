//
// Created by mina on 6/6/21.
//

#ifndef PARSERGENERATOR_INPUTCHECKER_H
#define PARSERGENERATOR_INPUTCHECKER_H

#include "Token.h"
#include "vector"
#include <map>
#include <stack>
#include "InputLanguageParser.h"
#include <iostream>

using namespace std;

void CheckInput(Token T,vector<string>Terminals,vector<string>NonTerminals,vector<vector<string>>Table);
#endif //PARSERGENERATOR_INPUTCHECKER_H
