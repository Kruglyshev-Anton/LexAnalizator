
#pragma once
#include "Node.h"
#include "HashTable.h"
#include <set>
#include <iostream>
#include <string>
using namespace std;
class SyntaxAnalizator
{
private:
	string lexeme;
	vector<Token> orderedLexems;
	set<string> vars;
	int currentId;
	int currentTagIndex = 1;
	bool isNum(string s);
	bool isName(string s);
	bool isVars();
	void getLexeme();
	void Error(string message);

	void Procedure(Node& n);
	void Begin(Node& n);
	void End(Node& n);
	void ProcedureName(Node& n);
	void Descriptions(Node& n);
	void DescrList(Node& n);
	void DescrList1(Node& n);
	void Descr(Node& n);
	void VarList(Node& n);
	void VarList1(Node& n);
	void Type(Node& n);
	void Operators(Node& n);
	void Operators1(Node& n);
	void Op(Node& n);
	void Expr(Node& n);
	void Expr1(Node& n);
	void SimpleExpr(Node& n);
	void RelationOperators(Node& n);
	void Id(Node& n, bool isNewVar = false);
	void Const(Node& n);


public:
	SyntaxAnalizator(vector<Token> orderedLexems);
	Node process();
};

