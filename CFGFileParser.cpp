//
// Created by hossam on 02/06/2021.
//

#include "CFGFileParser.h"

CFGFileParser::CFGFileParser() = default;

void CFGFileParser::readCFG(string path) {
    fstream file;
    file.open(path, ios::in);
    string line, production;
    while(getline(file, line)){
        if(line.at(0) == '#'){
            if(production.length() > 0) parseProduction(production);
            production = line;
        } else production += (" " + line);
    }
    if(production.length() > 0) parseProduction(production);
}

void CFGFileParser::parseProduction(string prod) {
    list<string> splitted, pieces;
    split(prod, "[\\s]+=[\\s]+", &splitted);
    string lhs = splitted.front();
    string rhs = splitted.back();
    splitted.clear();
//  read lhs (non-terminal)
    lhs.erase(lhs.begin());
    lhs = regex_replace(lhs, regex("[\\s]+"), "");
    if(find(nonTerminals.begin(), nonTerminals.end(), lhs) == nonTerminals.end())
        nonTerminals.push_back(lhs);
//  read rhs (set of productions seperated with |)
    rhs = regex_replace(rhs, regex("\\\\L"), "$");
    split(rhs, R"([\s]+\|[\s]+)", &splitted);
    for(auto i : splitted){
        split(i, "[\\s]+", &pieces);
        vector<string> prod;
        for(auto j : pieces){
            if(j.at(0) == '\''){
                j = regex_replace(j, regex("\'"), "");
                if(find(terminals.begin(), terminals.end(), j) == terminals.end())
                    terminals.push_back(j);
            }
            prod.push_back(j);
        }
        productions[lhs].insert(prod);
        pieces.clear();
    }
}

void CFGFileParser::split(string str, string seperator, list<string> *strings) {
    regex rgx(seperator);
    sregex_token_iterator iter(str.begin(),str.end(), rgx, -1);
    sregex_token_iterator end;
    for ( ; iter != end; ++iter) {
        if (*iter != "") {
            strings->push_back(*iter);
        }
    }
}

map<string, set<vector<string>>> CFGFileParser::getProductions() {
    return productions;
}

vector<string> CFGFileParser::getTerminals() {
    return terminals;
}

vector<string> CFGFileParser::getNonTerminals() {
    return nonTerminals;
}