#include <iostream>
#include "CFGFileParser.h"
#include "AmbiguitySolver.h"
#include "FollowSetGenerator.h"
#include "TableGenerator.h"
#include "FirstSetGenerator.h"
#include "LexicalAnalyzer.h"
#include "InputChecker.h"

void printList(vector<string> l){
    for(auto i : l){
        cout << i + " ";
    }
}

// Function to print Follow Set of every non-terminal for testing
void printFollowSets(FollowSetGenerator fsg, vector<string> nonter) {
    cout << "\n\nFollow Sets:\n";
    for (int i = 0; i < nonter.size(); i++) {
        string nonTerminal = nonter.at(i);
        set<string> follow = fsg.getFollowSet(nonTerminal);
        cout << "Non Terminal : " << nonTerminal << "\t, Follow Set: " << endl;
        for (auto s : follow) {
            cout << s << "\t";
        }
        cout << "\n";
    }
}

//int main() {
////Test input parser
//    CFGFileParser cfg;
//    cfg.readCFG("CFG.txt");
//    map<string, set<vector<string>>> prods = cfg.getProductions();
//    vector<string> nonter = cfg.getNonTerminals();
//    vector<string> ter = cfg.getTerminals();
//    AmbiguitySolver as(&prods, &ter, &nonter);
//    as.solveLeftFactoring();
//    as.solveLeftRecursion();
//    cout << "Productions:" << endl;
//    int num = 1;
//    for(auto i : nonter){
//        cout << num++ << "-" << endl;
//        for(auto j : prods[i]){
//            cout << i + " -> ";
//            printList(j);
//            cout << "\n";
//        }
//        cout << "\n";
//    }
//    cout << "Non-Terminals:" << endl;
//    num = 1;
//    for(auto i : nonter){
//        cout << num++ << "- " << i << endl;
//    }
//
//    cout << "\nTerminals:" << endl;
//    num = 1;
//    for(auto i : ter){
//        cout << num++ << "- " << i << endl;
//    }
//
////    Test left recursion
///*    map<string, set<vector<string>>> p;
//    p["S"] = {{"A", "a"}, {"b"}};
//    p["A"] = {{"A", "c"}, {"S", "d"}, {"f"}};
//    vector<string> ter  = {"a", "b", "c", "d", "f"};
//    vector<string> nter = {"A", "S"};
//    AmbiguitySolver as(&p, &ter, &nter);
//    as.solveLeftRecursion();
//    for(auto i : p){
//        for(auto j : i.second){
//            cout << i.first + " -> ";
//            printList(j);
//            cout << "\n";
//        }
//        cout << "\n";
//    }
//    */
//
//    FollowSetGenerator fsg(&prods, &ter, &nonter);
//
//    printFollowSets(fsg, nonter);
//
//    /*
//    vector<vector<string>> table=GenerateTable(FirstSet(prods,nonter,ter),fsg,ter,nonter);
//    for(vector<string>temp:table)
//    {
//        for(const string& a:temp)
//            cout<<a<<" ";
//        cout<<endl;
//    }*/
//    return 0;
//}

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
}