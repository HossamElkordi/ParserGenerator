//
// Created by Pierre on 6/4/2021.
//

#include "FirstSetGenerator.h"



map<string, vector<pair<string, vector<string>>>> FirstSet(map<string, set<vector<string>>> productions,
                                                           vector<string> nonTerminals, set<string> input){

    // Assuming that nonTerminals are ordered
    vector<string> reversed = nonTerminals;
    reverse(reversed.begin(), reversed.end());
    map<string, vector<pair<string, vector<string>>>> first;
    vector<pair<string, vector<string>>> temp;
    vector<string>::iterator s;
    set<vector<string>>::iterator s2;
    vector<pair<string, vector<string>>>::iterator s3;
    for(s = reversed.begin(); s != reversed.end(); ++s){
        for(s2 = productions[*s].begin(); s2 != productions[*s].end(); ++s2){
            vector<string> v = (*s2);
            string t = v[0];
            if(t.empty()){ // it is epsilon
                temp.emplace_back("", v);
            }else if(input.find(t) != input.end()){
                temp.emplace_back(t, v);
            }else{
                for(s3 = first[t].begin(); s3 != first[t].end(); ++s3){
                    temp.emplace_back(s3->first, v);
                }
            }
        }
        first[*s] = temp;
        temp.clear();
    }
    return first;
}

