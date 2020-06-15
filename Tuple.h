#ifndef TUPLE
#define TUPLE
#include <vector>
#include <string>
using namespace std;
class Tuple
{
private:
	//A tuple is a list of attribute values
	std::vector<std::string> attributeValues;
public:
	Tuple() {}
	Tuple(std::vector<std::string> inputVals) {
		attributeValues = inputVals;
	}
	void toString() {
		for (unsigned int i = 0; i < attributeValues.size(); i++) {
			cout << attributeValues.at(i) << endl;
		}
	}
	void getVariableValues(vector<Tuple>newTset, vector<string>inputQuery) {
		
		//puts Tuples into stringVec
		/*
		for (unsigned int i = 0; i < newTset.size(); i++) {
			vector<string> stringVec = newTset.at(i).getStringVec();
		}
		*/

		vector<int> intVec;
		vector<string> tempVec;

		//puts all variables in tempVec. Ignores constants
		for (unsigned int i = 0; i < inputQuery.size(); i++) {
			string tempString = inputQuery.at(i);
			if (tempString.at(0) != '\'') {
				tempVec.push_back(inputQuery.at(i));
				//cout << inputQuery.at(i) << endl;
				intVec.push_back(i);
			}
			else {}
		}
		
		int savedVar = 0;
		//cout << "intvec size " << intVec.size() << " and tempVec.size() " << tempVec.size() << endl;
		for (unsigned int j = 0; j < newTset.size(); j++) {
			vector<string> stringVec = newTset.at(j).getStringVec(); // set stringVec equal to newTset
			
			vector<int> duplicateCount;

			while (duplicateCount.size() != 0) {
				duplicateCount.erase(duplicateCount.begin());
			}

			if (savedVar != 0) {
				stringVec.erase(stringVec.begin() + savedVar);
			}

			int vitaminc = 1; // spacing function int
		
			// begin erase duplicates function
			//cout << "stage 1" << endl;
			for (unsigned int t = 0; t < tempVec.size(); t++) {
				for (unsigned int q = 0; q < tempVec.size(); q++) {
					if (tempVec.at(t) == tempVec.at(q)) {
						//cout << "stage 2" << endl;
						if (t != q) {
							//cout << "stage 3" << endl;
							tempVec.erase(tempVec.begin() + q);
							stringVec.erase(stringVec.begin() + q);
							savedVar = q;
						}
					}
				}
			}
			// end erase duplicates function

			for (unsigned int i = 0; i < tempVec.size(); i++) {
				//cout << "stage 1" << endl;
				
				//cout << tempVec.size() << stringVec.size() << endl;


				//cout << "stage 2" << endl;
				//cout << constCounter << endl;
				
				if (tempVec.size() > 1) {
					if (vitaminc == 1) {
						cout << "  ";
						vitaminc = 0;
					}
					if (i == tempVec.size() - 1) {
						cout << tempVec.at(i) << "=" << stringVec.at(intVec.at(i)) << endl;
						//vitaminc = 1;
					}
					else {
						cout << tempVec.at(i) << "=" << stringVec.at(intVec.at(i)) << ", ";
					}
				}
				else { cout << "  " << tempVec.at(i) << "=" << stringVec.at(intVec.at(i)) << endl; }
			}
		}
	}

	vector<string> getStringVec() {
		return attributeValues;
	}
	int testVals(vector<string> currentInputQuery) {
		int counter = 0;
		int returnVal = 1;
		//cout << currentInputQuery.size() << "query size " << attributeValues.size() << "atb size () " << endl;
		for (unsigned int i = 0; i < attributeValues.size(); i++) {
			//cout << attributeValues.at(i) << "--" << currentInputQuery.at(i) << endl;
		}
		for (unsigned int i = 0; i < attributeValues.size(); i++) {
			string currentStr = currentInputQuery.at(i);
			if (currentStr.at(0) == '\'') {
				if (currentStr == attributeValues.at(i)) {
					//cout << "do nothing" << endl;
				}
				else {
					returnVal = 0;
					counter += 1;
				}
			}
			else {
				//cout << "did nothing" << endl;
			}
		}

		if (currentInputQuery.size() > 1) {
			
			
			if (currentInputQuery.at(0) == currentInputQuery.at(1)) {
				string curStr = currentInputQuery.at(0);
				
				if (curStr.at(0) != '\'') {
					
					if (attributeValues.at(0) != attributeValues.at(1)) {
						
						returnVal = 0;
						//counter += 1;
					}
				}
			}
		}
		vector<int> intVect;
		vector<int> intVectMatch;
		//go throught CIQ
		for (unsigned int i = 0; i < currentInputQuery.size(); i++) {
			string curStr = currentInputQuery.at(0);

			if (curStr.at(0) != '\'') {
				for (unsigned int j = 0; j < currentInputQuery.size(); j++) {
					if (currentInputQuery.at(i) == currentInputQuery.at(j)) {
						//create a pair
						intVect.push_back(i);
						intVectMatch.push_back(j);
					}
				}
			}
		}
		//if a value is identified that is a variable, check against all other queries
		//if two variables match, create a data structure to hold these two int locations
		// test AtB at these locations against each other. if not equal, set return value to 0
		for(unsigned int j = 0; j < intVect.size(); j++) {
			if (attributeValues.at(intVect.at(j)) == attributeValues.at(intVectMatch.at(j))) {
			}
			else {
			returnVal = 0;
			}
		}

		if (returnVal == 1) {
			//cout << "Yes(" << attributeValues.size() - counter << ')' << endl;
		}
		else {
			//cout << "false" << endl;
		}
		return returnVal;
	}
	void getTupleString() {
		for (unsigned int i = 0; i < attributeValues.size(); i++) {
			cout << attributeValues.at(i) << endl;
		}
	}
	string getHelp() {
		string returnVal;
		if (attributeValues.size() != 0){
			for (unsigned int i = 0; i < attributeValues.size(); ++i) {
				returnVal = returnVal + attributeValues.at(i);
			}
		}
		return returnVal;
	}
};
#endif


