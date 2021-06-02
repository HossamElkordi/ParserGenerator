//
// Created by hossam on 02/06/2021.
//

#ifndef PARSERGENERATOR_CFGFILEPARSER_H
#define PARSERGENERATOR_CFGFILEPARSER_H

#include <string>
#include <map>
#include <set>
#include <list>
#include <regex>
#include <fstream>
#include <iostream>

using namespace std;

class CFGFileParser{
    private:
        map<string, set<vector<string>>> productions;
        vector<string> terminals;
        vector<string> nonTerminals;

        void split(string str, string seperator, list<string> * strings);

    public:
        CFGFileParser();
        void readCFG(string path);
        void parseProduction(string prod);
        map<string, set<vector<string>>> getProductions();
        vector<string> getTerminals();
        vector<string> getNonTerminals();
};

#endif //PARSERGENERATOR_CFGFILEPARSER_H
