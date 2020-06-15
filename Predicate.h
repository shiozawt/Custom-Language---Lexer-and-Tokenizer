#ifndef PREDICATE
#define PREDICATE
#include <vector>
#include <set>
#include "Parameter.h"
class Predicate {
private:
	std::string value = "";
	vector<Parameter> parameterVector;
	set<string> stringSet;
	//Rule ruleData;
public:
	Predicate() {}
	Predicate(std::string inputVal /*, vector<Parameter> inputParameter*/) {
		value = inputVal;
		//parameterVector = inputParameter;
	}
	void toString() {
		
	}
	string getString() {
		return value;
	}
};
#endif