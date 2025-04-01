#include"SyntaxAnalyzer.h"
#include <vector>
#include <unordered_set>
#include <cstddef>

//private methods
bool SyntaxAnalyzer::declarationCheck() {
    // Emma
    std::unordered_set<std::string> declaredVars;
    bool isValid = true;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "t_id") {
            std::string varName = lexemes[i];
            if (i > 1 && (tokens[i-2] == "integer" || tokens[i-2] == "string")){
                declaredVars.insert(varName);
            } else if (!declaredVars.contains(varName)) {
                isValid = false;
            }
        }
    }
    return isValid;
}

bool SyntaxAnalyzer::vdecassign(){
//   Aksel
    if (tokitr != tokens.end() && (*tokitr == "t_integer" || *tokitr == "t_string")) {
        ++tokitr; ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "t_id") {
            ++tokitr; ++lexitr;
            if (tokitr != tokens.end() && *tokitr == "s_assign") {
                ++tokitr; ++lexitr;
                if (tokitr != tokens.end() && expr()) {
                    if (tokitr != tokens.end() && *tokitr == "s_semi") {
                        ++tokitr; ++lexitr;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}bool SyntaxAnalyzer::stmtlist(){
    // Emma - check this
    auto startItr = tokitr;
    bool hasStmt = false;
    while (tokitr != tokens.end() && stmt() ) {
        hasStmt = true;
    }
    if (!hasStmt) {
        if (tokitr == startItr) {
            return true;
        }
        return false;
    }
    return true;
}
int SyntaxAnalyzer::stmt(){
    //    Patrick
    if (tokitr != tokens.end()) return false;
    
    if(ifstmt() || whilestmt() || assignstmt() || inputstmt() || outputstmt() || vdecassign()){
      return true;
    }
    return false;
}

bool SyntaxAnalyzer::ifstmt(){
//    Aksel
    if (tokitr != tokens.end() && *tokitr == "t_if") {
        ++tokitr; ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "s_lparen") {
            ++tokitr; ++lexitr;
            if (expr()) {
                if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                    ++tokitr; ++lexitr;
                    if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                        ++tokitr; ++lexitr;
                        if (stmtlist()) {
                            if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                                ++tokitr; ++lexitr;
                                elsepart();
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
      return false;
}
bool SyntaxAnalyzer::elsepart(){
    // Emma
    if (tokitr != tokens.end() && *tokitr == "t_else") {
        ++tokitr; ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
            ++tokitr; ++lexitr;
            if (stmtlist()) {
                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                    ++tokitr; ++lexitr;
                    return true;
                }
            }
        }
        return false;
    }
      return true; // empty set is valid
}
bool SyntaxAnalyzer::whilestmt(){
     //    Patrick
     if(tokitr != tokens.end()){
       if(*tokitr == "t_while"){
         tokitr++; lexitr++;
         if(tokitr != tokens.end() && *tokitr == "s_lparen"){
            tokitr++; lexitr++;
            if(tokitr != tokens.end() && expr()){
                if(tokitr != tokens.end() && *tokitr == "s_rparen"){
                    tokitr++; lexitr++;
                    if(tokitr != tokens.end() && *tokitr == "s_lbrace"){
                        tokitr++; lexitr++;
                        if(tokitr != tokens.end() && stmtlist()){
                            if(tokitr != tokens.end() && *tokitr == "s_rbrace"){
                              tokitr++; lexitr++;
                              return true;
                            }
                        }
                    }
                }
            }
         }
       }
     }
     return false;
}
bool SyntaxAnalyzer::assignstmt(){
//    Aksel
    if (tokitr != tokens.end() && *tokitr == "t_id") {
        ++tokitr; ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "s_assign") {
            ++tokitr; ++lexitr;
            if (tokitr != tokens.end() && expr()) {
                if (tokitr != tokens.end() && *tokitr == "s_semi") {
                    ++tokitr; ++lexitr;
                    return true;
                }
            }
        }
    }
      return false;
}
bool SyntaxAnalyzer::inputstmt(){
     //    Patrick
     if(tokitr != tokens.end()){
           if(*tokitr == "t_input"){
             tokitr++; lexitr++;
             if(tokitr != tokens.end() && *tokitr == "s_lparen"){
               tokitr++; lexitr++;
               if(tokitr != tokens.end() && *tokitr == "t_id"){
                  tokitr++; lexitr++;
                  if(tokitr != tokens.end() && *tokitr == "s_rparen"){
                    tokitr++; lexitr++;
                    return true;
                  }
               }
             }
           }
     }
     return false;
}
bool SyntaxAnalyzer::outputstmt(){
//    Emma
    if (tokitr != tokens.end() && *tokitr == "t_output") {
        ++tokitr; ++lexitr;
        if (tokitr != tokens.end() && *tokitr == "s_lparen") {
            ++tokitr; ++lexitr;
            if (tokitr != tokens.end() && (expr() || *tokitr == "t_text")) { //check this
                ++tokitr; ++lexitr;
                if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                    ++tokitr; ++lexitr;
                    return true;
                }
            }
        }
    }
      return false;
}
bool SyntaxAnalyzer::expr(){
        //Patrick
     if(tokitr != tokens.end()){
       if(simpleexpr()){
         if(logicop() && simpleexpr()){
           return true;
         }
         if(!logicop() && !simpleexpr()){
             tokitr++; lexitr++;
             return true;
         }
       }
     }
     return false;
}
bool SyntaxAnalyzer::simpleexpr(){
//    Aksel
    if (tokitr != tokens.end() && term()) {
        if (tokitr != tokens.end() && (arithop() || relop())) {
            ++tokitr; ++lexitr;
            if (!term()) {
                return false;
            }
        }
        return true;
    }
      return false;
}
bool SyntaxAnalyzer::term(){
//    Emma
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_number" || *tokitr == "t_id" || *tokitr == "t_text") {
            ++tokitr; ++lexitr;
            return true;
        } else if (*tokitr == "s_lparen") {
            ++tokitr; ++lexitr;
            if (expr()) {
                if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                    ++tokitr; ++lexitr;
                    return true;
                }
            }
        }
    }
      return false;
}
bool SyntaxAnalyzer::logicop(){
//    Emma
    if (tokitr != tokens.end() && (*tokitr == "t_and" || *tokitr == "t_or")) {
        ++tokitr; ++lexitr;
        return true;
    }
      return false;
}
bool SyntaxAnalyzer::arithop(){
//    Aksel
    if (tokitr != tokens.end() && (*tokitr == "s_plus" || *tokitr == "s_minus" || *tokitr == "s_mult")) {
        ++tokitr; ++lexitr;
        return true;
    }
      return false;
}
bool SyntaxAnalyzer::relop(){
  //Patrick
     if(tokitr != tokens.end()){
         if(*tokitr == "s_gt" || *tokitr == "s_lt" || *tokitr == "s_le" || *tokitr == "s_ge"){
             tokitr++; lexitr++;
             return true;
         }
     }
        return false;
}

//TODO: Do not touch syntaxAnalyzer or parse til class on tuesday
SyntaxAnalyzer::SyntaxAnalyzer(std::istream& infile){
    // pre: 1st parameter consists of an open file containing a source code's
    //	valid scanner/lexical analyzer output.  This data must be in the form: token : lexeme
    // post: the vectors have been populated

    if(!infile){
        cout<< "Error in opening file!"<<endl;
    }
    string data;
    while (getline(infile, data)) {
        int position = 0;
        bool found = false;
        int i = 0;

        while (i < data.length() && !found) {
            if (data[i] == ' : ') {
                position = i;
                found = true;
            }
            i++;
        }

        string token = data.substr(0, position);
        string lexeme = data.substr(position + 1, data.length() - position - 1);

        tokens.insert(tokens.end(), token);
        lexemes.insert(lexemes.end(), lexeme);
    }
    tokitr = tokens.begin();
    lexitr = lexemes.begin();

}


    bool SyntaxAnalyzer::parse(){
    // pre: none
    // post: The lexemes/tokens have been parsed.
    // If an error occurs, a message prints indicating the token/lexeme pair
    // that caused the error.
    // If no error, vectors contain syntactically correct source code

    if (tokitr != tokens.end() && *tokitr == "t_main") {
        tokitr++; lexitr++;
        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
            tokitr++; lexitr++;
            if (stmtlist()) {
                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                    return true;
                }
            }
        }
        auto const lineNumber = distance(tokens.begin(), tokitr) + 1;
        if (tokitr != tokens.end()) {
            cout << "Error: " << *tokitr <<  " " << *lexitr << " is invalid on line " << lineNumber<< endl;
        }
        else {
            cout<< "Error reached the end of file while reading on line " << lineNumber << endl;
        }
    }
    return false;
}
