//
// Created by hossam on 02/06/2021.
//

#ifndef PARSERGENERATOR_AMBIGUITYSOLVER_H
#define PARSERGENERATOR_AMBIGUITYSOLVER_H

#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

class AmbiguitySolver{
    private:
        map<string, set<vector<string>>> *productions;
        vector<string> *terminals;
        vector<string> *nonTerminals;
        bool existsnt(string in);
        void solveImmediateLeftRecursion(string lhs, set<vector<string>> *rhs, vector<string> *newProds);
        vector<string> concatLists(vector<string> a, vector<string> b);

    public:
        AmbiguitySolver();
        AmbiguitySolver(map<string, set<vector<string>>> *prods, vector<string> *ters, vector<string> *nonTers);
        void solveLeftFactoring();
        void solveLeftRecursion();
};

#endif //PARSERGENERATOR_AMBIGUITYSOLVER_H
