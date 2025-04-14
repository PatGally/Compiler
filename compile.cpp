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
map<string, int> vartable; 	// map of variables and their values
vector<Stmt *> insttable; 		// table of instructions
map<string, string> symboltable; // map of variables to datatype (i.e. sum t_integer)


// Runtime Global Methods
void dump(); 				// prints vartable, instable, symboltable

// You may need a few additional global methods to manipulate the global variables


// Classes Stmt and Expr
// It is assumed some methods in statement and expression objects will change and
// you may need to add a few new ones.


class Expr{ // expressions are evaluated!
public:
	virtual int eval() = 0;	//Evaluates expression
	virtual string toString() = 0;	//Takes contents of something and displays it through dump
	virtual ~Expr(){}	//Destroys object correctly
};

class ConstExpr : public Expr{	//Does constant expressions, do we need a destructor?
private:
	int value;
public:
	ConstExpr(int val);
	int eval();
	string toString();
};

class IdExpr : public Expr{	//Id expression, you have a variable, need to look for value in variable table
private:
	string id;
public: // Emma
	IdExpr(string s);
	int eval();
	string toString();
};

class InFixExpr : public Expr{	//Might want to change
//Patrick
private:
	vector<Expr *> exprs;
	vector<string> ops;  // tokens of operators
public:
	~InFixExpr(){
       for(Expr* expr: exprs){
         delete expr;
       }
       exprs.clear();
	}
	int eval();
	string toString();
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
       delete p_expr;
	}
	string toString();
	void execute();
};

class InputStmt : public Stmt{
  // Emma
private:
	string var;
public:
	InputStmt();
	~InputStmt();
	string toString();
	void execute();
	void setVar(const std::string& v);

};

class StrOutStmt : public Stmt{
private:
	string value;
public:
// Runtime Global Variables
int pc;// program counter, is incremented after excution method is called or gets assigned to the line it needs to jump or loop up to
vector<string> lexemes;
vector<string> tokens;
vector<string>::iterator lexitr;
vector<string>::iterator tokitr;
map<string, int> vartable; 	// map of variables and their values
vector<Stmt *> insttable; 		// table of instructions
map<string, string> symboltable; // map of variables to datatype (i.e. sum t_integer)


// Runtime Global Methods
void dump(); 				// prints vartable, instable, symboltable

// You may need a few additional global methods to manipulate the global variables


// Classes Stmt and Expr
// It is assumed some methods in statement and expression objects will change and
// you may need to add a few new ones.


class Expr{ // expressions are evaluated!
public:
	virtual int eval() = 0;	//Evaluates expression
	virtual string toString() = 0;	//Takes contents of something and displays it through dump
	virtual ~Expr(){}	//Destroys object correctly
};

class ConstExpr : public Expr{	//Does constant expressions, do we need a destructor?
private:
	int value;
public:
	ConstExpr(int val);
	int eval();
	string toString();
};

class IdExpr : public Expr{	//Id expression, you have a variable, need to look for value in variable table
private:
	string id;
public: // Emma
	IdExpr(string s);
	int eval();
	string toString();
};

class InFixExpr : public Expr{	//Might want to change
//Patrick
private:
	vector<Expr *> exprs;
	vector<string> ops;  // tokens of operators
public:
	~InFixExpr();
	int eval();
	string toString();
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
	AssignStmt(){

	}
	~AssignStmt();
	string toString();
	void execute();
};

class InputStmt : public Stmt{
  // Emma
private:
	string var;
public:
	InputStmt();
	~InputStmt();
	string toString();
	void execute();
};

class StrOutStmt : public Stmt{
private:
	string value;
public:
	StrOutStmt(string val){
        value = val;
    }
	~StrOutStmt();
	string toString();
	void execute();
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
          delete p_expr;
	}
	string toString();
	void execute();
};

class IfStmt : public Stmt{
  // Emma
private:
	Expr* p_expr;
	int elsetarget;
public:
	IfStmt();
	~IfStmt();
	string toString();
	void execute();
    void setExpr(Expr* expr);
    void setTarget(int t);
};

class WhileStmt : public Stmt{
private:
	Expr* p_expr;
	int elsetarget;
public:
	WhileStmt();
	~WhileStmt();
	string toString();
	void execute();
};

class GoToStmt : public Stmt{
  //Emma
private:
	int target;
public:
	GoToStmt();
        //Emma
	~GoToStmt();
	void setTarget();
	string toString();
	void execute();
};

class Compiler{
private:
	void buildIf();
        //Emma
	void buildWhile();
	void buildStmt(){
		//Patrick
        if(*tokitr == "t_if"){
          buildIf();
        }
		else if(*tokitr == "t_while"){
			buildWhile();
		}
		else if(*tokitr == "t_id"){
			buildAssign();
		}
		else if(*tokitr == "t_input"){
			buildInput();
		}
		else if(*tokitr == "t_output"){
			buildOutput();
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
	}
	void buildInput();
	void buildOutput(){
		//Patrick
		tokitr++; lexitr++; //itterate over s_lparen
        if(*tokitr == "t_text"){
          	string text = *lexitr;
            tokitr++; lexitr++; //itterate over t_text
        	StrOutStmt* strout = new StrOutStmt(text);
        }
        else{
         	Expr* expr = buildExpr();
         	ExprOutStmt* strout = new ExprOutStmt(expr);
        }
        tokitr++; lexitr++; //itterate over s_rparen
	}
	// use one of the following buildExpr methods, when using this method, you are resonsible to add the expression to the instruction table
	Expr* buildExpr();
	// headers for populate methods may not change
	void populateTokenLexemes(istream& infile);
	void populateSymbolTable(istream& infile);
        // Emma
public:
	Compiler(){}
	// headers may not change
	Compiler(istream& source, istream& symbols){
		// build precMap - include logical, relational, arithmetic operators

		populateTokenLexemes(source);	//Copy over lexemes data file readin code
		populateSymbolTable(symbols);	//Reading in the symbol table output file in variable name, data type : lexeme, token
	}

	// The compile method is responsible for getting the instruction
	// table built.  It will call the appropriate build methods.
	bool compile();
        //Patrick
	// The run method will execute the code in the instruction
	// table.
	void run();
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
void Compiler::buildIf(){
  tokitr++;
  ++lexitr;
  Expr* condition = nullptr;
  buildExpr(condition);
  if(*tokitr == "t_jump"){
    cerr<<"Incorrect Syntax"<<endl;
    exit(-1);
  }
  ++tokitr;
  int line = stoi(*lexitr);
  ++lexitr;

  IfStmt* ifstmt = new IfStmt();
  ifstmt-> setExpr(condition);
  ifstmt-> setTarget(line);
  insttable.push_back(ifstmt);
}
void Compiler::buildInput(){
  ++tokitr;
  string var = *lexitr;
  ++lexitr;

  InputStmt* input = new InputStmt();
  input-> setVar(var);
  insttable.push_back(input);
}
InputStmt :: InputStmt(){}
InputStmt :: ~InputStmt(){}


void InputStmt::setVar(const string& v){
  var = v;
}
string InputStmt::toString(){
  return "Input" + var;
}
void InputStmt::execute(){
  cout << "Enter Value For: " << var << endl;
  int val;
  cin >> val;
  vartable[var] = val;
  ++pc;
}


ConstExpr::ConstExpr(int val){
  value = val;
}
int ConstExpr::eval(){
  return value;
}
string ConstExpr::toString(){
  return to_string(value);
}
IdExpr::IdExpr(string s){
  id = s;
}
IfStmt::IfStmt() {}
IfStmt::~IfStmt() {}

void IfStmt::setExpr(Expr* e) {
	p_expr = e;
}
void IfStmt::setTarget(int line) {
	elsetarget = line;
}
string IfStmt::toString() {
	return "If condition -> " + p_expr->toString() + " goto " + to_string(elsetarget);
}
void IfStmt::execute() {
	if (p_expr->eval() == 0) {
		pc = elsetarget;
	} else {
		++pc;
	}
}
int IdExpr::eval(){
  if(vartable.find(id) != vartable.end()){
    return vartable[id];
  } else {
    cerr<<"Error: Variable not initialized"<<endl;
    exit(-1);
  }

}