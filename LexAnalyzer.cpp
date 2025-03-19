#include "LexAnalyzer.h"
#include <regex>
// pre: parameter refers to open data file consisting of token and
// lexeme pairs i.e.  s_and and t_begin begin t_int 27
// Each pair appears on its own input line.
// post: tokenmap has been populated - key: lexeme, value: token

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

    if (!infile) {
        cout << "Error: Unable to open input file!" << endl;
        outfile << "Error: Unable to open input file!" << endl;
        return;
    }

    string data;
    regex identifier(R"([a-zA-Z_][a-zA-Z0-9_]*)");  // Matches identifiers (variable names, keywords)
    regex number(R"([0-9]+)");                      // Matches numbers
    regex text("\"([^\"]*)\"");                     // Matches string literals inside double quotes
    regex symbols(R"([{}=+*;:,()<>\-])");               // Matches single-character symbols
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


            size_t* pos_argue = &pos;
            ostream* out = &outfile;
            if(!found) {
                // Check if it's an identifier
                try {
                    found = identifierCheck(match, identifier,
                    tokenmap, remaining, out, pos_argue);
                }
                catch (runtime_error& e) {
                    cerr << e.what() << endl;
                    outfile << e.what() << endl;
                    return;
                }
            }

            // Check if it's a number
            try {
                if (!found) {
                    found = numberCheck(match, number, remaining,
                        out, pos_argue);
                    string temp_remain = remaining.substr(1, remaining.length()-1);
                    if (found && (identifierCheck(match, identifier, tokenmap, temp_remain, out, pos_argue)
                        || textCheck(match, text, temp_remain, out, pos_argue))) {
                        throw std::runtime_error("Error: number cannot be followed by invalid lexemes");
                    }
                }
            }
            catch (runtime_error& e) {
                cerr << e.what() << endl;
                outfile << e.what() << endl;
                return;
            }

            // Check if it's text
            if (!found) {
                found =  textCheck(match, text, remaining, out, pos_argue);
            }

            // check if its symbol
            if (!found) {
                found = symbolCheck(match, symbols, remaining, out, pos_argue);
            }

            if (!found){
                // Unknown token
                cerr << "Error: Unknown Lexeme: " << data[pos] << endl;
                outfile << "Error: Unknown Lexeme: " << data[pos] << endl;
                return;
            }
        }
    }
    cout << "Output Success" << endl;
}

bool LexAnalyzer::identifierCheck(smatch match, regex identifier, map<string, string> tokenmap,
        string remaining, ostream* outfile, size_t* pos) {
    if (regex_search(remaining, match, identifier) && match.position() == 0) {
        if (remaining[0] != '_') {
            string tokenType = (tokenmap.find(match.str()) != tokenmap.end()) ? tokenmap[match.str()] : "t_id";
            *outfile << tokenType << " : " << match.str() << endl;
            *pos += match.length();
        }
        else { // exit code here
            throw std::runtime_error("Error Can't start number or identifier with an underscore: " + match.str());
        }
        return true;
    }
    return false;
}
bool LexAnalyzer::numberCheck(smatch match, regex number,
    string remaining, ostream* outfile, size_t* pos) {
    if (regex_search(remaining, match, number) && match.position() == 0) {
        *outfile << "t_number : " << match.str() << endl;
        *pos += match.length();
        return true;
    }
    return false;
}
bool LexAnalyzer::textCheck(smatch match, regex text,
    string remaining, ostream* outfile, size_t* pos) {
    if (regex_search(remaining, match, text) && match.position() == 0) {
        *outfile << "t_text : " << match.str(1) << endl;
        *pos += match.length();
        return true;
    }
    return false;
}
bool LexAnalyzer::symbolCheck(smatch match, regex symbols,
    string remaining, ostream* outfile, size_t* pos) {
    if (regex_search(remaining, match, symbols) && match.position() == 0) {
        string symbol = match.str();
        if (remaining.substr(0, 2) == "<=") { // skipping over match
            symbol = "<=";
        } else if (remaining.substr(0, 2) == ">=") {
            symbol = ">=";
        }
        string tokenType = (tokenmap.find(symbol) != tokenmap.end()) ? tokenmap[symbol] : "s_unknown";
        *outfile << tokenType << " : " << symbol << endl;
        *pos += symbol.length();
        return true;
    }
    return false;
}

