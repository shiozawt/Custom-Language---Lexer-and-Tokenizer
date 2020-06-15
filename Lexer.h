#ifndef LEXER
#define LEXER
#include "Tokenizer.h"
//#include "datalogProgram.h"
#include <iostream>
#include <string>
#include <vector>

class Lexer {
protected:
	vector<Token> output_list;
	Tokenizer myTokenizer;
	//DatalogProgram myDatalog;
public:
	
	Lexer(string input) {
		myTokenizer = Tokenizer(input);
		//getNextToken();
	}
	/*
	void copyTokensList() {
		for (int i = 0; i < output_list.size(); ++i) {
			int sizeFunc = output_list.size();
			Token passedOffToken = output_list.at(i);
			int identifier = i;
			myDatalog.recieveTokensList(passedOffToken, identifier, sizeFunc);
		}
	}
	*/
	vector<Token> getTokens() {
		return output_list;
	}
	void catchExtras() {
		if (output_list.size() == 0) {
			Token newToken("",1,E_O_F);
			output_list.push_back(newToken);
		}
	}

	void getNextToken() {
		while (myTokenizer.characterList() != myTokenizer.inputValSize()) {
			output_list.push_back(myTokenizer.getNextToken());
			//put in code to get rid of comments here
			if (output_list[output_list.size() - 1].space()) {
				output_list.pop_back();
			}
		}
	}

	void printAllTokens() {
		for (unsigned int i = 0; i < output_list.size(); i++) {
			cout << output_list[i].toString() << endl;
		}
	}

	void scanInput() {
	}

	void printTotalTokens() {
		cout << "Total Tokens = " << output_list.size() << endl;
	}

	friend class DatalogProgram;
	void removeCommentTokens() {
		for (unsigned int i = 0; i < output_list.size(); ++i){
			if (output_list.at(i).getType() == COMMENT) {
				output_list.erase(output_list.begin() + i);
				i = i - 1;
			}
			else {
			}
		}
	}
};



#endif