//
// Created by youssef on 6/4/21.
//

#ifndef PARSERGENERATOR_FOLLOWSETGENERATOR_H
#define PARSERGENERATOR_FOLLOWSETGENERATOR_H

#include "map"
#include "set"
#include "vector"
#include "algorithm"
#include "iostream"

using namespace std;

class FollowSetGenerator{
private:
    map<string, set<vector<string>>> *productions;
    vector<string> *terminals;
    vector<string> *nonTerminals;
    map<string, set<string>> first;
    map<string, set<string>> follow;
    void generateFollowSets();
    bool isNonTerminal(const string& s);
    bool containsEpsilon(set<string> s);
    void initializeFirstMap();
    void initializeFollowMap();
    void addAll(string i, string j, bool withEpsilon, bool isFirst);


public:
    FollowSetGenerator(map<string, set<vector<string>>> *prods, vector<string> *ters, vector<string> *nonTers);
    set<string> getFollowSet(const string& nonTerminal);
};

#endif //PARSERGENERATOR_FOLLOWSETGENERATOR_H
