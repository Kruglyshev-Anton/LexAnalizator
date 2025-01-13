#include "SyntaxAnalizator.h"
#include <algorithm>


bool SyntaxAnalizator::isName(string s)
{
	std::string type(orderedLexems[currentId - 1].type);
	if (type == "ID_NAME")
		return true;
	return false;
}

bool SyntaxAnalizator::isNum(string s)
{
	int state = 0;
	for (char c : s)
	{
		if (state == 0 && c == '0')
			state = 4;
		else if ((state == 0 || state == 1)
			&& isdigit(c))
			state = 1;
		else if ((state == 1 || state == 4) &&
			c == '.')
			state = 2;
		else if ((state == 2 || state == 3)
			&& isdigit(c))
			state = 3;
		else
			return false;
	}
	return (state == 1 || state == 3 || state == 4);
}

void SyntaxAnalizator::getLexeme()
{
	if (currentId >= orderedLexems.size())
	{
		lexeme = "#";
		return;
	}
	lexeme = orderedLexems[currentId].lex;
	currentId++;
}

void SyntaxAnalizator::Procedure(Node& n)
{
	if (lexeme == "procedure")
	{
		// Procedure → Begin Descriptions Operators End
		n.addSon("Begin");
		Begin(n.getSon(0));
		n.addSon("Descriptions");
		Descriptions(n.getSon(1));
		n.addSon("Operators");
		Operators(n.getSon(2));
		n.addSon("End");
		End(n.getSon(3));
		n.trace += n.getSon(0).trace + "\n";
		n.trace += n.getSon(1).trace + "\n";
		n.trace += n.getSon(2).trace + "\n";
		n.trace += n.getSon(3).trace + '\n';

	}
	else Error("Expected : 'procedure'");
}

void SyntaxAnalizator::Begin(Node& n) {
	if (lexeme == "procedure")
	{
		// Begin → procedure ProcedureName ; begin
		n.addSon("procedure");
		getLexeme();
		n.addSon("ProcedureName");
		ProcedureName(n.getSon(1));
		if (lexeme == ";") {
			n.addSon(";");
			getLexeme();
		}
		else {
			Error("Expected : ';'");
		}
		if (lexeme == "begin") {
			n.addSon("begin");
			getLexeme();
		}
		else {
			Error("Expected : 'begin'");
		}
		n.trace += n.getSon(1).trace + " DECL";

	}
	else Error("Expected : 'procedure'");
}

void SyntaxAnalizator::End(Node& n) {
	if (lexeme == "end")
	{
		// End → end
		n.addSon("end");
		getLexeme();
	}
	else Error("Expected : 'end'");
}

void SyntaxAnalizator::ProcedureName(Node& n) {
	if (isName(lexeme))
	{
		// ProcedureName → Id
		n.addSon("Id");
		Id(n.getSon(0), true);
		n.trace += n.getSon(0).trace;
	}
	else Error("Expected : procedure name");
}

void SyntaxAnalizator::Descriptions(Node& n) {
	if (lexeme == "var")
	{
		// Descriptions → var DescrList
		n.addSon("var");
		getLexeme();
		n.addSon("DescrList");
		DescrList(n.getSon(1));
		n.trace += "var " + n.getSon(1).trace;
		if (n.getSon(1).count != 2)
			n.trace += to_string(n.getSon(1).count) + " DECL";
		else
			n.trace += " DECL";
	}
	else Error("Expected : 'var'");
}

void SyntaxAnalizator::DescrList(Node& n) {
	if (isName(lexeme))
	{
		// DescrList → Descr DescrList’
		n.addSon("Descr");
		Descr(n.getSon(0));
		n.addSon("DescrList1");
		DescrList1(n.getSon(1));
		n.count += n.getSon(1).count;
		n.trace += n.getSon(0).trace +" " + n.getSon(1).trace ;
	}
	else Error("Expected : variable name");
}

void SyntaxAnalizator::DescrList1(Node& n) {
	if (lexeme == "for")
	{
		// DescrList’→eps
		n.addSon("eps");
		n.count = 0;
	}
	else if (isName(lexeme)) {
		if (isVars()) {
			// DescrList’→DescrList
			n.addSon("DescrList");
			DescrList(n.getSon(0));
			n.trace = n.getSon(0).trace;
			n.count = n.getSon(0).count;
		}
		else {
			//DescrList’→ eps
			n.addSon("eps");
		}
	}
	else {
		//DescrList’→ eps
		n.addSon("eps");
	}
}

void SyntaxAnalizator::Descr(Node& n) {
	if (isName(lexeme))
	{
		// Descr → VarList : Type ;
		n.addSon("VarList");
		VarList(n.getSon(0));
		if (lexeme == ":") {
			n.addSon(":");
			getLexeme();
		}
		else {
			Error("Excepted : ':'");
		}
		n.addSon("Type");
		Type(n.getSon(2));
		if (lexeme == ";") {
			n.addSon(";");
			getLexeme();
		}
		else {
			Error("Excepted : ';'");
		}
		n.trace += n.getSon(2).trace + " " + n.getSon(0).trace;
		if (n.getSon(0).count != 1)
			n.trace +=  to_string(n.getSon(0).count + 1) + " DECL";
		else
			n.trace += " DECL";

	}
	else Error("Excepted : variable name");
}

void SyntaxAnalizator::VarList(Node& n) {
	if (isName(lexeme))
	{
		// VarList→ Id VarList’
		n.addSon("Id");
		Id(n.getSon(0),true);
		n.addSon("VarList1");
		VarList1(n.getSon(1));
		n.count += n.getSon(1).count;
		n.trace += n.getSon(0).trace + " " + n.getSon(1).trace;
	}
	else Error("Expected : variable name");
}

void SyntaxAnalizator::VarList1(Node& n) {
	if (lexeme == ":")
	{
		// VarList’→ eps
		n.addSon("eps");
		n.count = 0;
	}
	else if (lexeme == ",") {
		// VarList’→ , VarList
		n.addSon(",");
		getLexeme();
		n.addSon("VarList");
		VarList(n.getSon(1));
		n.trace += n.getSon(1).trace;
		n.count = n.getSon(1).count;
	}
	else Error("Expected : ':' or ','");
}

void SyntaxAnalizator::Type(Node& n) {
	if (lexeme == "integer")
	{
		// Type → integer
		n.addSon("integer");
		getLexeme();
		n.trace += "integer";
	}
	else Error("Expected : 'integer'");
}

void SyntaxAnalizator::Operators(Node& n) {
	if (lexeme == "for" || isName(lexeme))
	{
		// Operators → Op Operators’
		n.addSon("Op");
		Op(n.getSon(0));
		n.addSon("Operators1");
		Operators1(n.getSon(1));
		n.trace += n.getSon(0).trace + " " + n.getSon(1).trace;
	}
	else Error("Expected : 'for' or variable name");
}

void SyntaxAnalizator::Operators1(Node& n) {
	if (lexeme == "for" || isName(lexeme))
	{
		// Operators’→Operators
		n.addSon("Operators");
		Operators(n.getSon(0));
		n.trace += n.getSon(0).trace;
	}
	else if (lexeme == "end") {
		// Operators’→eps
		n.addSon("eps");

	}
	else Error("Expected : 'case' or 'end' or variable name or value");
}



void SyntaxAnalizator::Op(Node& n) {
	if (lexeme == "for")
	{
		// Op → for Id := Const to Const do begin Operators end ;
		n.addSon("for");
		getLexeme();
		n.addSon("Id");
		Id(n.getSon(1));
		if (lexeme == ":=") {
			n.addSon(":=");
			getLexeme();
		}
		else {
			Error("Expected : ':='");
		}
		n.addSon("Const");
		Const(n.getSon(3));
		if (lexeme == "to") {
			n.addSon("to");
			getLexeme();
		}
		else {
			Error("Expected : 'to'");
		}
		n.addSon("Const");
		Const(n.getSon(5));
		if (lexeme == "do") {
			n.addSon("do");
			getLexeme();
		}
		else {
			Error("Expected : 'do'");
		}
		if (lexeme == "begin") {
			n.addSon("begin");
			getLexeme();
		}
		else {
			Error("Expected : 'begin'");
		}
		n.addSon("Operators");
		Operators(n.getSon(8));
		if (lexeme == "end") {
			n.addSon("end");
			getLexeme();
		}
		else {
			Error("Expected : 'end'");
		}
		if (lexeme == ";") {
			n.addSon(";");
			getLexeme();
		}
		else {
			Error("Expected : ';'");
		}
		n.trace +=  n.getSon(1).trace + " " + n.getSon(3).trace + "=";
		n.trace += " m" + to_string(currentTagIndex) + " DEFL ";
		n.trace += n.getSon(1).trace + " " + n.getSon(5).trace + " <";
		n.trace += " m" + to_string(currentTagIndex + 1) + " BF ";
		n.trace += n.getSon(8).trace;
		n.trace += n.getSon(1).trace+ " " + n.getSon(1).trace + " 1 + =";
		n.trace += "m" + to_string(currentTagIndex) + " BRL";
		n.trace += " m" + to_string(currentTagIndex + 1) + " DEFL";
		

		// DEFL - новая метка
		// BRL - к метке перейти
		// BF - переход к метке, если условие ложно
		currentTagIndex += 2;
	}
	else if (isName(lexeme)) {
		// Op → Id := Expr ;
		n.addSon("Id");
		Id(n.getSon(0));
		if (lexeme == ":=") {
			n.addSon(":=");
			getLexeme();
		}
		else {
			Error("Expected : ':='");
		}
		n.addSon("Expr");
		Expr(n.getSon(2));
		if (lexeme == ";") {
			n.addSon(";");
			getLexeme();
		}
		else {
			Error("Expected : ';'");
		}
		n.trace = n.getSon(0).trace + " " + n.getSon(2).trace + "=";
	}
	else Error("Expected : 'for' or 'end' or variable name or value");
}

void SyntaxAnalizator::Expr(Node& n) {
	if (lexeme == "(" || isName(lexeme) || isNum(lexeme))
	{
		// Expr → SimpleExpr Expr’
		n.addSon("SimpleExpr");
		SimpleExpr(n.getSon(0));
		n.addSon("Expr1");
		Expr1(n.getSon(1));
		n.trace = n.getSon(0).trace + " " + n.getSon(1).trace;
	}
	else Error("Expected : '(' or value or variable name");
}

void SyntaxAnalizator::Expr1(Node& n) {
	if (lexeme == ";" || lexeme == ")")
	{
		// Expr’->eps
		n.addSon("eps");
	}
	else if (lexeme == "+") {
		// Expr' -> +Expr
		n.addSon("+");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
		n.trace = n.getSon(1).trace + " +";
	}
	else if (lexeme == "-") {
		// Expr' -> -Expr
		n.addSon("-");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
		n.trace = n.getSon(1).trace + " -";
	}
	else Error("Expected : '+' or '-' or ';' or ')'");
}

void SyntaxAnalizator::SimpleExpr(Node& n) {
	if (lexeme == "(")
	{
		// SimpleExpr → ( Expr )
		n.addSon("(");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
		if (lexeme == ")") {
			n.addSon(")");
			getLexeme();
		}
		else {
			Error("Expected : ')'");
		}
		n.trace += n.getSon(1).trace + " ";

	}
	else if (isName(lexeme)) {
		// SimpleExpr → Id
		n.addSon("Id");
		Id(n.getSon(0));
		n.trace += n.getSon(0).trace;

	}
	else if (isNum(lexeme)) {
		// SimpleExpr → Const
		n.addSon("Const");
		Const(n.getSon(0));
		n.trace += n.getSon(0).trace;
	}
	else Error("Expected : '(' or variable name or value");
}

void SyntaxAnalizator::RelationOperators(Node& n)
{
	if (lexeme == "=")
	{
		n.addSon("=");
		n.getSon(0).trace = lexeme;
		n.trace = lexeme;
		getLexeme();
	}
	else if (lexeme == "<>") {
		n.addSon("<>");
		n.getSon(0).trace = lexeme;
		n.trace = lexeme;
		getLexeme();
	}
	else if (lexeme == ">") {
		n.addSon(">");
		n.getSon(0).trace = lexeme;
		n.trace = lexeme;
		getLexeme();
	}
	else if (lexeme == "<") {
		n.addSon("<");
		n.getSon(0).trace = lexeme;
		n.trace = lexeme;
		getLexeme();
	}
	else {
		Error("Expected : '=' or '<>' or '>' or '<'");
	}
}

void SyntaxAnalizator::Id(Node& n, bool isNewVar) {
	if (isName(lexeme))
	{
		// Id → id_name
		bool isVarExsisting = vars.find(lexeme) != vars.end();
		if (isNewVar == false) {
			if (isVarExsisting == false) {
				Error("Excepted declaration : " + lexeme);
			}
			n.addSon(lexeme);
			n.getSon(0).trace = lexeme;
			getLexeme();
		}
		else {
			if (!isVarExsisting) {
				vars.insert(lexeme);
				n.addSon(lexeme);
				n.getSon(0).trace = lexeme;
				getLexeme();
			}
			else {
				Error("Declared already : " + lexeme);
			}
		}
		n.trace = n.getSon(0).trace;
	}
	else Error("Expected : variable name");
}

void SyntaxAnalizator::Const(Node& n) {
	if (isNum(lexeme))
	{
		// Const → int_num
		n.addSon(lexeme);
		n.trace = lexeme;
		getLexeme();
	}
	else Error("Expected : value");
}

bool SyntaxAnalizator::isVars() {

	if (string(orderedLexems[currentId].lex) == "," || string(orderedLexems[currentId].lex) == ":") {
		return true;
	}
	else {
		return false;
	}
}


void SyntaxAnalizator::Error(string message) {
	cout << message << '\n';
	exit(0);
}


SyntaxAnalizator::SyntaxAnalizator(std::vector<Token> lexems)
{
	orderedLexems = lexems;
	currentId = 0;
}

Node SyntaxAnalizator::process()
{
	Node root("Procedure");
	getLexeme();
	Procedure(root);
	if (lexeme != "#")
		Error("super oshibka");
	return root;
}
