#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>
using namespace std;
#include "LexAnalyzer.h"



int main() {
    ifstream lexemes("../lexTokens.txt");
    ifstream source("../source.txt");
    ofstream sourcelexemes("../sourcelexemes.txt");
    LexAnalyzer lexanalyzer(lexemes);
    lexanalyzer.scanFile(source, sourcelexemes);

    lexemes.close();
    source.close();
    return 0;
}