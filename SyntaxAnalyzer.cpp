#include"SyntaxAnalyzer.h"

//private methods
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
}
bool SyntaxAnalyzer::stmtlist(){
    // Emma - check this
    while (tokitr != tokens.end() && stmt() ) {
        return true;
    }
      return false;
}
int SyntaxAnalyzer::stmt(){
    //    Patrick
    if(tokitr != tokens.end() && ifstmt() || whilestmt() || assignstmt() || inputstmt() || outputstmt()){
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
}

    bool SyntaxAnalyzer::parse(){
    // pre: none
    // post: The lexemes/tokens have been parsed.
    // If an error occurs, a message prints indicating the token/lexeme pair
    // that caused the error.
    // If no error, vectors contain syntactically correct source code
    return false;
}
