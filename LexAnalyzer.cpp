#include "LexAnalyzer.h"
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

    tokens.push_back(token);
    lexemes.push_back(lexeme);
    tokenmap.insert({lexeme, token});
  }
  for (const auto& tokenPair : tokenmap) {
        cout << tokenPair.first << " : " << tokenPair.second << endl;
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

}
