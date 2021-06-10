#include <iostream>
#include "CFGFileParser.h"
#include "AmbiguitySolver.h"
#include "FollowSetGenerator.h"
#include "TableGenerator.h"
#include "FirstSetGenerator.h"
#include "LexicalAnalyzer.h"
#include "InputChecker.h"


int main(int argc, char** argv){
    string defPaths, cfgPath, progPath, outputPath;
    defPaths = (argc > 2) ? argv[2] : "lexDefinitions.txt";
    cfgPath = (argc > 3) ? argv[3] : "CFG.txt";
    progPath = (argc > 4) ? argv[3] : "program.txt";
    outputPath = (argc > 5) ? argv[4] : "result.txt";

//    Generate the lexical analyzer
    LexicalAnalyzer lex;
    lex.generateLexicalAnalyzer(defPaths);

//    Parse the context-free grammar
    CFGFileParser cfg;
    cfg.readCFG(cfgPath);
    map<basic_string<char>, set<vector<basic_string<char>>>> prods = cfg.getProductions();
    vector<basic_string<char>> ters = cfg.getTerminals();
    vector<basic_string<char>> nonTers = cfg.getNonTerminals();

//    Resolve ambiguity in the grammar
    AmbiguitySolver as(&prods, &ters, &nonTers);
    as.solveLeftRecursion();
    as.solveLeftFactoring();

//    Create the first and follow set for the grammar
    map<string, vector<pair<string, vector<string>>>> first = FirstSet(prods, nonTers, ters);
    FollowSetGenerator fsg(&prods, &ters, &nonTers);

//    Create the LL(1) parsing table
    vector<vector<vector<string>>> table = GenerateTable(first, fsg, ters, nonTers);

//    Create The Tokens Provider
    InputLanguageParser ilp(progPath, lex.getDfaGraph(), lex.getDfaAccepted(), lex.getStartState());

    CheckInput(&ilp, ters, nonTers, table, outputPath);

    return 0;
}