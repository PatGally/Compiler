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
public:
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
	StrOutStmt();
	~StrOutStmt();
	string toString();
	void execute();
};

class ExprOutStmt : public Stmt{
  //Patrick
private:
	Expr* p_expr;
public:
	ExprOutStmt();
	~ExprOutStmt();
	string toString();
	void execute();
};

class IfStmt : public Stmt{
private:
	Expr* p_expr;
	int elsetarget;
public:
	IfStmt();
	~IfStmt();
	string toString();
	void execute();
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
private:
	int target;
public:
	GoToStmt();
	~GoToStmt();
	void setTarget();
	string toString();
	void execute();
};

class Compiler{
private:
	void buildIf();
	void buildWhile();
	void buildStmt();
        //Patrick
	void buildAssign();
        //Patrick
	void buildInput();
	void buildOutput();
        //Patrick
	// use one of the following buildExpr methods
	void buildExpr(Expr*&);      Expr* buildExpr();
	// headers for populate methods may not change
	void populateTokenLexemes(istream& infile);
	void populateSymbolTable(istream& infile);
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
