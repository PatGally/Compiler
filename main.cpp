#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>

#include "SyntaxAnalyzer.h"
using namespace std;
#include "LexAnalyzer.h"



int main() {
    //Patrick
    //Syntax Checker
    ifstream sourcelexemesInput("../test.txt");
    SyntaxAnalyzer syntax(sourcelexemesInput);
    syntax.parse();
    sourcelexemesInput.close();
    return 0;
}