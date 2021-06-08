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
    string answer;
    string output;
    bool error= false;
    while (!stack.empty())
    {
        //Got a match
        if(stack.top()==token.GetType())
        {
            output +="matched "+token.GetLexeme()+"\n";
            answer+=stack.top();
            stack.pop();
            token=NextToken->getNextToken();
        }
        //no match
        else if(NonTerminalRows.find(stack.top()) != NonTerminalRows.end())
        {
            //No path
            if(Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetLexeme()]).empty())
            {
                error = true;
                output+="Error: No path from "+stack.top()+" to "+token.GetLexeme()+"\n";
                output+="discard "+token.GetLexeme()+"\n";
                token=NextToken->getNextToken();
            }
            //Going to epsilon
            else if(Table[NonTerminalRows[stack.top()]][TerminalColumns[token.GetLexeme()]]==epsilon)
                stack.pop();
            //Another production
            else
            {
                stack.pop();
                for(int i = Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetLexeme()]).size()-1; i >= 0 ; --i)
                    stack.push(Table.at(NonTerminalRows[stack.top()]).at(TerminalColumns[token.GetLexeme()]).at(i));
            }
        }//Top of stack is terminal and not matching
        else
        {
            error = true;
            output+="Error: found "+stack.top()+" instead of "+token.GetLexeme().at(0)+"\n";
            output+="inserted"+stack.top()+"\n";
            answer += stack.top();
            stack.pop();
        }
    }
    if(!error)
        output+="inserted string is correct & accepted";
    else
        output+= "inserted string should have been "+answer;
    WriteResult(output, outPath);
}

