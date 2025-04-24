/*
*Patrick Gallavan, Emma Camp, Aksel Del Toro
 * Sent in a file of lexemes and a file of variable types of a program to be compiled. This program, compiles the files
 * into a instruction table to be later executed during run time. After run time it will output the contents of the
 * symbol table, and variable table as well as the contents of the instruction table.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;




class Expr;
class Stmt;


int pc;
vector<string> lexemes;
vector<string> tokens;
vector<string>::iterator lexitr;
vector<string>::iterator tokitr;
map<string, string> vartable;
vector<Stmt *> insttable;
map<string, string> symboltable;
map<string, int> precMap;


void dump();

class Expr{
public:
	virtual string toString() = 0;
	virtual ~Expr(){}
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

class StrIdExpr : public Expr{
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
	//Emma
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
	string toString() {
		return id;
	}
	string getId(){
		return id;
	}

};

class IntPostFixExpr : public Expr{
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
			if (vartable.find(token) != vartable.end() && isdigit(vartable[token][0])) {
				tempNumHolder.push_back(stoi(vartable[token]));
			}
		    else if (isdigit(token[0])) {
  				tempNumHolder.push_back(stoi(token));
			}
			else if (isOperator(token)) {
				int b = tempNumHolder.back();
				tempNumHolder.pop_back();
				int a = tempNumHolder.back();
				tempNumHolder.pop_back();
				if (vartable.find(to_string(a)) != vartable.end() && vartable.find(to_string(b)) != vartable.end()) {
					a = stoi(vartable[to_string(a)]);
					b = stoi(vartable[to_string(b)]);
				}
				else if (vartable.find(to_string(a)) != vartable.end()) {
					a = stoi(vartable[to_string(a)]);
				}
				else if (vartable.find(to_string(b)) != vartable.end()) {
					b = stoi(vartable[to_string(b)]);
				}

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
	string* eval() {
		string* result = new string();
		vector<string> tempStack;

		for (const string& token : exprs) {
			if (isOperator(token)) {
				string b = tempStack.back();
				string* tempB = &b;
				tempStack.pop_back();
				string a = tempStack.back();
				string* tempA = &a;
				tempStack.pop_back();

				if (vartable.find(*tempA) != vartable.end() && vartable.find(*tempB) != vartable.end()) {
                    *tempA = vartable[*tempA];
					*tempB = vartable[*tempB];
                }
				else if (vartable.find(*tempA) != vartable.end()) {
                    *tempA = vartable[*tempA];
                }
                else if (vartable.find(*tempB) != vartable.end()) {
                    *tempB = vartable[*tempB];
                }

				if (*tempB == "nullptr") {
					tempB = nullptr;
				}
				if (*tempA == "nullptr") {
					tempA = nullptr;
				}

				if (token == "==") {
					if (tempA == nullptr || tempB == nullptr) {
						tempStack.push_back("nullptr");
					}
					else {
						tempStack.push_back(*tempA == *tempB ? "" : "nullptr");
					}
				} else if (token == "!=") {
					if (tempA == nullptr || tempB == nullptr) {
						tempStack.push_back("nullptr");
					}
					else {
						tempStack.push_back(*tempA == *tempB ? "" : "nullptr");
					}
				}
				else if (token == "<") {
					if (tempA == nullptr || tempB == nullptr) {
						tempStack.push_back("nullptr");
					}
					else {
						tempStack.push_back(*tempA < *tempB ? "" : "nullptr");
					}
                }
                else if (token == ">") {
                	if (tempA == nullptr || tempB == nullptr) {
                		tempStack.push_back("nullptr");
                	}
                	else {
                		tempStack.push_back(*tempA > *tempB ? "" : "nullptr");
                	}
                }
                else if (token == "<=") {
                	if (tempA == nullptr || tempB == nullptr) {
                		tempStack.push_back("nullptr");
                	}
                	else {
                		tempStack.push_back(*tempA <= *tempB ? "" : "nullptr");
                	}
                }
                else if (token == ">=") {
                	if (tempA == nullptr || tempB == nullptr) {
                		tempStack.push_back("nullptr");
                	}
                	else {
                		tempStack.push_back(*tempA >= *tempB ? "" : "nullptr");
                	}
                }
                else if (token == "and") {
                	if (tempA == nullptr || tempB == nullptr) {
                		tempStack.push_back("nullptr");
                	}
                	else {
                		tempStack.push_back((!a.empty() && !b.empty()) ? "" : "nullptr");}
                	}
                else if (token == "or") {
                	if (tempA == nullptr || tempB == nullptr) {
                		tempStack.push_back("nullptr");
                	}
                	else {
                		tempStack.push_back(!a.empty() || !b.empty() ? "" : "nullptr");
                	}
                }
				else if (token == "+") {
					if (tempA == nullptr || tempB == nullptr) {
						tempStack.push_back("nullptr");
					}
					else {
						tempStack.push_back(*tempA + *tempB);
					}
				}
				else {
				tempStack.push_back(token);
				}
			} else {
				tempStack.push_back(token);
			}
		}

		if (!tempStack.empty()) {
			*result = tempStack.back();
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

class Stmt {
private:
	string name;
public:
	Stmt(string stmtName){name  = stmtName;}
	virtual ~Stmt(){};
	virtual string toString() = 0;
	virtual void execute() = 0;
	string getName(){
		return name;
	}
};

class AssignStmt : public Stmt{ // Stores pointer to expression
//Patrick
private:
	string var;
	Expr* p_expr;
public:
	AssignStmt(string id, Expr* expr) :Stmt("AssignStmt"){
        var = id;
        p_expr = expr;
	}
	~AssignStmt(){
		if (p_expr == nullptr)
			delete p_expr;
    }
	string toString(){
        return getName() + var + " = " + p_expr->toString();
    }
	void execute() {
		if (dynamic_cast<IntegerConstExpr*>(p_expr)) {
			vartable[var] = to_string(dynamic_cast<IntegerConstExpr*>(p_expr)->eval());
		}
		else if (dynamic_cast<StringConstExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<StringConstExpr*>(p_expr)->eval();
		}
		else if (dynamic_cast<IntIdExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<IntIdExpr*>(p_expr)->getId();
		}
		else if (dynamic_cast<StrIdExpr*>(p_expr)) {
			vartable[var] = dynamic_cast<StrIdExpr*>(p_expr)->getId();
		}
		else if (dynamic_cast<IntPostFixExpr*>(p_expr)) {
			vartable[var] = to_string(dynamic_cast<IntPostFixExpr*>(p_expr)->eval());
		}
		else if (dynamic_cast<StrPostFixExpr*>(p_expr)) {
			string* postfix = (dynamic_cast<StrPostFixExpr*>(p_expr)->eval());
			vartable[var] = *postfix;
			delete postfix;
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
	InputStmt() : Stmt("InputStmt"){}
	~InputStmt(){}
	void setVar(string v){
       var = v;
    }
    string getVar(){
      return var;
    }
	string toString(){
       return getName() + var;
    }
	void execute() {
		cout << "Enter value for: " << var << endl;
		string val;
		cin >> val;
		bool isInteger = false;
		if (symboltable.find(var) != symboltable.end()) {
			if (symboltable[var] == "t_integer") {
				for (int i = 0; i < val.length(); i++) {
					if (isdigit(val[i])) {
						isInteger = true;
					}
				}
				if (isInteger) {
					vartable[var] = val;
				}
				else {
					cerr << "Error: Input value is not an integer." << endl;
					return;
				}
			}
			else {
				vartable[var] = val;
			}
			++pc;
		}
	}
};

class StrOutStmt : public Stmt {
	//Aksel
	private:
		string value;
	public:
		StrOutStmt(string& val) : Stmt("StrOutStmt") {
			value = val;
		}
		~StrOutStmt() {

		}
		string toString() {
			return getName() + value;
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
	ExprOutStmt(Expr* expr) : Stmt("ExprOutStmt"){
        p_expr = expr;
    }
	~ExprOutStmt(){
		if (p_expr == nullptr)
          delete p_expr;
	}
	string toString (){
        return getName() + p_expr->toString();
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
			string* result = dynamic_cast<StrPostFixExpr*>(p_expr)->eval();
			if (*result == "nullptr") {
				cout << "FALSE" << endl;
			}
			else {
				cout << *result << endl;
			}
			delete result;
		}
		else if (dynamic_cast<StrIdExpr*>(p_expr)) {
			cout << dynamic_cast<StrIdExpr*>(p_expr)->getId() << endl;
		}
		else if (dynamic_cast<IntIdExpr*>(p_expr)) {
			cout << dynamic_cast<IntIdExpr*>(p_expr)->getId() << endl;
		}
		pc++;
	}
};

class GoToStmt : public Stmt{
	//Emma
private:
	int target;
public:
	GoToStmt() : Stmt("GoToStmt"){
		target = 0;
	}
	~GoToStmt(){}
	void setTarget(int t){
		target = t;
	}
	string toString(){
		return getName() + to_string(target);
	}
	void execute(){
		pc = target;
	}

};

class IfStmt : public Stmt{
  // Emma
private:
	Expr* p_expr;
	int elsetarget ;
public:
	IfStmt() : Stmt("IfStmt"){}
	~IfStmt(){
		if (p_expr == nullptr)
			delete p_expr;

	}
	string toString(){
       return getName() + p_expr->toString() + " goto ";
     }
	void execute() {
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
                pc++;
            } else {
            	pc = elsetarget;
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
        		++pc;
      		} else {
      			pc = elsetarget;
       }
    } else if (strPostFixExpr) {
      string* val = strPostFixExpr->eval();
      if (*val == "") {
        ++pc;
      } else {
      	pc = elsetarget;
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
	WhileStmt() : Stmt("WhileStmt"){
		p_expr = nullptr;
		elsetarget = 0;
	}
    WhileStmt(Expr* expr, int target) : Stmt("WhileStmt"){
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
		return getName() + p_expr->toString() + " goto " + to_string(elsetarget);
	}
	void execute() {
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
            if (val == "") {
                ++pc;
            } else {
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
        	string* val = strPostFixExpr->eval();
        	if (*val == "") {
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
	}
};


class Compiler{
private:
	void buildIf(){
		//Emma
       ++tokitr;
       ++lexitr;
		++tokitr;
       ++lexitr;
		Expr* condition = buildExpr();
       ++tokitr;
		++lexitr;

       IfStmt* ifstmt = new IfStmt();
       ifstmt -> setExpr(condition);
       ifstmt -> setTarget(0);
       insttable.push_back(ifstmt);
		while(*tokitr != "s_rbrace"){
			buildStmt();
		}
		tokitr++; lexitr++;
		GoToStmt* gotostmt = new GoToStmt();
		insttable.push_back(gotostmt);
		ifstmt->setTarget(insttable.size());
		if(*tokitr == "t_else"){
			tokitr++; lexitr++;
			tokitr++; lexitr++;
			while(*tokitr != "s_rbrace"){
				buildStmt();
			}
			tokitr++; lexitr++;
			gotostmt->setTarget(insttable.size());
		}



    }

	void buildWhile() {
		//Aksel
		++tokitr;
		++lexitr;
		++tokitr;
		++lexitr;

		Expr* condition = buildExpr();

		WhileStmt* whileStmt = new WhileStmt(condition, 0);
		insttable.push_back(whileStmt);

		++tokitr;
		++lexitr;

		while (*tokitr != "s_rbrace") {
			buildStmt();
		}

		++tokitr;
		++lexitr;

		int jumpTarget = insttable.size();
		whileStmt->setTarget(jumpTarget);
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
		tokitr++; lexitr++;
        tokitr++; lexitr++;
        Expr* expr = buildExpr();
        tokitr++; lexitr++;
        AssignStmt* assign = new AssignStmt(id, expr);
        insttable.push_back(assign);
	}
	void buildInput(){
		//Aksel
      ++tokitr;++lexitr;
	  ++tokitr;++lexitr;
      string var = *lexitr;
      InputStmt* input = new InputStmt();
      input->setVar(var);
      insttable.push_back(input);
	  ++tokitr;++lexitr;
	  ++tokitr;++lexitr;
    }
	void buildOutput(){
		//Patrick
		tokitr++; lexitr++;
		tokitr++; lexitr++;
		auto nextTok = ++tokitr;
		tokitr--;
        if(*tokitr == "t_text" && *nextTok == "s_rparen"){
          	string text = *lexitr;
            tokitr++; lexitr++;
        	StrOutStmt* strout = new StrOutStmt(text);
            insttable.push_back(strout);
        }
        else{
         	Expr* expr = buildExpr();
         	ExprOutStmt* strout = new ExprOutStmt(expr);
            insttable.push_back(strout);
        }
		if(*tokitr == "s_rparen"){
			tokitr++; lexitr++;
		}
	}

	Expr* buildExpr() {
		//Aksel
		vector<string> outputQueue;
		vector<string> opStack;
		bool hasInt = false;
		bool hasStr = false;

		string firstToken = *tokitr;
		string firstLexeme = *lexitr;

		auto lookaheadTok = tokitr;
		auto lookaheadLex = lexitr;
		++lookaheadTok;
		++lookaheadLex;

		if (firstToken == "t_text" && *lookaheadTok == "s_rparen") {
			string val = *lexitr;
			++tokitr; ++lexitr;
			return new StringConstExpr(val);
		}
		if (firstToken == "t_number" && *lookaheadTok == "s_rparen") {
			string val = *lexitr;
			++tokitr; ++lexitr;
			return new IntegerConstExpr(stoi(val));
		}

		if (firstToken == "t_id" && *lookaheadTok == "s_rparen") {
			string varName = *lexitr;
			++tokitr; ++lexitr;
			if (symboltable.find(varName) != symboltable.end()) {
				if (symboltable[varName] == "t_string") {
					return new StrIdExpr(varName);
				} else {
					return new IntIdExpr(varName);
				}
			}
		}
		int parenthesis = 0;
		bool inParan = false;
		while (!inParan && *tokitr != "s_semi") {
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
			else if (token == "s_lparen") {
				opStack.push_back(lexeme);
				++parenthesis;
			}
			else if (precMap.find(lexeme) != precMap.end()) {
				while (!opStack.empty() && precMap[opStack.back()] >= precMap[lexeme]) {
					outputQueue.push_back(opStack.back());
					opStack.pop_back();
				}
				opStack.push_back(lexeme);
			}

			else if (token == "s_rparen") {
				if(parenthesis == 0) {
					inParan = true;
				}
				else{
					while (!opStack.empty() && opStack.back() != "(") {
						outputQueue.push_back(opStack.back());
						opStack.pop_back();
					}

					opStack.pop_back();
					--parenthesis;
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



	void populateTokenLexemes(istream& infile) { //Emma
		string line;
		while (getline(infile, line)) {
			int i = 0;
			bool found = false;
			while (i < line.length() && !found) {
				if (line[i] == ' ') {
					found = true;
				}
				i++;
			}
			if (found) {
				tokens.push_back(line.substr(0, i - 1));
				lexemes.push_back(line.substr(i, line.length()));
			}
		}
		tokitr = tokens.begin();
		lexitr = lexemes.begin();
	};

	void populateSymbolTable(istream& infile){	//Emma
          string id, datatype;
          while (infile >> id >> datatype ) {
            symboltable[id] = datatype;
          }
     }

public:
	Compiler(){}

	Compiler(istream& source, istream& symbols){
		//Patrick
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

		populateTokenLexemes(source);
		populateSymbolTable(symbols);
	}


	bool compile(){ //Patrick
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


	void run(){
		//Aksel
		pc = 0;
		while (pc < insttable.size()) {
			insttable[pc]->execute();
		}
    };
};

void dump(){
	cout << "-------Variable Table-----"<<endl;
	for(const auto & pair : symboltable){
		cout << pair.first <<" "<<pair.second<<endl;
	}
	cout << "\n-------Symbol Table-----"<<endl;
	for(const auto & pair : symboltable){
		cout << pair.first <<" "<<pair.second<<endl;
	}
	cout << "\n-------Instruction Table-----"<<endl;
	for(size_t i = 0; i < insttable.size(); i++){
		cout << i <<" "<<insttable[i] ->toString() <<endl;
	}
	cout << "\n------------------------"<<endl;

}
int main(){
  //emma

	ifstream source("sourcelexemes.txt");
	ifstream symbols("vars.txt");
	 if (!source || !symbols) exit(-1);
	Compiler c(source, symbols);
	c.compile();
	dump();
	c.run();

	return 0;
}