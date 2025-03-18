#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>
using namespace std;
#include "LexAnalyzer.h"

// const vector<pair<string,regex>> tokenpairs = {
//     {"t_and", regex("\\band\\b")},
//     {"t_or", regex("\\bor\\b")},
//     {"t_not", regex("\\bnot\\b")},
//     {"t_true", regex("\btrue\\b")},
//     {"t_false", regex("\\bfalse\\b")},
//     {"t_input", regex("\\binput\\b")},
//     {"t_output", regex("\\boutput\\b")},
//     {"t_integer", regex("\\binteger\\b")},
//     {"t_string", regex("\\bstring\\b")},
//     {"t_if", regex("\\bif\\b")},
//     {"t_else", regex("\\belse\\b")},
//     {"t_while", regex("\\bwhile\\b")},
//     {"b_main", regex("\\bmain\\b")},
//     {"s_assign", regex("=")},
//     {"s_comma", regex{","}},
//     {"s_colon", regex(":")},
//     {"s_lparen", regex("(")},
//     {"s_lparen", regex(")")},
//     {"s_semi", regex(";")},
//     {"s_lbrace", regex("{")},
//     {"s_rbrace", regex("}")},
//     {"s_lt", regex("<")},
//     {"s_le", regex("<=")},
//     {"s_gt", regex(">")},
//     {"s_ge", regex(">=")},
//     {"s_plus", regex("+")},
//     {"s_minus", regex("-")},
//     {"s_mult", regex("*")}
// };

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