//
// Created by youssef on 6/4/21.
//

#include "FollowSetGenerator.h"
#include "FirstSetGenerator.h"

FollowSetGenerator::FollowSetGenerator(map<string, set<vector<string>>> *prods, vector<string> *ters,
                                       vector<string> *nonTers) {
    productions = prods;
    terminals = ters;
    nonTerminals = nonTers;
    initializeFirstMap();
    initializeFollowMap();
    generateFollowSets();
}

set<string> FollowSetGenerator::getFollowSet(const string& nonTerminal) {

    return follow.at(nonTerminal);
}

void FollowSetGenerator::generateFollowSets() {

    string startSymbol = nonTerminals->at(0);
    follow[startSymbol].insert("$");

    bool addedNew = 1;
    int count = 0;
    while (addedNew) {
        addedNew = 0;
        map<string, set<vector<string>>>::iterator it;
        for (it = productions->begin(); it != productions->end(); it++) {
            string LHS = it->first;
            set<vector<string>> fullRHS = it->second;

            set<vector<string>>::iterator it2;
            for (it2 = fullRHS.begin(); it2 != fullRHS.end(); it2++) {
                vector<string> RHS = *it2;
                for (int i = 0; i < RHS.size(); i++) {
                    if (!isNonTerminal(RHS.at(i))) {
                        continue;
                    }

                    if (i == RHS.size() - 1) {
                        addAll(RHS.at(i), LHS, 1, 0);
                    } else if (!isNonTerminal(RHS.at(i + 1))) {
                        follow[RHS.at(i)].insert(RHS.at(i+1));
                    } else {
                        addAll(RHS.at(i), RHS.at(i + 1), 0, 1);
                        if (containsEpsilon(first[RHS.at(i + 1)]))
                            addAll(RHS.at(i), LHS, 1, 0);
                    }
                }
            }
        }
        count++;
        if (count < nonTerminals->size())
            addedNew = 1;
    }
}

bool FollowSetGenerator::isNonTerminal(const string &s) {
    std::vector<string>::iterator it;
    it = std::find(nonTerminals->begin(), nonTerminals->end(), s);
    return it != nonTerminals->end();
}

void FollowSetGenerator::initializeFollowMap() {
    for (int i = 0; i < nonTerminals->size(); i++) {
        set<string> s;
        follow.insert(pair<string, set<string>>(nonTerminals->at(i), s));
    }
}

// Function to add in follow[i] all the elements of follow[j]
void FollowSetGenerator::addAll(string i, string j, bool withEpsilon, bool isFirst) {
    set<string> s;
    if (isFirst)
        s = first[j];
    else
        s = follow[j];
    set<string>::iterator itr;
    for (itr = s.begin(); itr != s.end(); itr++) {
        if (*itr == "$" && !withEpsilon)
            continue;
        follow[i].insert(*itr);
    }
}

void FollowSetGenerator::initializeFirstMap() {
    map<string, vector<pair<string, vector<string>>>> m = FirstSet(*productions, *nonTerminals, *terminals);
    for (int i = 0; i < nonTerminals->size(); i++) {
        set<string> s;
        vector<pair<string, vector<string>>> v = m[nonTerminals->at(i)];
        for (int j = 0; j < v.size(); j++) {
            s.insert(v.at(j).first);
        }
        first.insert(pair<string, set<string>>(nonTerminals->at(i), s));
    }
}

bool FollowSetGenerator::containsEpsilon(set<string> s) {
    auto pos = s.find("$");
    return pos != s.end();
}
