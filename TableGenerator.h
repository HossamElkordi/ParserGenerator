//
// Created by mina on 6/5/21.
//

#ifndef PARSERGENERATOR_TABLEGENERATOR_H
#define PARSERGENERATOR_TABLEGENERATOR_H

#include "FollowSetGenerator.h"
#include <fstream>
using namespace std;

vector<vector<vector<string>>> GenerateTable(const map<string, vector<pair<string, vector<string>>>>& First,  FollowSetGenerator Follow,vector<string>Terminals,vector<string>NonTerminals);
#endif //PARSERGENERATOR_TABLEGENERATOR_H
