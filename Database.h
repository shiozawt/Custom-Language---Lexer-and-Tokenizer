#ifndef DATABASE
#define DATABASE
//#include "DatalogProgram.h"
#include "Relation.h"
#include <map>
#include <string>
using namespace std;
class Database
{
private:
	//map<string name, Relation relaton>;
	//std::vector<Relation> relationList;
	map<string, Relation> databaseMap;
	vector<string> schemeList;
	Relation rel;
	vector<Relation> sortingVector;
	vector<string> savedVals;
	bool tof = true;
	bool tester = true;
public:
	Database() {}
	
	Database(map<string, Relation> inputDatabaseMap) {
		databaseMap = inputDatabaseMap;
	}
	//For each scheme in the Datalog program, add an empty Relation to the Database
	//Use the scheme name as the name of the relation and the attribute list from the scheme as the scheme of the relation.
	void EVALUATE_SCHEME() {

	}
	void ruleEval(vector<string>ruleVec) {
		int runs = 0;
		while (tof == true) {
			runs = runs + 1;
			tester = true;
			evaluate(ruleVec);
		}
		cout << endl;
		cout << "Schemes populated after " << runs << " passes through the Rules." << endl;
	}
	void evaluate(vector<string>ruleVec) {
		vector<string> headerVec;
		string name;
		//tof = false;
	//create a relation for each given value in the ruleVec
		//take name and headers from ruleVec, and get tuples from databaseMap for given name
		//for each given rule, pass name, databaseMap at given name, and header string vector on 
		vector<string> newRuleVec;
		int passCount = 0;
		for (unsigned int i = 0; i < ruleVec.size(); ++i) {
			
			string str = ruleVec.at(i);
			vector<Relation> relationVec;
			cout << str << endl;
			bool checkPoint = true;
			bool checkPointTwo = false;
			bool checkPointThree = false;
			string RHStr;
			string LHStr;
			string HeaderStr;
			vector<string> HeaderVec;
			//get name
			for (unsigned int j = 0; j < str.size(); ++j) {
				if (str.at(j) == '-') {					
					checkPointTwo = true;
				}
				if (str.at(j) == ')') {
					if (checkPointTwo == true) {
						checkPointThree = false;
						if (HeaderStr.size() != 0) {
							HeaderVec.push_back(HeaderStr);
							//cout << "headerstr is " << HeaderStr << endl;
							HeaderStr = "";
							//cout << HeaderVec.size() << endl;
							Relation newRelation = rel.CREATE_RELATION(RHStr, databaseMap.at(RHStr), HeaderVec);
							//cout << "RHSTR is " << RHStr << endl;
							relationVec.push_back(newRelation);
							RHStr = "";
							//erase headerVec
							unsigned int m = HeaderVec.size();
							for (unsigned int t = 0; t < m; ++t) {
								HeaderVec.erase(HeaderVec.begin());
							}
							//cout << "HeaderVec size is now " << HeaderVec.size() << endl;
						}
					}
				}
				//
				if (str.at(j) == ',') {
					if (checkPointTwo == true) {
						if (checkPointThree == true) {
							HeaderVec.push_back(HeaderStr);
							//cout << "headerstr is " << HeaderStr << endl;
							HeaderStr = "";
						}
					}
				}
				
				if (checkPointTwo == true) {
					if (checkPointThree == true) {
						if (str.at(j) != ',') {
							HeaderStr = HeaderStr + str.at(j);
						}
					}
				}
				
				if (str.at(j) == '(') {
					if (checkPointTwo == true) {
						checkPointThree = true;
					}
				}
				if (str.at(j) == '(') {
					checkPoint = false; 
					if (RHStr.size() != 0) {
						//cout << "RHstr is " << RHStr << endl;
					}
					//RHStr = "";
				}
				if (str.at(j) == '(') {
					checkPoint = false;
					if (checkPointTwo == false) {
						if (LHStr.size() != 0) {
							//cout << "LHstr is " << LHStr << endl;
						}
						//LHStr = "";
					}
				}
				if (isalpha(str.at(j))) {
					if (checkPointTwo == true) {
						if (checkPoint == true) {
							RHStr = RHStr + str.at(j);
						}
					}
				}		 
				if (isalpha(str.at(j))) {
					if (checkPointTwo == false) {
						if (checkPoint == true) {
							LHStr = LHStr + str.at(j);
						}
					}
				}
				if (str.at(j) == ')') {
					checkPoint = true;
				}
			}
			//get headers
			bool testZ = true;
			if (relationVec.size() == 1) {
				testZ = false;
			}

			while (relationVec.size() > 1) {
				Relation newRelation = relationVec.at(0).join(relationVec.at(1), ruleVec.at(i));
				relationVec.erase(relationVec.begin());
				relationVec.erase(relationVec.begin());
				relationVec.push_back(newRelation);
				//cout << "relationVec.size()" << relationVec.size() << endl;
			}
			/*
			cout << "new test program (located in database RuleEval) " << endl;

			cout << "current input tuples" << endl;
			for (unsigned int i = 0; i < relationVec.at(0).getTupleVectorSize(); ++i) {
				vector<string> yVec = relationVec.at(0).getTupleVal(i);
				for (unsigned int j = 0; j < yVec.size(); ++j) {
					cout << yVec.at(j);
				}
				cout << endl;
			}
			cout << "current database tuples" << endl;
			for (unsigned int i = 0; i < databaseMap.at(LHStr).getTupleVectorSize(); ++i) {
				vector<string> yVec = databaseMap.at(LHStr).getTupleVal(i);
				for (unsigned int j = 0; j < yVec.size(); ++j) {
					cout << yVec.at(j);
				}
				cout << endl;
			}
			*/
			//edit out headers that are not necessary
			// -> pass in relationVec.at(0) and rule LH
			if (testZ == true) {
				relationVec.at(0).deleteBadHeaders(str);
				//cout << "BAD HEADERS" << endl;
			}
			
			if (testZ == false) {
				relationVec.at(0).alignment(databaseMap.at(LHStr), ruleVec.at(i));
				//cout << "ALIGNMENT" << endl;
			}
			/*
			cout << "updated input tuples" << endl;
			for (unsigned int i = 0; i < relationVec.at(0).getTupleVectorSize(); ++i) {
				vector<string> yVec = relationVec.at(0).getTupleVal(i);
				for (unsigned int j = 0; j < yVec.size(); ++j) {
					cout << yVec.at(j);
				}
				cout << endl;
			}
			*/

			//TEST CASE OUTPUTS
			//relationVec.at(0).outputHeaders();
			//relationVec.at(0).outputTuple();
			//--

			//relationVec.at(0).alignment(databaseMap.at(LHStr));

			/*
			cout << "new test program (located in database RuleEval) " << endl;

			for (unsigned int i = 0; i < relationVec.at(0).getTupleVectorSize(); ++i) {
				vector<string> yVec = relationVec.at(0).getTupleVal(i);
				for (unsigned int j = 0; j < yVec.size(); ++j) {
					cout << yVec.at(j);
				}
				cout << endl;
			}
			//cout << LHStr << endl;
			//relationVec.at(0).verifySize();
			*/
			int fst = databaseMap.at(LHStr).getTupleVectorSize();
			//databaseMap.at(LHStr).getTuples();
			databaseMap.at(LHStr).combine(relationVec.at(0), ruleVec.at(i));
			/*
			cout << "updated database tuples" << endl;
			for (unsigned int i = 0; i < databaseMap.at(LHStr).getTupleVectorSize(); ++i) {
				vector<string> yVec = databaseMap.at(LHStr).getTupleVal(i);
				for (unsigned int j = 0; j < yVec.size(); ++j) {
					cout << yVec.at(j);
				}
				cout << endl;
			}
			*/
			/*move this back up if things break*/
			databaseMap.at(LHStr).sortThoseTuples();
			Relation NCP = databaseMap.at(LHStr);
			//rel.getResults(NCP, relationVec.at(0));
			/*move this back up if things break*/
			
			int scd = databaseMap.at(LHStr).getTupleVectorSize();
			//cout << scd << "::" << fst << endl;
			if (scd != fst) {
				newRuleVec.push_back(ruleVec.at(i));
				savedVals.push_back(ruleVec.at(i));
				tester = false;
				//cout << scd << "::" << fst << endl;
			}
			
			passCount = passCount + 1;
		}
		if (tester == false) {
		}
		else {
			tof = false;
		}
		/*
		for (unsigned int i = 0; i < newRuleVec.size(); ++i) {
			cout << newRuleVec.at(i) << endl;
		}
		*/
		//rel.coutRuleStorage();
		
		//cout << endl;
		//ruleParse();
	//join function called (to join headers and tuples on right side of relation)
		//databaseMap.at().join(relation);
	//
	}

	void getQueries(string str) { 
		string newStr;
		int counter = 0;
		for (unsigned int i = 0; i < str.size(); ++i) {
			if (str.at(i) == '(') {
				break;
			}
			else {
				newStr = newStr + str.at(i);
				counter += 1;
			}
		}
		counter += 1;
		//rel.select(str, databaseMap.at(newStr));
		//cout << str.at(counter) << endl;
		//now get the tokens from query and test if they are constants or variables
		string firstVal;
		vector<string> stringVec;
		int newCount = counter;
		for (unsigned int i = newCount; i < str.size(); ++i) {
			if (str.at(i) == ')') {\
				stringVec.push_back(firstVal);
				firstVal = "";
				break;
			}
			else if (str.at(i) == ',') {
				stringVec.push_back(firstVal);
				firstVal = "";
			}
			else {
				firstVal = firstVal + str.at(i);
				//counter += 1;
			}
		}
		//cout << "size of stringVec is  " << stringVec.size() << endl;
		rel.select(stringVec, databaseMap.at(newStr));
	}
	void getString() {
		
		//databaseMap.at("SK").toString();
	}
	void getSchemeList(vector<string> input) {
		//cout << "this actually ran " << '\n' << '\n' << endl;
		schemeList = input;
		//cout << schemeList.size() << "sizeX AE A-12" << endl;
	}
	void addFactToMap(Tuple AttributeList, string nameString) {
		databaseMap.at(nameString).inputTuple(AttributeList);
		removeDuplicateFacts(nameString);
	}
	void testIfFactIsStored() {
		//databaseMap.at("SK").outputTuple();
		//databaseMap.at("test").outputTuple();
	}
	void AddToMap(string name, Relation relation) {
		databaseMap.insert(pair<string, Relation>(name, relation));
		//relation.toString();
		//cout << "Relation has been inserted into dataBase map. name is " << name << endl;
		//cout << "Total map size is now " << databaseMap.size() << endl;
		//cout << "databaseMap.at" << name << " is first " << databaseMap.at(name).getRelationshipName() << endl;
		/*
		if (name == "SK") {
			cout << "databaseMap.at" << name << " is first " << databaseMap.at(name).getRelationshipName() << endl;
			string testString = "THIS ACTUALLY WORKS!!";
			databaseMap.at(name).inputFacts(testString);
			cout << "databaseMap.at" << name << " is now " << databaseMap.at(name).getRelationshipName() << endl;
		}
		*/
		//mymap.insert ( std::pair<char,int>('a',100) );
	}
	void removeDuplicateFacts(string nameString) {
		map<string, Relation>::iterator it = databaseMap.begin();
		while (it != databaseMap.end())
		{
			// Accessing KEY from element pointed by it.
			string word = it->first;

			// Accessing VALUE from element pointed by it.
			Relation count = it->second;
			sortingVector.push_back(count);
			//cout << "current RelationVector size is " << sortingVector.size() << endl;
			//cout << word << " :: " << count << std::endl;

			// Increment the Iterator to point to next entry
			it++;
		}
		int tupleVectorSize = 0;
		tupleVectorSize = databaseMap.at(nameString).getTupleVectorSize();
		//cout << "tupleVectorSize" << " " << tupleVectorSize << endl;
		// get the vectors turned into strings and put into a vector of strings. Then, delete values from databaseMap
		//turn Tuples into strings
		vector<string> stringVec;
		string Hold;
		for (int i = 0; i < tupleVectorSize; ++i) {
			stringVec.push_back(databaseMap.at(nameString).getStringsForVectorFromTuples(i));
		}
		int removalcounter = 0;
		vector<int> removalVec;
		for (unsigned int i = 0; i < stringVec.size(); ++i) {
			int counter = 0;
			for (unsigned int j = 0; j < stringVec.size(); ++j) {
				if (stringVec.at(i) == stringVec.at(j)) {
					counter += 1;
					if (counter > 1) {
						stringVec.erase(stringVec.begin() + j);
						removalVec.push_back(j + removalcounter);
						removalcounter += 1;
					}
				}
			}
		}
		//cout << stringVec.size() << endl;
		//cout << removalVec.size() << endl;
		// remove values at points given on removalVec from the tuple vector
		databaseMap.at(nameString).removeRepeatedValues(removalVec);
	}
	//friend class DatalogProgram;
};
#endif

