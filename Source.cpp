#include "LexAnalizator.h"
#include "SyntaxAnalizator.h"
#include "HashTable.h"
using namespace std;
int main() {
	vector<Token> lexemsFromFile;
	LexAnalizator lexan = LexAnalizator();
	lexan.ScanWrite("input.txt",lexemsFromFile);

	SyntaxAnalizator p(lexemsFromFile);
	Node root = p.process();
	//root.print(0);
	cout << root.trace;
}
