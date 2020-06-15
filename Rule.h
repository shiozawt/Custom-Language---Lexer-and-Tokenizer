#ifndef RULE
#define RULE
#include <iostream>
#include <vector>
#include "Predicate.h"
class Rule
{
private:
	Predicate headPredicate;
	vector<Predicate> predicateVector;
	std::string ruleString = "";
public:
	Rule() {}
	Rule(std::string inputString /*Predicate HP, vector<Predicate> inputVector*/) {
		//headPredicate = HP;
		//predicateVector = inputVector;
		ruleString = inputString;
	}
	string getString() {
		return ruleString;
	}
	void toString(vector<Rule> ruleVector) {
		//cout << "Rules(" << ruleVector.size() << "):" << endl;
		//ruleVector.front();
		int rulesHolder = ruleVector.size();
		for (int i = 0; i < rulesHolder; ++i) {
			//cout << "  " << ruleVector.front().getString() << endl;
			ruleVector.erase(ruleVector.begin());
		}
	}
};
#endif
