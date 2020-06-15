#ifndef TOKEN
#define TOKEN
#include <string>
#include <iostream>

enum identifier {
	COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	UNDEFINED,
	E_O_F
};

class Token{
private:
	std::string tokenVal = "DEFAULT";
	int line;
	identifier kind;
	
public:
	Token() {

	}
	identifier getType() {
		return kind;
	}
	Token(std::string value, int lineNum = 0, identifier type = UNDEFINED) {
		tokenVal = value;
		line = lineNum;
		kind = type;
	}
	string getTokenVal() {
		return tokenVal;
	}
	
	std::string toString() {
		std::string output = "";

		switch (kind) {
		case COMMA:
			output = "COMMA";
			break;
		case PERIOD:
			output = "PERIOD";
			break;
		case Q_MARK:
			output = "Q_MARK";
			break;
		case RIGHT_PAREN:
			output = "RIGHT_PAREN";
			break;
		case LEFT_PAREN:
			output = "LEFT_PAREN";
			break;
		case COLON:
			output = "COLON";
			break;
		case COLON_DASH:
			output = "COLON_DASH";
			break;
		case MULTIPLY:
			output = "MULTIPLY";
			break;
		case ADD:
			output = "ADD";
			break;
		case SCHEMES:
			output = "SCHEMES";
			break;
		case RULES:
			output = "RULES";
			break;
		case STRING:
			output = "STRING";
			break;
		case COMMENT:
			output = "COMMENT";
			break;
		case FACTS:
			output = "FACTS";
			break;
		case QUERIES:
			output = "QUERIES";
			break;
		case ID:
			output = "ID";
			break;
		case UNDEFINED:
			output = "UNDEFINED";
			break;
		case E_O_F:
			output = "EOF";
			break;
		}
		output = '(' + output + ',' + '"' + tokenVal + '"' + ',';
		output += std::to_string(line);
		output = output + ')';
		
		return output;
	}
	
	bool space() {
		if (tokenVal == "space") {
			return true;
		}
		else {
			return false;
		}
	}
};

#endif