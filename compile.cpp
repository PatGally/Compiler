#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// You will need these forward references.
class Expr;
class Stmt;

// Runtime Global Variables
int pc;  // program counter, is incremented after excution method is called or gets assigned to the line it needs to jump or loop up to
vector<string> lexemes;
vector<string> tokens;
vector<string>::iterator lexitr;
vector<string>::iterator tokitr;
map<string, string> vartable; 	// map of variables and their values
vector<Stmt *> insttable; 		// table of instructions
map<string, string> symboltable; // map of variables to datatype (i.e. sum t_integer) variable name : datatype
map<string, int> precMap; // map of operator precedence


// Runtime Global Methods
void dump(); 				// prints vartable, instable, symboltable

// You may need a few additional global methods to manipulate the global variables


// Classes Stmt and Expr
// It is assumed some methods in statement and expression objects will change and
// you may need to add a few new ones.

class Expr{ // expressions are evaluated!
public:
	virtual string toString() = 0;	//Takes contents of something and displays it through dump
	virtual ~Expr(){}	//Destroys object correctly
};

class IntegerConstExpr : public Expr{
	//Aksel
private:
	int value;
public:
	IntegerConstExpr(int val){
       value = val;
    }
	int eval(){
      return value;
    }
	string toString(){
      return to_string(value);
    }
};
class StringConstExpr : public Expr{
	//Aksel
private:
	string value;
public:
	StringConstExpr(string val) {
		value = val;
	}
	string eval() {
		return value;
	}
	string toString() {
		return value;
	}
};

class StrIdExpr : public Expr{	//Id expression, you have a variable, need to look for value in variable table
private:
	string id;
public: // Emma
	StrIdExpr(string s){
       id = s;
    }

	string eval(){
       if(vartable.find(id) != vartable.end()){
         return vartable[id];
       } else {
         cerr<<"Error:"<<id<<endl;
         return 0;
         }
    }
	string toString(){
       return id;
    }
   string getId(){
     return id;
   }
};
class IntIdExpr : public Expr{
private:
    string id;
public:
  IntIdExpr(string val){
    id = val;
  }
  int eval(){
    if(vartable.find(id) != vartable.end()){
    	return std::stoi(vartable[id]);
    } else {
      cerr<<"Error:"<<id<<endl;
      return 0;
    }
  }
  string getId(){
    return id;
  }
};

class IntPostFixExpr : public Expr{	//Might want to change
//Patrick
private:
	vector<string> exprs;

	bool isOperator(string term) {
		if (precMap.find(term) != precMap.end()) {
			return true;
		}
		return false;
	}
	int applyOperator(int a, int b, string oper) {
		if (oper == "+") {
			return a + b;
		}
		else if (oper == "-") {
			return a - b;
		}
		else if (oper == "*") {
			return a * b;
		}
		else if (oper == "/") {
			return a / b;
		}
		else if (oper == "and") {
			return a && b;
		}
		else if (oper == "or") {
			return a || b;
		}
		else if (oper == "<") {
			return a < b;
		}
		else if (oper == ">") {
			return a > b;
		}
		else if (oper == "<=") {
			return a <= b;
		}
		else if (oper == ">=") {
			return a >= b;
		}
		else if (oper == "==") {
			return a == b;
		}
		else if (oper == "!=") {
			return a != b;
		}
		return 0;
	}
public:
	IntPostFixExpr(vector<string> exp) {
		for (int i = 0; i < exp.size(); ++i) {
            exprs.push_back(exp[i]);
        }
	}
	~IntPostFixExpr(){
        exprs.clear();
    }
	int eval() {
		vector<int> tempNumHolder;
		int result = 0;
		for (const string& token : exprs) {
			if (isdigit(token[0])) {
				tempNumHolder.push_back(stoi(token));
			}
			else if (isOperator(token)) {
				int b = tempNumHolder.back();
				tempNumHolder.pop_back();
				int a = tempNumHolder.back();
				tempNumHolder.pop_back();
				result = applyOperator(a, b, token);
				tempNumHolder.push_back(result);
			}
		}
		return result;
	}
	string toString(){
        string result = "";
		for (int i = 0; i < exprs.size(); ++i) {
            result += exprs[i];
        }
		return result;
    }
};
class StrPostFixExpr : public Expr{	//Might want to change
//Patrick
private:
	vector<string> exprs;

	bool isOperator(string term) {
		if (precMap.find(term) != precMap.end()) {
			return true;
		}
		return false;
	}
public:
	StrPostFixExpr(vector<string> exp) {
        for (int i = 0; i < exp.size(); ++i) {
            exprs.push_back(exp[i]);
        }
    }
	~StrPostFixExpr() {
		exprs.clear();
	}
	string eval() {
		string result = "";
		vector<string> tempStack;

		for (const string& token : exprs) {
			if (isOperator(token)) {
				string b = tempStack.back();
				tempStack.pop_back();
				string a = tempStack.back();
				tempStack.pop_back();

				if (token == "==") {
					tempStack.push_back(a == b ? "" : nullptr);
				} else if (token == "!=") {
					tempStack.push_back(a != b ? "" : nullptr);
				}
				else if (token == "<") {
                    tempStack.push_back(a < b ? "" : nullptr);
                }
                else if (token == ">") {
                    tempStack.push_back(a > b ? "" : nullptr);
                }
                else if (token == "<=") {
                    tempStack.push_back(a <= b ? "" : nullptr);
                }
                else if (token == ">=") {
                    tempStack.push_back(a >= b ? "" : nullptr);
                }
                else if (token == "and") {
                	tempStack.push_back((!a.empty() && !b.empty()) ? "" : nullptr);}
                else if (token == "or") {
                    tempStack.push_back(!a.empty() || !b.empty() ? "" : nullptr);
                }
				else if (token == "+") {
					tempStack.push_back(a + b ? "" : nullptr);
				}
				else {
				tempStack.push_back(token);
				}
			} else {
				tempStack.push_back(token);
			}
		}

		if (!tempStack.empty()) {
			result = tempStack.back();
		}
		return result;
	}

	string toString(){
		string result = "";
		for (int i = 0; i < exprs.size(); ++i) {
            result += exprs[i];
        }
		return result;
    }

};

class Stmt {// statements are executed!
private:
	string name;
public:
	Stmt(){}
	virtual ~Stmt(){};
	virtual string toString() = 0;
	virtual void execute() = 0;
};

class AssignStmt : public Stmt{ // Stores pointer to expression
//Patrick
private:
	string var;
	Expr* p_expr;
public:
	AssignStmt(string id, Expr* expr){
        var = id;
        p_expr = expr;
	}
	~AssignStmt(){
		if (p_expr == nullptr)
			delete p_expr;
    }
	string toString(){
        return "Assign " + var + " = " + p_expr->toString();
    }
	void execute() {
		if (dynamic_cast<IntegerConstExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<IntegerConstExpr*>(p_expr)->eval();
		}
		else if (dynamic_cast<StringConstExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<StringConstExpr*>(p_expr)->eval();
		}
		else if (dynamic_cast<IntIdExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<IntIdExpr*>(p_expr)->getId();
		}
		else if (dynamic_cast<StrIdExpr*>(p_expr)) {
			vartable[var] = vartable[dynamic_cast<StrIdExpr*>(p_expr)->getId()];
		}
		else if (dynamic_cast<IntPostFixExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<IntPostFixExpr*>(p_expr)->eval();
		}
		else if (dynamic_cast<StrPostFixExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<StrPostFixExpr*>(p_expr)->eval();
		}
		else {
			cerr << "Error: Invalid expression type" << endl;
			exit(-1);
		}
		pc++;
	}
};

class InputStmt : public Stmt{
  // Emma
private:
	string var;
public:
	InputStmt();
	~InputStmt();
	void setVar(const string& v){
       var = v;
    }
    string getVar(){
      return var;
    }
	string toString(){
       return "Input" + var;
    }
	void execute(){
       cout << "Enter value for: " << var << endl;
       int val;
       cin >> val;
       cin >> val;
       vartable[var] = val;
       ++pc;
    }
};

class StrOutStmt : public Stmt {
	//Aksel
	private:
		string value;
	public:
		StrOutStmt(const string& val) {
			value = val;
		}
		~StrOutStmt() {

		}
		string toString() {
			return "Output" + value;
		}
		void execute() {
			cout << value << endl;
			++pc;
		}
        string getVar(){
          return value;
        }

        string getExpr(){
          return value;
        }


};

class ExprOutStmt : public Stmt{
  //Patrick
private:
	Expr* p_expr;
public:
	ExprOutStmt(Expr* expr){
        p_expr = expr;
    }
	~ExprOutStmt(){
		if (p_expr == nullptr)
          delete p_expr;
	}
	string toString (){
        return "Output " + p_expr->toString();
    }
	void execute(){
		if (dynamic_cast<IntegerConstExpr*>(p_expr)) {
			cout << dynamic_cast<IntegerConstExpr*>(p_expr)->eval() << endl;
		}
		else if (dynamic_cast<IntPostFixExpr*>(p_expr)) {
			cout << dynamic_cast<IntPostFixExpr*>(p_expr)->eval() << endl;
		}
		else if (dynamic_cast<StringConstExpr*>(p_expr)) {
			cout << dynamic_cast<StringConstExpr*>(p_expr)->eval() << endl;
		}
		else if (dynamic_cast<StrPostFixExpr*>(p_expr)) {
			cout << dynamic_cast<StrPostFixExpr*>(p_expr)->eval() << endl;
		}
		else if (dynamic_cast<StrIdExpr*>(p_expr)) {
			cout << vartable[dynamic_cast<StrIdExpr*>(p_expr)->getId()] << endl;
		}
		else if (dynamic_cast<IntIdExpr*>(p_expr)) {
			cout << dynamic_cast<IntIdExpr*>(p_expr)->getId() << endl;
		}
		pc++;
	}
};

class IfStmt : public Stmt{
  // Emma
private:
	Expr* p_expr;
	int elsetarget;
public:
	IfStmt(){}
	~IfStmt(){
      if (p_expr == nullptr) {
        delete p_expr;
      }
	}
	string toString(){
       return "If " + p_expr->toString() + " goto ";
     }
	void execute() {	//Check for the other 4 expressions -> done
	IntegerConstExpr* intExpr = dynamic_cast<IntegerConstExpr*>(p_expr);
	StringConstExpr* strExpr = dynamic_cast<StringConstExpr*>(p_expr);
	IntIdExpr* intIdExpr = dynamic_cast<IntIdExpr*>(p_expr);
	StrIdExpr* strIdExpr = dynamic_cast<StrIdExpr*>(p_expr);
    StrPostFixExpr* strPostFixExpr = dynamic_cast<StrPostFixExpr*>(p_expr);
    IntPostFixExpr* IntpostFixExpr = dynamic_cast<IntPostFixExpr*>(p_expr);
    if (intExpr) {
        int val = intExpr->eval();
        if (val == 0) {
            pc = elsetarget;
        } else {
            ++pc;
        }
    } else if (strExpr) {
        string val = strExpr->eval();
            if (val == "") {
                pc = elsetarget;
            } else {
              ++pc;
        }
    } else if (intIdExpr) {
      	int val = intIdExpr->eval();
      		if (val == 0) {
        	  pc = elsetarget;
      		} else{
        	  ++pc;
      	}
    } else if (strIdExpr) {
      string val = strIdExpr->eval();
      		if (val == "") {
        		pc = elsetarget;
      		} else {
              ++pc;
       }
    } else if (strPostFixExpr) {
      string val = strPostFixExpr->eval();
      if (val == "") {
        pc = elsetarget;
      } else {
        ++pc;
        }
    } else if (IntpostFixExpr) {
      int val = IntpostFixExpr->eval();
      if (val == 0) {
        pc = elsetarget;
      } else {
        ++pc;
        }
    }
}
    void setExpr(Expr* expr){
      p_expr = expr;
    }


    void setTarget(int t){
      elsetarget = t;
    }
};

class WhileStmt : public Stmt{
	//Aksel
private:
	Expr* p_expr;
	int elsetarget;
public:
	WhileStmt(){
		p_expr = nullptr;
		elsetarget = 0;
	}
    WhileStmt(Expr* expr, int target){
      p_expr = expr;
      elsetarget = target;

    }
	~WhileStmt(){
        if (p_expr == nullptr)
		delete p_expr;
	}

	void setTarget(int target) {
		elsetarget = target;
	}
	string toString(){
		return "While " + p_expr->toString() + " goto " + to_string(elsetarget);
	}
	void execute() {	//Check for the other 4 expressions
	    IntegerConstExpr* intExpr = dynamic_cast<IntegerConstExpr*>(p_expr);
        StringConstExpr* strExpr = dynamic_cast<StringConstExpr*>(p_expr);
        IntIdExpr* intIdExpr = dynamic_cast<IntIdExpr*>(p_expr);
        StrIdExpr* strIdExpr = dynamic_cast<StrIdExpr*>(p_expr);
		StrPostFixExpr* strPostFixExpr = dynamic_cast<StrPostFixExpr*>(p_expr);
		IntPostFixExpr* intPostFixExpr = dynamic_cast<IntPostFixExpr*>(p_expr);
	    if (intExpr) {
	        int val = intExpr->eval();
	        if (val == 0) {
	            pc = elsetarget;
	        } else {
			   ++pc;
			}
    	} else if (strExpr) {
        	string val = strExpr->eval();
            if (val == "") {		//this is supposed to increment the program counter when true -> done
                ++pc;
            } else {	//this is supposed to assign the pc to elsetarget -> done
            	pc = elsetarget;
            }
        } else if (intIdExpr) {
            int val = intIdExpr->eval();
            if (val == 0) {
              pc = elsetarget;
            } else {
              ++pc;
          }
        } else if (strIdExpr) {
          string val = strIdExpr->eval();
          if (val == "") {
            ++pc;
          } else {
            pc = elsetarget;
          }
        } else if (strPostFixExpr) {
        	string val = strPostFixExpr->eval();
        	if (val == "") {
        		pc = elsetarget;
        	} else {
        		++pc;
        	}
        } else if (intPostFixExpr) {
        	int val = intPostFixExpr->eval();
        	if (val == 0) {
        		pc = elsetarget;
        	} else {
        		++pc;
        	}
	}
};

class GoToStmt : public Stmt{
  //Emma
private:
	int target;
public:
	GoToStmt(){
       target = 0;
     }
	~GoToStmt(){}
	void setTarget(int t){
       target = t;
    }
	string toString(){
       return "GoTo " + to_string(target);
    }
	void execute(){
      pc = target;
    }

};

class Compiler{
private:
	void buildIf(){
       ++tokitr;
       ++lexitr;
       Expr* condition = nullptr;
       buildExpr();
       if(*tokitr == "t_jump"){
         cerr << "Incorrect Syntax" << endl;
         exit(-1);
       }
       ++tokitr;
       int line = stoi(*tokitr);
       ++lexitr;
       IfStmt* ifstmt = new IfStmt();
       ifstmt -> setExpr(condition);
       ifstmt -> setTarget(line);
       insttable.push_back(ifstmt);

    }

	void buildWhile() {
		//Aksel
		++tokitr; //iterating under t_while
		++lexitr; //iterating under t_while
		++tokitr; //iterating under t_lparen
		++lexitr; //iterating under t_lparen
		Expr* condition = buildExpr();
		WhileStmt whileStmt(condition, 0);
		insttable.push_back(&whileStmt);
		if (*tokitr != "{") {
			cerr << "Error: Expected '{' to start while loop body" << endl;
			return;
		}
		++tokitr;
		++lexitr;
		while (*tokitr != "}") {
			buildStmt();
		}
		if (*tokitr != "}") {
			cerr << "Error: Expected '}' to close while loop body" << endl;
			return;
		}
		int jumpTarget = insttable.size();
		whileStmt.setTarget(jumpTarget);
		++tokitr;
		++lexitr;
	}

	void buildStmt(){
		//Patrick
		while (*tokitr != "s_rbrace") {
			if (*tokitr == "t_if") {
				buildIf();
			} else if (*tokitr == "t_while") {
				buildWhile();
			} else if (*tokitr == "t_id") {
				buildAssign();
			} else if (*tokitr == "t_input") {
				buildInput();
			} else if (*tokitr == "t_output") {
				buildOutput();
			}
		}
	}
	void buildAssign(){
		//Patrick
		string id = *lexitr;
		tokitr++; lexitr++;	//itterates over t_id
        tokitr++; lexitr++;	//itterate over s_assign
        Expr* expr = buildExpr();
        tokitr++; lexitr++;	//itterate over s_semi
        AssignStmt* assign = new AssignStmt(id, expr);
        insttable.push_back(assign);
	}
	void buildInput(){
      ++tokitr;
      string var = *lexitr;
      ++lexitr;
      InputStmt* input = new InputStmt();
      input->setVar(var);
      insttable.push_back(input);
    }
	void buildOutput(){
		//Patrick
		tokitr++; lexitr++; //iterate over s_lparen
        if(*tokitr == "t_text"){
          	string text = *lexitr;
            tokitr++; lexitr++; //iterate over t_text
        	StrOutStmt* strout = new StrOutStmt(text);
            insttable.push_back(strout);
        }
        else{
         	Expr* expr = buildExpr();
         	ExprOutStmt* strout = new ExprOutStmt(expr);
            insttable.push_back(strout);
        }
        tokitr++; lexitr++; //iterate over s_rparen
	}

	Expr* buildExpr() {
		//Aksel
		vector<string> outputQueue;
		vector<string> opStack;
		bool hasInt = false;
		bool hasStr = false;

		while (*tokitr != "s_semi" && *tokitr != "s_rparen") {
			string token = *tokitr;
			string lexeme = *lexitr;

			if (token == "t_number") {
				hasInt = true;
				outputQueue.push_back(lexeme);
			}
			else if (token == "t_text") {
				hasStr = true;
				outputQueue.push_back(lexeme);
			}
			else if (token == "t_id") {
				if (symboltable.find(lexeme) != symboltable.end()) {
					if (symboltable[lexeme] == "t_string") {
						hasStr = true;
					} else {
						hasInt = true;
					}
				}
				outputQueue.push_back(lexeme);
			}
			else if (precMap.find(token) != precMap.end()) {
				// Operator
				while (!opStack.empty() && precMap[opStack.back()] >= precMap[lexeme]) {
					outputQueue.push_back(opStack.back());
					opStack.pop_back();
				}
				opStack.push_back(lexeme);
			}
			else if (token == "s_lparen") {
				opStack.push_back(lexeme);
			}
			else if (token == "s_rparen") {
				while (!opStack.empty() && opStack.back() != "(") {
					outputQueue.push_back(opStack.back());
					opStack.pop_back();
				}
				if (!opStack.empty() && opStack.back() == "(") {
					opStack.pop_back();
				}
			}

			++tokitr;
			++lexitr;
		}

		while (!opStack.empty()) {
			outputQueue.push_back(opStack.back());
			opStack.pop_back();
		}

		if (hasInt && hasStr) {
			cerr << "Type error: cannot mix integers and strings in an expression." << endl;
		}

		if (hasStr) {
			return new StrPostFixExpr(outputQueue);
		} else {
			return new IntPostFixExpr(outputQueue);
		}
	}


	// headers for populate methods may not change
	void populateTokenLexemes(istream& infile){
		//Aksel
		string token, lexeme;
		while (infile >> token >> lexeme) {
			tokens.push_back(token);
			lexemes.push_back(lexeme);
		}

		tokitr = tokens.begin();
		lexitr = lexemes.begin();
    };
	void populateSymbolTable(istream& infile){
          string id, datatype;
          while (infile >> id >> datatype >> datatype) {
            symboltable[id] = datatype;
          }
     }

public:
	Compiler(){}
	// headers may not change
	Compiler(istream& source, istream& symbols){
		// build precMap - include logical, relational, arithmetic operators
		precMap["or"] = 5;
		precMap["and"] = 4;
		precMap["<"] = 3;
		precMap[">"] = 3;
		precMap["<="] = 3;
		precMap[">="] = 3;
		precMap["!="] = 3;
		precMap["=="] = 3;
		precMap["+"] = 2;
		precMap["-"] = 2;
		precMap["*"] = 1;
		precMap["/"] = 1;
		precMap["%"] = 1;

		populateTokenLexemes(source);	//Copy over lexemes data file readin code
		populateSymbolTable(symbols);	//Reading in the symbol table output file in variable name, data type : lexeme, token
	}

	// The compile method is responsible for getting the instruction
	// table built.  It will call the appropriate build methods.
	bool compile(){
		tokitr++; lexitr++; //iterate over t_main
        tokitr++; lexitr++; //iterate over s_lbrace
        buildStmt();
        tokitr++; lexitr++; //iterate over s_rbrace
        if(tokitr != tokens.end()){
            cerr<< "Error: " << *tokitr <<  " " << *lexitr << " is invalid"<<endl;
            return false;
        }
          cout<< "Compile Output Success!"<<endl;
          return true;
	}

	// The run method will execute the code in the instruction
	// table.
	void run(){
		//Aksel
		pc = 0;
		while (pc < insttable.size()) {
			insttable[pc]->execute();
		}
    };
};

// prints vartable, instable, symboltable
void dump();
int main(){

	ifstream source("sourcelexemes.txt");
	ifstream symbols("vars.txt");
	if (!source || !symbols) exit(-1);
	Compiler c(source, symbols);
	c.compile();
	// might want to call dump to check if everything built correctly
	// dump();
	c.run();

	return 0;
}