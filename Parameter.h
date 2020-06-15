#ifndef PARAMETER
#define PARAMETER
#include <algorithm>
class Parameter {
private:
	bool stringTest = false;
	string parameterVal = "";
	vector<Parameter> domainVector;
	string sortHelp = "";
	vector<string> newVector;

public:
	Parameter() {}
	Parameter(bool kind, string Val) {
		stringTest = kind;
		parameterVal = Val;
	}
	void toString(vector<Parameter> inputVector) {
		sortOutMyVector(inputVector);
		//cout << "Domain(" << newVector.size() << "):" << endl;
		int domainHolder = newVector.size();
		for (int i = 0; i < domainHolder; ++i) {
			//cout << "  " << newVector.front() << endl;
			newVector.erase(newVector.begin());
		}
	}
	string getParameterVal() {
		return parameterVal;
	}
	void sortOutMyVector(vector<Parameter> inputVector) {
		for (unsigned int i = 0; i < inputVector.size(); ++i) {
			int counter = 0;
			for (unsigned int j = 0; j < inputVector.size(); ++j) {
				if (inputVector.at(i).getParameterVal() == inputVector.at(j).getParameterVal()) {
					counter += 1;
					if (counter > 1) {
						inputVector.erase(inputVector.begin()+j);
					}
				}
				//inputVector.erase(inputVector.begin());
			}
		}
		//
		domainVector = inputVector;
		sortFunction();
	}
	void sortFunction() {
		
		for (unsigned int i = 0; i < domainVector.size(); ++i) {
			newVector.push_back(domainVector.at(i).getParameterVal());
		}
		
		std::sort(newVector.begin(), newVector.end());
		
		/*
		for (int i = 0; i < newVector.size(); ++i) {
			for (int j = 0; j < newVector.size(); ++j) {
				if (newVector.at(i).getParameterVal() > transferVector.at(j).getParameterVal()) {
					
				}
			}
		}
		domainVector = transferVector;
		*/
	}
	string getDomainString() {
		return parameterVal;
	}
};
#endif
