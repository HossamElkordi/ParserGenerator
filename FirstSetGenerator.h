//
// Created by Pierre on 6/4/2021.
//

#ifndef PARSERGENERATOR_FIRSTSETGENERATOR_H
#define PARSERGENERATOR_FIRSTSETGENERATOR_H
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

map<string, vector<pair<string, vector<string>>>> FirstSet(map<string, set<vector<string>>> productions,
vector<string> nonTerminals, set<string> input);

#endif //PARSERGENERATOR_FIRSTSETGENERATOR_H
