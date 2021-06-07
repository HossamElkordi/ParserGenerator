//
// Created by hossam on 07/06/2021.
//

#ifndef PARSERGENERATOR_LEXICALANALYZER_H
#define PARSERGENERATOR_LEXICALANALYZER_H

#include <string>
#include <map>
#include <set>
#include "InputParser.h"
#include "Nfa.h"
#include "Dfa.h"
#include "MinimizedDfa.h"


using namespace std;

class LexicalAnalyzer{
    private:
        map<set<int>, map<string, set<int>>> dfaGraph;
        map<set<int>, string> dfaAccepted;
        set<int> start;


    public:
        LexicalAnalyzer();
        void generateLexicalAnalyzer(string definitionsPath);
        map<set<int>, map<string, set<int>>> getDfaGraph();
        map<set<int>, string> getDfaAccepted();
        set<int> getStartState();
};

#endif //PARSERGENERATOR_LEXICALANALYZER_H
