//
// Created by youssef on 6/4/21.
//

#include "FollowSetGenerator.h"

FollowSetGenerator::FollowSetGenerator(map<string, set<vector<string>>> *prods, vector<string> *ters,
                                       vector<string> *nonTers) {
    productions = prods;
    terminals = ters;
    nonTerminals = nonTers;
    generateFollowSets();
}

set<string> FollowSetGenerator::getFollowSet(string *nonTerminal) {

    return follow.at(*nonTerminal);
}

void FollowSetGenerator::generateFollowSets() {
    for (int i = 0; i < nonTerminals->size(); i++) {
        string nonTerminal = nonTerminals->at(i);
        vector<string> temp = *terminals;
        set<string> s(temp.begin(), temp.end());
        follow.insert(pair<string, set<string>>(nonTerminal, s));
    }
}

