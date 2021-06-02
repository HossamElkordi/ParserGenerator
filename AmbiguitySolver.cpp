//
// Created by hossam on 02/06/2021.
//

#include "AmbiguitySolver.h"

AmbiguitySolver::AmbiguitySolver() = default;

AmbiguitySolver::AmbiguitySolver(map<string, set<vector<string>>> *prods, vector<string> *ters, vector<string> *nonTers) {
    productions = prods;
    terminals = ters;
    nonTerminals = nonTers;
}

void AmbiguitySolver::solveLeftFactoring() {

}

void AmbiguitySolver::solveLeftRecursion() {
    vector<string> newProds;
    for(auto i = nonTerminals->begin(); i != nonTerminals->end(); ++i){
        if(i->empty()) continue;
        for(auto j = nonTerminals->begin(); j != i; ++j){
            if(j->empty()) continue;
            for(auto k = (*productions)[*i].begin(); k != (*productions)[*i].end(); ++k){
                if(*j == k->front()){
                    vector<string> temp = *k;
                    set<vector<string>> rep = (*productions)[*j];
                    temp.erase(temp.begin());
                    (*productions)[*i].erase(k);
                    for (auto x : rep) {
                        vector<string> newOne = concatLists(x, temp);
                        (*productions)[*i].insert(newOne);
                    }
                }
            }
        }
        solveImmediateLeftRecursion(*i, &(*productions)[*i], &newProds);
    }
    for(auto i : newProds){
        (*nonTerminals).insert(++find(nonTerminals->begin(), nonTerminals->end(), i), i + "'");
    }
}

void AmbiguitySolver::solveImmediateLeftRecursion(string lhs, set<vector<string>> *rhs, vector<string> *newProds) {
    set<vector<string>> newSet, oldSet;
    string newLHS = lhs + "'";
    for(auto i = rhs->begin(); i != rhs->end(); ++i){
        if(lhs == i->front()){
            vector<string> temp = *i;
            temp.erase(temp.begin());
            temp.push_back(newLHS);
            newSet.insert(temp);
        }else{
            oldSet.insert(*i);
        }
    }
    if(!newSet.empty()){
        newSet.insert({"$"});
        for(auto i = oldSet.begin(); i != oldSet.end(); ++i){
            vector<string> temp = *i;
            temp.push_back(newLHS);
            temp.erase(find(temp.begin(), temp.end(), "$"));
            oldSet.erase(i);
            oldSet.insert(temp);
        }
        (*productions)[lhs] = oldSet;
        (*productions)[newLHS] = newSet;
        (*newProds).push_back(lhs);
    }
}

vector<string> AmbiguitySolver::concatLists(vector<string> a, vector<string> b) {
    vector<string> res;
    res.reserve(a.size() + b.size());
    for(auto i : a) res.push_back(i);
    for(auto i : b) res.push_back(i);
    return res;
}
