#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>
using namespace std;
#include "LexAnalyzer.h"

const vector<pair<string, regex>> tokenpairs = {
    {"t_and", regex(R"(\band\b)")},
    {"t_or", regex(R"(\bor\b)")},
    {"t_not", regex(R"(\bnot\b)")},
    {"t_true", regex(R"(\btrue\b)")},
    {"t_false", regex(R"(\bfalse\b)")},
    {"t_input", regex(R"(\binput\b)")},
    {"t_output", regex(R"(\boutput\b)")},
    {"t_integer", regex(R"(\binteger\b)")},
    {"t_string", regex(R"(\bstring\b)")},
    {"t_if", regex(R"(\bif\b)")},
    {"t_else", regex(R"(\belse\b)")},
    {"t_while", regex(R"(\bwhile\b)")},
    {"b_main", regex(R"(\bmain\b)")},
    {"s_assign", regex("=")},
    {"s_comma", regex(",")},
    {"s_colon", regex(":")},
    {"s_lparen", regex(R"(\()")},
    {"s_rparen", regex(R"(\))")},
    {"s_semi", regex(";")},
    {"s_lbrace", regex(R"(\{)")},
    {"s_rbrace", regex(R"(\})")},
    {"s_lt", regex("<")},
    {"s_le", regex("<=")},
    {"s_gt", regex(">")},
    {"s_ge", regex(">=")},
    {"s_plus", regex(R"(\+)")},
    {"s_minus", regex("-")},
    {"s_mult", regex(R"(\*)")}
};

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