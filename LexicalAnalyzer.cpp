//
// Created by hossam on 07/06/2021.
//

#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer() = default;

void LexicalAnalyzer::generateLexicalAnalyzer(string definitionsPath) {
    InputParser ip(definitionsPath);
    ip.readFile();
    map<string, string> regs = ip.getRegexes();
    for(auto i : ip.getKeywords()){
        regs[i] = i;
    }
    for(auto i : ip.getPunctuations()){
        regs[i] = "\\"+i;
    }

    Nfa nfa = Nfa();
    nfa = nfa.getfromlist(regs);

    Dfa dfa(nfa.transitions, nfa.getAlphabets(), nfa.tags, ip.getRegexPriority());
    dfa.createDFA();
    dfaGraph = dfa.getGraph();
    dfaAccepted = dfa.getDfaAccepted();
    start = dfa.getStart();


    minimizeDfa(&dfaGraph, &dfaAccepted, nfa.getAlphabets(), &start);
//    map<string, map<string, string>> dfaForm;
//    map<string, string> accForm;
//    string startState;
//    dfa.translateGraph(&dfaForm, &accForm, &startState);
}

map<set<int>, map<string, set<int>>> LexicalAnalyzer::getDfaGraph() {
    return dfaGraph;
}

map<set<int>, string> LexicalAnalyzer::getDfaAccepted() {
    return dfaAccepted;
}

set<int> LexicalAnalyzer::getStartState() {
    return start;
}
