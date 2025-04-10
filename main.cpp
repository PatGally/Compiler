#include <fstream>
#include <regex>

#include "SyntaxAnalyzer.h"
using namespace std;



int main() {
    //Patrick
    //Syntax Checker
    ifstream sourcelexemesInput("../test.txt");
    SyntaxAnalyzer syntax(sourcelexemesInput);
    syntax.parse();
    sourcelexemesInput.close();
    return 0;
}