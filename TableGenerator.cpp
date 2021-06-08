//
// Created by mina on 6/5/21.
//

#include "TableGenerator.h"
vector<vector<vector<string>>> GenerateTable(const map<string, vector<pair<string, vector<string>>>>& First,  FollowSetGenerator Follow,vector<string>Terminals,vector<string>NonTerminals)
{
    map<string,int>NonTerminalRows,TerminalColumns;
    TerminalColumns["$"]=0;
    for(int i=1;i<=Terminals.size();++i)
        TerminalColumns[Terminals.at(i-1)] = i;
    for(int i=0;i<NonTerminals.size();++i)
        NonTerminalRows[NonTerminals.at(i)] = i;
    vector<vector<vector<string>>>answer;
    for(int i=0;i<NonTerminalRows.size();++i)
    {
        vector<vector<string>>temp;
        vector<string>d;
        temp.assign(TerminalColumns.size(),d);
        answer.push_back(temp);
    }
    vector<string>nonTerminalsForFollow;
    for (auto const& iterator : First)
    {
        for(const pair<string,vector<string>>& NonTerminalPair:iterator.second)
        {
            if(answer[NonTerminalRows[iterator.first]][TerminalColumns[NonTerminalPair.first]].empty())
            {
                answer[NonTerminalRows[iterator.first]][TerminalColumns[NonTerminalPair.first]]=NonTerminalPair.second;
                if(find(NonTerminalPair.second.begin(),NonTerminalPair.second.end(),"$")!=NonTerminalPair.second.end())
                    nonTerminalsForFollow.push_back(iterator.first);
            }
            else
            {
                vector<vector<vector<string>>> error;
                return error;
            }
        }
    }
    for(const string& NonTerminal : nonTerminalsForFollow)
    {
        for(const string& Terminal:Follow.getFollowSet(NonTerminal))
        {
            if(answer[NonTerminalRows[NonTerminal]][TerminalColumns[Terminal]].empty())
            {
                vector<string>temp;
                temp.emplace_back("$");
                answer[NonTerminalRows[NonTerminal]][TerminalColumns[Terminal]]=temp;
            }
        }
    }
    return answer;
}