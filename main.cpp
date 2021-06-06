#include <iostream>
#include "CFGFileParser.h"
#include "AmbiguitySolver.h"
#include "FollowSetGenerator.h"
#include "TableGenerator.h"
#include "FirstSetGenerator.h"

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

int main() {
//Test input parser
    CFGFileParser cfg;
    cfg.readCFG("CFG.txt");
    map<string, set<vector<string>>> prods = cfg.getProductions();
    vector<string> nonter = cfg.getNonTerminals();
    vector<string> ter = cfg.getTerminals();
    AmbiguitySolver as(&prods, &ter, &nonter);
    as.solveLeftFactoring();
    as.solveLeftRecursion();
    cout << "Productions:" << endl;
    int num = 1;
    for(auto i : nonter){
        cout << num++ << "-" << endl;
        for(auto j : prods[i]){
            cout << i + " -> ";
            printList(j);
            cout << "\n";
        }
        cout << "\n";
    }
    cout << "Non-Terminals:" << endl;
    num = 1;
    for(auto i : nonter){
        cout << num++ << "- " << i << endl;
    }

    cout << "\nTerminals:" << endl;
    num = 1;
    for(auto i : ter){
        cout << num++ << "- " << i << endl;
    }

//    Test left recursion
/*    map<string, set<vector<string>>> p;
    p["S"] = {{"A", "a"}, {"b"}};
    p["A"] = {{"A", "c"}, {"S", "d"}, {"f"}};
    vector<string> ter  = {"a", "b", "c", "d", "f"};
    vector<string> nter = {"A", "S"};
    AmbiguitySolver as(&p, &ter, &nter);
    as.solveLeftRecursion();
    for(auto i : p){
        for(auto j : i.second){
            cout << i.first + " -> ";
            printList(j);
            cout << "\n";
        }
        cout << "\n";
    }
    */

    FollowSetGenerator fsg(&prods, &ter, &nonter);

    printFollowSets(fsg, nonter);

    /*
    vector<vector<string>> table=GenerateTable(FirstSet(prods,nonter,ter),fsg,ter,nonter);
    for(vector<string>temp:table)
    {
        for(const string& a:temp)
            cout<<a<<" ";
        cout<<endl;
    }*/
    return 0;
}
