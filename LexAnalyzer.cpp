#include "LexAnalyzer.h"
#include <sstream>
#include <regex>
// pre: parameter refers to open data file consisting of token and
// lexeme pairs i.e.  s_and and t_begin begin t_int 27
// Each pair appears on its own input line.
// post: tokenmap has been populated - key: lexeme, value: token
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
LexAnalyzer::LexAnalyzer(istream& infile) {

  if(!infile){
	cout<< "Error in opening file!"<<endl;
  }

  string data;
  while(getline(infile, data)){
    int position = 0;
    bool found = false;
    int i = 0;
    while( i < data.length() && !found){
      if(data[i] == ' '){
        position = i;
        found = true;
      }
      i++;
    }
    string token = data.substr(0, position);
    string lexeme = data.substr(position + 1, data.length()-1);

    tokenmap.insert({lexeme, token});
  }
}

// pre: 1st parameter refers to an open text file that contains source
// code in the language, 2nd parameter refers to an open empty output
// file
// post: If no error, the token and lexeme pairs for the given input
// file have been written to the output file (token : lexeme).
// If there is an error, the incomplete token/lexeme pairs, as well as
// an error message have been written to the output file.
// A success or fail message has printed to the console.
void LexAnalyzer::scanFile(istream& infile, ostream& outfile) {
    cout << "in scanFile" << endl;

    if (!infile) {
        cout << "Error: Unable to open input file!" << endl;
        outfile << "Error: Unable to open input file!" << endl;
        return;
    }

    string data;
    regex identifier(R"([a-zA-Z_][a-zA-Z0-9_]*)");  // Matches identifiers (variable names, keywords)
    regex number(R"([0-9]+)");                      // Matches numbers
    regex text("\"([^\"]*)\"");                     // Matches string literals inside double quotes
    regex symbols(R"([{}=+*;()<>\-])");               // Matches single-character symbols
    bool found = false;

    while (getline(infile, data)) {
        size_t pos = 0;
        while (pos < data.length()) {
            found = false;
            if (isspace(data[pos])) {
                pos++; // Skip space
                found = true;
            }

            smatch match;
            string remaining = data.substr(pos); // Use a substring from pos to end
            cout <<"remaining: " << remaining<< endl; // see how lines are processed.


            // Check if it's an identifier
            if (!found && regex_search(remaining, match, identifier) && match.position() == 0) {
                if (remaining[0] != '_') {
                    cout << "match: " << match.str() << endl;
                    cout << "identifier: " << match.str() << endl;
                    cout << "-----------------" << endl;
                    string tokenType = (tokenmap.find(match.str()) != tokenmap.end()) ? tokenmap[match.str()] : "t_id";
                    outfile << tokenType << " : " << match.str() << endl;
                    pos += match.length();
                }
                else { // exit code here
                    cerr << "Error Can't start number or identifier with an underscore" << endl;
                    outfile << "Error" << " : " << match.str() << endl;
                    return;
                }
                found = true;
            }

            // Check if it's a number
            if (!found && regex_search(remaining, match, number) && match.position() == 0) {
                cout << "match: " << match.str() << endl;
                cout << "number: " << match.str() << endl;
                cout << "-----------------" << endl;
                outfile << "t_number : " << match.str() << endl;
                pos += match.length();
                found = true;
            }

            // Check if it's text
            if (! found && regex_search(remaining, match, text) && match.position() == 0) {
                cout << "match: " << match.str() << endl;
                cout << "text: " << match.str() << endl;
                cout << "-----------------" << endl;
                outfile << "t_text : " << match.str(1) << endl;
                pos += match.length();
                found = true;
            }

            // check if its symbol
            if (!found && regex_search(remaining, match, symbols) && match.position() == 0) {
                string symbol = match.str();
                if (remaining.substr(0, 2) == "<=") { // skipping over match
                    symbol = "<=";
                } else if (remaining.substr(0, 2) == ">=") {
                    symbol = ">=";
                }
                cout << "match: " << symbol << endl;
                cout << "symbols: " << symbol << endl;
                cout << "-----------------" << endl;
                string tokenType = (tokenmap.find(symbol) != tokenmap.end()) ? tokenmap[symbol] : "s_unknown";
                outfile << tokenType << " : " << symbol << endl;
                pos += symbol.length();
                found = true;

            }

            if (!found){
                // Unknown token
                cout << "Unknown : " << data[pos] << endl;
                outfile << "Unknown : " << data[pos] << endl;
                pos++;
            }

        }
    }
}


