//
// Created by mina on 6/5/21.
//

#include "TableGenerator.h"
vector<vector<string >>GenerateTable(const map<string, vector<pair<string, vector<string>>>>& First,vector<string>Terminals,vector<string>NonTerminals)
{
    map<string,int>NonTerminalRows,TerminalColumns;
    for(int i=0;i<Terminals.size();++i)
        TerminalColumns[Terminals.at(i)] = i;
    for(int i=0;i<Terminals.size();++i)
        NonTerminalRows[NonTerminals.at(i)] = i;
    vector<vector<string>>answer;
    for(int i=0;i<NonTerminalRows.size();++i)
    {
        vector<string>temp;
        temp.assign(TerminalColumns.size(),"");
        answer.push_back(temp);
    }
    for (auto const& iterator : First)
    {
        for(const pair<string,vector<string>>& NonTerminalPair:iterator.second)
        {
            for(const string& GoTo:NonTerminalPair.second)
            {
                if(answer[NonTerminalRows[iterator.first]][TerminalColumns[NonTerminalPair.first]].empty())
                    answer[NonTerminalRows[iterator.first]][TerminalColumns[NonTerminalPair.first]]+=GoTo;
                else
                {
                    vector<vector<string>> error;
                    return error;
                }
            }
        }
    }
    //TODO constructor parameters
    //FollowSetGenerator myobj;
    //myobj.getFollowSet()
    return answer;
}