#ifndef PARSER_MAIN
#define PARSER_MAIN
//#include "Token.h"
#include "Lexer.h"
#include "DatalogProgram.h"
using namespace std;
class ParserMain {
private:
	vector<Token> tokenList;
	DatalogProgram dataAccess;
	Predicate predicateAccess;
	string tempString = "";
	Rule ruleAccess;
	//Lexer lexerVal;
public:
	ParserMain() {}
	ParserMain(vector<Token> inputTokens) {
		tokenList = inputTokens;
	}
	/*
	void recieveTokensList(Token passedInToken, int identifier, int sizeHold) {
		//tokenList.size() = sizeHold;
		Token placeHolder = passedInToken;
		tokenList.push_back(placeHolder);
		parse(passedInToken);
		//cout << "recieveTokensList" << endl;
		//cout << tokenList[identifier].toString() << endl;
		//cout << "current size of token list is" << tokenList.size();
	}
	*/
	void parse() {
		try {
			//tokenListCopy = tokenList;
			DataLogParse();

			if (tokenList.front().getType() == E_O_F) {
				//cout << "Success!" << endl;
				
				dataAccess.toString();
			}
			else {
				throw tokenList.front();
			}
		}
		catch (Token error) {
			cout << "Failure!" << endl;
			cout << "  " << error.toString() << endl;
		}

	}
	//function to start the parsing

	void DataLogParse() {
		//cout << "datalogparse funcition" << endl;
		if (tokenList.front().getType() == SCHEMES) {
			getNextValue();
		}
		else {
			throw tokenList.front();
		}

		if (tokenList.front().getType() == COLON) {
			getNextValue();

			parseScheme();
			schemeListParser();

		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == FACTS) {
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == COLON) {
			getNextValue();
			parseFactList();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == RULES) {
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == COLON) {
			getNextValue();
			parseRuleList();
		}
		else {
			throw tokenList.front();
		}

		if (tokenList.front().getType() == QUERIES) {
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == COLON) {
			getNextValue();
			queryParse();
			queryListParse();
		}
		else {
			throw tokenList.front();
		}

		//SCHEMES COLON scheme schemeList FACTS COLON ->
		// -> factList RULES COLON ruleList QUERIES COLON query queryList}
	}
	void parserToString() {
		//int counter = 0;
		//cout << "Success!" << endl;
		//cout << "Scheme:" << endl; 
		//counter = counter + 2;
		//tokenListCopy.at(0).outputScheme();

	}

	void queryParse() {
		if (tokenList.front().getType() == ID) {
			predicateParse();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == Q_MARK) {
			tempString = tempString + tokenList.front().getTokenVal();
			dataAccess.addToQueries(tempString);
			tempString = "";
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
	}
	//query->predicate Q_MARK

	void queryListParse() {
		if (tokenList.front().getType() == ID) {
			//getNextValue();
			queryParse();
			queryListParse();
		}
		else {
			return;
		}
	}
	//queryList->query queryList | lambda

	void parseRuleList() {
		if (tokenList.front().getType() == ID) {
			parseRule();
			parseRuleList();
		}
		else {
			return;
		}
	}
	//rule ruleList | lambda

	void parseRule() {
		if (tokenList.front().getType() == ID) {
			
			headPredicateParse();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == COLON_DASH) {
			tempString = tempString + " " + tokenList.front().getTokenVal() + " ";
			getNextValue();
			predicateParse();
			predicateListParse();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == PERIOD) {
			tempString = tempString + tokenList.front().getTokenVal();
			dataAccess.addToRules(tempString);
			tempString = "";
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
	}
	//ruleList->headPredicate COLON_DASH predicate predicateList PERIOD
	void predicateListParse() {
		if (tokenList.front().getType() == COMMA) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
			predicateParse();
			predicateListParse();
		}
		else {
			return;
		}
	}
	//predicateList->COMMA predicate predicateList | lambda

	void parameterListParse() {
		if (tokenList.front().getType() == COMMA) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
			parameterParse();
			parameterListParse();
		}
		else {
			return;
		}
	}
	//parameterList	-> 	COMMA parameter parameterList | lambda

	void parameterParse() {
		if (tokenList.front().getType() == STRING) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else if (tokenList.front().getType() == ID) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
	}
	//parameter->STRING | ID

	void predicateParse() {
		if (tokenList.front().getType() == ID) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == LEFT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
			parameterParse();
			parameterListParse();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == RIGHT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
	}
	//predicate->ID LEFT_PAREN parameter parameterList RIGHT_PAREN

	void headPredicateParse() {
		if (tokenList.front().getType() == ID) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == LEFT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == ID) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
			idListParser();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == RIGHT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
	}
	//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN

	void getNextValue() {
		if (tokenList.size() != 0) {
			tokenList.erase(tokenList.begin());
		}
	}

	void parseScheme() {
		
		if (tokenList.front().getType() == ID) {
			tempString = tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == LEFT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == ID) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
			idListParser();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == RIGHT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			dataAccess.addToScheme(tempString);
			tempString = "";
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
	}
	//ID LEFT_PAREN ID idList RIGHT_PAREN

	void idListParser() {
		if (tokenList.front().getType() == COMMA) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			return;
		}
		if (tokenList.front().getType() == ID) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
			idListParser();
		}
		else {
			throw tokenList.front();
		}
	}
	//COMMA ID idList | lambda

	void schemeListParser() {
		if (tokenList.front().getType() == ID) {
			parseScheme();
			schemeListParser();
		}
		else {
			return;
		}
	}

	void parseFactList() {
		if (tokenList.front().getType() == ID) {
			parseFact();
			parseFactList();
		}
		else {
			return;
		}
	}
	// factList->fact factList | lambda

	void parseFact() {
		if (tokenList.front().getType() == ID) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == LEFT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == STRING) {
			tempString = tempString + tokenList.front().getTokenVal();
			bool ToF = false;
			dataAccess.createNewParameter(ToF, tokenList.front().getTokenVal());
			getNextValue();
			parseStringList();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == RIGHT_PAREN) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
		if (tokenList.front().getType() == PERIOD) {
			tempString = tempString + tokenList.front().getTokenVal();
			dataAccess.addToFacts(tempString);
			tempString = "";
			getNextValue();
		}
		else {
			throw tokenList.front();
		}
	}

	//fact->ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD

	void parseStringList() {
		//cout << "Parsing string list " << endl;
		if (tokenList.front().getType() == COMMA) {
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
		}
		else {
			return;
		}
		if (tokenList.front().getType() == STRING) {
			bool ToF = false;
			dataAccess.createNewParameter(ToF, tokenList.front().getTokenVal());
			tempString = tempString + tokenList.front().getTokenVal();
			getNextValue();
			parseStringList();
		}
		else {
			throw tokenList.front();
		}
	}
	//stringList -> COMMA STRING stringList | lambda
};
#endif
