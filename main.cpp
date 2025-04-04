#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>

#include "SyntaxAnalyzer.h"
using namespace std;
#include "LexAnalyzer.h"



int main() {
    //Lexical Analyzer
    //Patrick
    ifstream lexemes("../lexTokens.txt");
    ifstream source("../source.txt");
    ofstream sourcelexemes("../sourcelexemes.txt");
    LexAnalyzer lexanalyzer(lexemes);
    lexanalyzer.scanFile(source, sourcelexemes);
    sourcelexemes.close();

    //Syntax Checker
    ifstream sourcelexemesInput("../sourcelexemes.txt");
    ifstream syntaxCheck((move(sourcelexemesInput)));
    SyntaxAnalyzer syntax(syntaxCheck);
    syntax.parse();

    sourcelexemesInput.close();
    lexemes.close();
    source.close();
    syntaxCheck.close();
    return 0;
}