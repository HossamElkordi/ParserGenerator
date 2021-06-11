//
// Created by mina on 6/6/21.
//

#include "InputChecker.h"
void WriteResult(const string& result, const string& outPath)
{
    fstream my_file;
    my_file.open(outPath, ios::out);
    my_file << result;
    my_file.close();
}

void CheckInput(InputLanguageParser* NextToken,vector<string>Terminals,vector<string>NonTerminals,vector<vector<vector<string>>>Table, string outPath)
{
    Token token = NextToken->getNextToken();
    map<string,int>NonTerminalRows,TerminalColumns;
    TerminalColumns["$"]=0;
    for(int i=1;i<=Terminals.size();++i)
        TerminalColumns[Terminals.at(i-1)] = i;
    for(int i=0;i<NonTerminals.size();++i)
        NonTerminalRows[NonTerminals.at(i)] = i;
    stack<string> stack;
    stack.push("$");
    stack.push(NonTerminals.at(0));
    vector<string> epsilon;
    epsilon.emplace_back("$");
    string answer="METHOD_BODY\n";
    while (!stack.empty())
    {
        //Got a match
        if(stack.top()==token.GetType() || stack.top()==token.GetLexeme())
        {
            stack.pop();
            if(token.GetLexeme()!="$")
                token=NextToken->getNextToken();
        }
        //no match
        else if(NonTerminalRows.find(stack.top()) != NonTerminalRows.end())
        {
            //No path
            if(token.GetLexeme()!="$" && Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetType()]).empty())
                token=NextToken->getNextToken();
            //Going to epsilon
            else if(Table[NonTerminalRows[stack.top()]][TerminalColumns[token.GetType()]]==epsilon)
                stack.pop();
            //Another production
            else
            {
                string LastTop=stack.top();
                stack.pop();
                for(int i = Table.at(NonTerminalRows[LastTop]).at(TerminalColumns[token.GetType()]).size()-1; i >= 0 ; --i)
                    stack.push(Table.at(NonTerminalRows[LastTop]).at(TerminalColumns[token.GetType()]).at(i));
                if(Table.at(NonTerminalRows[LastTop]).at(TerminalColumns[token.GetType()]).size()>0 && Table.at(NonTerminalRows[LastTop]).at(TerminalColumns[token.GetType()]).at(0)!="synch")
                {
                    for(int i = 0; i < Table.at(NonTerminalRows[LastTop]).at(TerminalColumns[token.GetType()]).size() ; ++i)
                        answer+=Table.at(NonTerminalRows[LastTop]).at(TerminalColumns[token.GetType()]).at(i)+" ";
                    answer+="\n";
                }
            }
        }//Top of stack is terminal and not matching
        else
            stack.pop();
    }
    WriteResult(answer, outPath);
}

