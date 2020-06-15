#include <iostream>
using namespace std;
#include <string>
#include "Lexer.h"
#include "ParserMain.h"
#include "Interpreter.h"
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{

	stringstream inputStream;

	ifstream in(argv[1]);

	string input = "";

	while (in.peek() != EOF) {
		input += in.get();
	}

	Lexer myLexer(input);
	myLexer.getNextToken();
	myLexer.catchExtras();
	myLexer.removeCommentTokens();
	//myLexer.printAllTokens();
	//myLexer.printTotalTokens();
	//myLexer.copyTokensList();

	ParserMain obj(myLexer.getTokens());
	obj.parse();

	Interpreter ip;
	ip.Interpret();

	//cout << input << endl;

	in.close();

	return 0;
}