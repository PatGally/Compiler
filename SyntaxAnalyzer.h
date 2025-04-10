/*
* CSC4450 - HW 4 Part 2 - Syntax Analyzer
* Members: Patrick Gallavan, Emma Camp, Aksel Del Toro
* Build a Syntax Analyzer that reads token : lexeme pairs from a source file,
* checks for valid syntax based on the language's grammar, and reports any
* syntax errors with the specific token/lexeme that caused them.
* Also builds a symbol table for declared variables and their types.
*/
#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H
#include <iostream>
#include <vector>
#include <map>
using namespace std;
class SyntaxAnalyzer{
private:
    vector<string> lexemes;
    vector<string> tokens;
    vector<string>::iterator lexitr;
    vector<string>::iterator tokitr;
    // map of variables and their datatype
    // i.e. sum t_integer
    map<string, string> symboltable;
    // other private methods
    bool declarationCheck();
    //Emma and Patrick
    bool vdecassign();
    //   Aksel
    bool stmtlist();
    //    Emma
    int stmt();
    //    Patrick
    bool ifstmt();
    //    Aksel
    bool elsepart();
    //    Emma
    bool whilestmt();
    //    Patrick
    bool assignstmt();
    //    Aksel
    bool inputstmt();
    //    Patrick
    bool outputstmt();
    //    Emma
    bool expr();
    //    Patrick
    bool simpleexpr();
    //    Aksel
    bool term();
    //    Emma
    bool logicop();
    //    Emma
    bool arithop();
    //    Aksel
    bool relop();
    //    Patrick

public:
    SyntaxAnalyzer(istream& infile);
    // pre: 1st parameter consists of an open file containing a source code's
    //	valid scanner/lexical analyzer output.  This data must be in the form: token : lexeme
    // post: the vectors have been populated

    bool parse();
    // pre: none
    // post: The lexemes/tokens have been parsed.
    // If an error occurs, a message prints indicating the token/lexeme pair
    // that caused the error.
    // If no error, vectors contain syntactically correct source code
};



#endif //SYNTAXANALYZER_H
