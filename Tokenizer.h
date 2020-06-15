#ifndef TOKENIZER
#define TOKENIZER
#include "Token.h"
#include <iostream>
#include <stdio.h>
#include <cctype>
#include <sstream>
using namespace std;
class Tokenizer
{
	private:
		int tempLineHolder = 0;
		string input = "";
		int line = 1;
		int charList = 0;
	public:
		Tokenizer() {
			input = "";
		}
		Tokenizer(string userInput) {
			input = userInput;
			//cout << "in tokenizer, userInput is " << input;
			//int inputSize = userInput.size();
			
			

			//std::cout << "current userInput size is " << userInput.size() << endl;
		}
		void cleanup() {
			createToken("", E_O_F);
		}
		int characterList() {
			return charList;
		}
		int inputValSize() {
			return input.size();
		}
		Token createToken(string Val, identifier kind) {
			//cout << "new token created" << endl;
			Token newToken(Val, line, kind);
			return newToken;
		}
		Token getNextToken() {
			

			if (tempLineHolder != 0) {
				line = line + tempLineHolder;
				tempLineHolder = 0;
			}

			int tempChar = charList;
			char currentChar = input.at(tempChar);
			//cout << "curretn Char is " << currentChar << "and charList is" << charList << endl;
			//cout << "getNextToken" << " current input.1 is " <<  input.at(1) << endl;
			istringstream nextChar(input.substr(charList, 2));
			nextChar.get();
			char lookAhead = nextChar.peek();
			if (lookAhead == EOF) {
				if (currentChar == '\n') {
					line++;
				}
				string TokenValue = "";
				charList++;
				return createToken(TokenValue, E_O_F);
			}

			//space
			if (isspace(currentChar)) {
				if (currentChar == '\n') {
					line++;
				}
				charList++;
				string value = "space";
				Token space(value);
				return space;
			}
			else if (currentChar == ':') {
				char nextCharacter = input.at(charList +1);
				if (nextCharacter == '-') {
					string TokenValue = ":-";
					charList = charList + 2;
					return createToken(TokenValue, COLON_DASH);
				}
				else {
					string TokenValue = ":";
					charList++;
					return createToken(TokenValue, COLON);
				}
			}
			else if (currentChar == ')') {
				string TokenValue = ")";
				charList++;
				return createToken(TokenValue, RIGHT_PAREN);
			}
			else if (currentChar == '(') {
				string TokenValue = "(";
				charList++;
				return createToken(TokenValue, LEFT_PAREN);
			}
			//COMMA
			else if (currentChar == ',') {
				string TokenValue = ",";
				charList++;
				return createToken(TokenValue, COMMA);
			}
			//PERIOD,
			else if (currentChar == '.') {
				string TokenValue = ".";
				charList++;
				return createToken(TokenValue, PERIOD);
			}
			//Q_MARK,
			else if (currentChar == '?') {
				string TokenValue = "?";
				charList++;
				return createToken(TokenValue, Q_MARK);
			}
			//MULTIPLY,
			else if (currentChar == '*') {
				string TokenValue = "*";
				charList++;
				return createToken(TokenValue, MULTIPLY);
			}
			//ADD,
			else if (currentChar == '+') {
				string TokenValue = "+";
				charList++;
				return createToken(TokenValue, ADD);
			}
			//test for letter
			else if (isalpha(currentChar)) {
				//create empty string
				string wordChar = "";
				// set string equal to current Character
				wordChar = currentChar;
				//increment Character Index
				charList++;
				//current Character is equal to input at our current index
				currentChar = input.at(charList);
				// loop while we have a digit or number
				while (isalpha(currentChar) || isdigit(currentChar)) {
					//add to string
					wordChar += currentChar;
					//increment index
					charList++;
					// get new current character from input
					currentChar = input.at(charList);
				}
				if (wordChar == "Schemes") {
					return createToken(wordChar, SCHEMES);
				}
				else if (wordChar == "Facts") {
					return createToken(wordChar, FACTS);
				}
				else if (wordChar == "Rules") {
					return createToken(wordChar, RULES);
				}
				else if (wordChar == "Queries") {
					return createToken(wordChar, QUERIES);
				}
				else {
					return createToken(wordChar, ID);
				}
			}
			else if (currentChar == '\'') {
				
				std::string stringString = "";
				stringString = currentChar;
				charList++;
				currentChar = input.at(charList);
				
				int testVar = 1;
				while (testVar != 0 ) {
					istringstream nextChar(input.substr(charList, 2));
					nextChar.get();
					char lookAhead = nextChar.peek();
					if (lookAhead == EOF) {
						stringString += currentChar;
						return createToken(stringString, UNDEFINED);
					}
					else if (currentChar == '\'') {
						
						stringString += currentChar;
						charList++;
						currentChar = input.at(charList);

						istringstream newNextChar(input.substr(charList, 2));
						newNextChar.get();
						char newLookAhead = newNextChar.peek();
						if (newLookAhead == EOF) {
							break;
						}
						else if (currentChar == '\'') {

							stringString += currentChar;
							charList++;
							currentChar = input.at(charList);
							}
						else {
							testVar = 0;
						}
					}
					else {
						if (currentChar == '\n') {
							tempLineHolder = tempLineHolder + 1;
						}
						stringString += currentChar;
						charList++;
						currentChar = input.at(charList);
					}
				}
				return createToken(stringString, STRING);
			}
			else if (currentChar == '#') {
				char nextVar = input.at(charList + 1);
				std::string commentString = "";
				commentString = currentChar;
				charList++;
				currentChar = input.at(charList);
				if (nextVar == '|') {
					while (currentChar != '#') {
						istringstream nextChar(input.substr(charList, 2));
						nextChar.get();
						char lookAhead = nextChar.peek();
						if (lookAhead == EOF) {
							return createToken(commentString, UNDEFINED);
						}
						else {
							
							commentString += currentChar;
							charList++;
							currentChar = input.at(charList);
						}
						if (currentChar == '\n') {
							tempLineHolder = tempLineHolder + 1;
						}
						commentString += currentChar;
						charList++;
						currentChar = input.at(charList);
					}
					commentString += currentChar;
					charList++;
					currentChar = input.at(charList);
					return createToken(commentString, COMMENT);
				}
				else {
					while (currentChar != '\n') {
						commentString += currentChar;
						charList++;
						currentChar = input.at(charList);
					}
					return createToken(commentString, COMMENT);
				}
			}

			else  {
			string TokenValue;
			TokenValue = currentChar;
				charList++;
				return createToken(TokenValue, UNDEFINED);
			}
		}
};

#endif