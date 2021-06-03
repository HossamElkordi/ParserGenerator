//
// Created by hossam on 02/06/2021.
//

#include <iostream>
#include "AmbiguitySolver.h"

AmbiguitySolver::AmbiguitySolver() = default;

AmbiguitySolver::AmbiguitySolver(map<string, set<vector<string>>> *prods, vector<string> *ters, vector<string> *nonTers) {
    productions = prods;
    terminals = ters;
    nonTerminals = nonTers;
}

bool AmbiguitySolver::existsnt(string in) {
    for (int i = 0; i < nonTerminals->size(); ++i) {
        if(nonTerminals->at(i).compare(in)==0)
            return true;
    }
    return false;
}


void AmbiguitySolver::solveLeftFactoring() {
    for(auto i=productions->begin();i!=productions->end();i++){
        set<vector<string>> s=i->second;
        vector<vector<string>>temp;
        for(auto j=s.begin();j!=s.end();j++){
            vector<string>tempo;
            for(int k=0;k<(*j).size();++k){
                tempo.push_back((*j)[k]);
            }
            temp.push_back(tempo);
        }
        /*
        vector<vector<int> > db(
                temp.size(),
                vector<int>(temp.size()));
        for (int j = 0; j < temp.size(); ++j) {
            for (int k = j+1; k <temp.size() ; ++k) {
                for (int l = 0; l < min(temp[j].size(),temp[k].size()); ++l) {
                    if (temp[j][l].compare(temp[k][l])!=0){
                        db[j][k]=l;
                        break;
                    }
                    if(l+1==min(temp[j].size(),temp[k].size()))
                        db[j][k]=l+1;
                }
            }
        }
        continue;*/
        for (int j = 0; j < temp.size(); ++j) {
            vector<int>sim;
            for (int k = j+1; k <temp.size() ; ++k) {
                if (temp[j][0].compare(temp[k][0])==0){
                    sim.push_back(k);
                }
            }
            if(sim.size()!=0){
                string ttl=i->first+"'";
                string master=temp[j][0];
                while(existsnt(ttl)){ttl=ttl+"'";}
                vector<vector<string>> newp;
                vector<string> tempo;
                if (temp[j].size()==1){tempo.push_back("$");}
                for (int q = 1; q <temp[j].size() ; ++q) {
                    tempo.push_back(temp[j][q]);
                }
                newp.push_back(tempo);
                for(int q=0;q<sim.size();++q){
                   vector<string>tempa;
                    if (temp[sim[q]].size()==1){
                        tempa.push_back("$");

                    }
                    for (int s = 1; s <temp[sim[q]].size(); ++s) {
                        tempa.push_back(temp[sim[q]][s]);
                    }
                    newp.push_back(tempa);
                }
                vector<string>o;
                o.push_back(temp[j][0]);
                o.push_back(ttl);
                temp[j]=o;
                for (int k = 0; k < sim.size(); ++k) {
                    temp.erase(temp.begin()+sim[k]);
                    for (int l = k+1; l < sim.size(); ++l) {
                        if(sim[l]>sim[k])
                            sim[l]--;
                    }
                }
                set<vector<string>>np;
                for (int k = 0; k < newp.size(); ++k) {
                    np.insert(newp[k]);
                }
                set<vector<string>>op;
                for (int k = 0; k < temp.size(); ++k) {
                    op.insert(temp[k]);
                }
                (*productions)[ttl]=np;
                (*productions)[i->first]=op;
                int k=0;
                while((*nonTerminals)[k].compare(i->first)!=0){
                    ++k;
                }
                (*nonTerminals).insert((*nonTerminals).begin()+k+1,ttl);
                i=--(productions->begin());
            }
        }
    }

}

void AmbiguitySolver::solveLeftRecursion() {
    vector<string> newProds;
    for(auto i = nonTerminals->begin(); i != nonTerminals->end(); ++i){
        for(auto j = nonTerminals->begin(); j != i; ++j){
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
            auto it = find(temp.begin(), temp.end(), "$");
            if(it != temp.end()) temp.erase(it);
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
