#include"SyntaxAnalyzer.h"

//private methods
bool SyntaxAnalyzer::vdecassign(){
//   Aksel
      return false;
}
bool SyntaxAnalyzer::stmtlist(){
//    Emma
      return false;
}
    int SyntaxAnalyzer::stmt(){
        //    Patrick
      return false;
    }

bool SyntaxAnalyzer::ifstmt(){
//    Aksel
      return false;
}
bool SyntaxAnalyzer::elsepart(){
//    Emma
      return false;
}
    bool SyntaxAnalyzer::whilestmt(){
        //    Patrick
      return false;
    }
bool SyntaxAnalyzer::assignstmt(){
//    Aksel
      return false;
}
    bool SyntaxAnalyzer::inputstmt(){
        //    Patrick
        return false;
    }
bool SyntaxAnalyzer::outputstmt(){
//    Emma
      return false;
}
    bool SyntaxAnalyzer::expr(){
        //    Patrick
        return false;
    }
bool SyntaxAnalyzer::simpleexpr(){
//    Aksel
      return false;
}
bool SyntaxAnalyzer::term(){
//    Emma
      return false;
}
bool SyntaxAnalyzer::logicop(){
//    Emma
      return false;
}
bool SyntaxAnalyzer::arithop(){
//    Aksel
      return false;
}
    bool SyntaxAnalyzer::relop(){
        //    Patrick
        return false;
    }

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
