//
// Created by mina on 6/6/21.
//

#include "InputChecker.h"
void CheckInput(Token token,vector<string>Terminals,vector<string>NonTerminals,vector<vector<vector<string>>>Table)
{
    InputLanguageParser NextToken;
    map<string,int>NonTerminalRows,TerminalColumns;
    for(int i=0;i<Terminals.size();++i)
        TerminalColumns[Terminals.at(i)] = i;
    for(int i=0;i<NonTerminals.size();++i)
        NonTerminalRows[NonTerminals.at(i)] = i;
    stack<string> stack;
    stack.push("$");
    stack.push(NonTerminals.at(0));
    vector<string> epsilon;
    epsilon.emplace_back("$");
    string answer;
    while (!stack.empty())
    {
        //Got a match
        if(stack.top()==token.GetType())
        {
            cout<<"matched "<<token.GetLexeme()<<endl;
            answer+=stack.top();
            stack.pop();
            token=NextToken.getNextToken();
        }
        //no match
        else if(NonTerminalRows.find(stack.top()) != NonTerminalRows.end())
        {
            //No path
            if(Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetLexeme()]).empty())
            {
                cout<<"Error: No path from "<<stack.top()<<" to "<<token.GetLexeme()<<endl;
                cout<<"discard "<<token.GetLexeme()<<endl;
                token=NextToken.getNextToken();
            }
            //Going to epsilon
            else if(Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetLexeme()])==epsilon)
                stack.pop();
            //Another production
            else
            {
                stack.pop();
                for(unsigned int i = Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetLexeme()]).size()-1; i >= 0 ; --i)
                    stack.push(Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetLexeme()]).at(i));
            }
        }//Top of stack is terminal and not matching
        else
        {
            cout<<"Error: found "<<stack.top()<<" instead of "<<token.GetLexeme().at(0)<<endl;
            cout<<"inserted"<<endl;
            answer += stack.top();
            stack.pop();
        }
    }
    cout<<"inserted string"<<answer<<"is accepted"<<endl;
}