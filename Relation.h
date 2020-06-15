#ifndef RELATION
#define RELATION

#include <iostream>
#include <string>
#include <vector>
#include "Scheme.h"
#include "Tuple.h"
#include <set>

class Relation
{
private:
	//A relation has a name, a scheme, and a set of tuples
	//contains a set of Tuples associated with a name and Scheme 
	std::string relationName = "";
	Scheme relationScheme;
	std::vector<Tuple> tupleSet;
	Tuple tup;
	vector<string> currentInputQuery;
	vector<Tuple> madrid;
public:
	Relation() {}
	Relation(std::string inputRelationName, Scheme inputRelationScheme, std::vector<Tuple> inputTupleSet) {
		relationName = inputRelationName;
		relationScheme = inputRelationScheme;
		tupleSet = inputTupleSet;
	}
	vector<string> ruleStorage;
	void deleteBadHeaders(string str) {
	// this is the whole rule
		//cout << str << endl;
		bool checkPoint = false;
		bool checkPointTwo = true;
		vector<string> newHeader;
		string newStr;
		for (unsigned int j = 0; j < str.size(); ++j) {
			if (str.at(j) == ')') {
				if (checkPointTwo == true){
					newHeader.push_back(newStr);
				}
				checkPoint = false;
				checkPointTwo = false;
			}
			if (str.at(j) == ',') {
				if (checkPointTwo == true) {
					newHeader.push_back(newStr);
					newStr = "";
				}
			}
			if (str.at(j) != ',') {
				if (checkPoint == true) {
					newStr = newStr + str.at(j);
				}
			}
			if (str.at(j) == '(') {
				checkPoint = true;
			}
		}

		//the function below cout's the new Header (list of rules contained in LH)
		for (unsigned int j = 0; j < newHeader.size(); ++j) {
			//cout << newHeader.at(j) << endl;
		}

		//NEXT STEP IS TO ADD ALL THE TUPLES THAT GO ALONG WITH THESE HEADERS TO A NEW TUPLE SET AND EDIT THE RELATION ACCORDINGLY
		//-> TEST, AND LOOK INTO SORTING MECHANISMS
		vector<vector<string>> tupleVec;
		for (unsigned int j = 0; j < tupleSet.size(); ++j) {
			Tuple tup = tupleSet.at(j);
			vector<string> stringVec = tup.getStringVec();
			tupleVec.push_back(stringVec);
		}
		//get values at which we need to get values
		vector<string> schemeVec = relationScheme.getStringVec();
		vector<int> intVec;
		for (unsigned int i = 0; i < newHeader.size(); ++i) {
			for (unsigned int j = 0; j < schemeVec.size(); ++j) {
				if (schemeVec.at(j) == newHeader.at(i)) {
					//cout << schemeVec.at(j) << "==" << newHeader.at(i) << endl;
					intVec.push_back(j);
				}
			}
		}
		relationScheme = newHeader;
		
		vector<vector<string>> stringVecVec;

		for (unsigned int i = 0; i < tupleVec.size(); ++i) {
			vector<string> stringVec = tupleVec.at(i);
			vector<string> newStringVec;
			for (unsigned int j = 0; j < intVec.size(); ++j) {
				newStringVec.push_back(stringVec.at(intVec.at(j)));
				//cout << stringVec.at(intVec.at(j)) << " ";
				//cout << intVec.at(j) << endl;
			}
		
			//cout << endl;
			stringVecVec.push_back(newStringVec);
		}
		
		//Sort Tuples Alphabetically
		
		std::sort(stringVecVec.begin(), stringVecVec.end());
		for (unsigned int i = 0; i < stringVecVec.size(); ++i) {
			vector<string> newStringVec = stringVecVec.at(i);
			for (unsigned int j = 0; j < newStringVec.size(); ++j) {
				//cout << "!";
				//cout << newStringVec.at(j) << " ";
			}
			//cout << endl;
		}
		
		//set TupleSet to stringVecVec for this relation
		vector<Tuple> newTvec;
		for (unsigned int i = 0; i < stringVecVec.size(); ++i) {
			Tuple newTuple = stringVecVec.at(i);
			newTvec.push_back(newTuple);
		}
		tupleSet = newTvec;
		//cout << newTvec.size() << "  " << tupleSet.size() << endl;
	}
	void combine(Relation input, string testCase) {
		/*
		cout << "combine beginning input tuples" << endl;
		for (unsigned int i = 0; i < input.getTupleVectorSize(); ++i) {
			vector<string> yVec = input.tupleSet.at(0).getStringVec();
			for (unsigned int j = 0; j < yVec.size(); ++j) {
				cout << yVec.at(j);
			}
			cout << endl;
		}
		*/
	//populate doubleVec with tuples from input
	vector<vector<string>> doubleVec;
	for (unsigned int i = 0; i < input.tupleSet.size(); ++i) {
		Tuple newTuple = input.tupleSet.at(i);
		vector<string> converter = newTuple.getStringVec();
		doubleVec.push_back(converter);
	}

	//--- NEW CODE TO FIX ERROR 54 ----
	doubleVec.erase(unique(doubleVec.begin(), doubleVec.end()), doubleVec.end());
	
	//convert input.tupleSet to doubleVec
	
	vector<Tuple> rpk;
	for (unsigned int i = 0; i < doubleVec.size(); ++i) {
		Tuple tko = doubleVec.at(i);
		vector<string> mpg = doubleVec.at(i);
		for (unsigned int j = 0; j < mpg.size(); ++j) {
			//cout << mpg.at(j);
		}
		//cout << endl;
		rpk.push_back(tko);
	}
	//cout << input.tupleSet.size() << "::";
	input.tupleSet = rpk;
	//cout << input.tupleSet.size() << endl;
	
	//
	for (unsigned int i = 0; i < doubleVec.size(); ++i) {
		vector<string> cbd = doubleVec.at(i);
		for (unsigned int j = 0; j < cbd.size(); ++j) {
			//cout << cbd.at(j);
		}
		//cout << endl;
	}

	//---- END OF NEW CODE ---

	//original vec populate from main
	vector<vector<string>> originalVec;
	for (unsigned int i = 0; i < tupleSet.size(); ++i) {
		Tuple newTuple = tupleSet.at(i);
		vector<string> converter = newTuple.getStringVec();
		originalVec.push_back(converter);
	}
	vector<int> itemsToDeleteFromInput;
	//test input list values against each other and delete repeats
	for (unsigned int i = 0; i < originalVec.size(); ++i) {
		for (unsigned int j = 0; j < doubleVec.size(); ++j) {
			if (originalVec.at(i) == doubleVec.at(j)) {
				itemsToDeleteFromInput.push_back(j);
			}
		}
	}
	//cout << itemsToDeleteFromInput.size() << endl;

	//!!!create a function here to erase double funcitons from input.tupleSet!!!
	

	//std::sort(itemsToDeleteFromInput.begin(), itemsToDeleteFromInput.end());
	int placeHolder = itemsToDeleteFromInput.size();
	sort(itemsToDeleteFromInput.begin(), itemsToDeleteFromInput.end(), greater<int>());
	/*
	//cout << "Outputing itemsToDelete" << endl;
	for (unsigned int i = 0; i < itemsToDeleteFromInput.size(); ++i) {
		//cout << itemsToDeleteFromInput.at(i) << endl;
	}
	*/
	
	if (itemsToDeleteFromInput.size() > 0) {
		for (int i = 0; i < placeHolder; ++i) {
			//cout << i << endl;
			input.tupleSet.erase(input.tupleSet.begin() + itemsToDeleteFromInput.at(i));
		}
	}
	/*
	cout << "test erase function" << endl;
	for (unsigned int i = 0; i < input.tupleSet.size(); ++i) {
		vector<string> rec = input.tupleSet.at(i).getStringVec();
		for (unsigned int j = 0; j < rec.size(); ++j) {
			cout << rec.at(j);
		}
		cout << endl;
	}
	*/
	//cout << tupleSet.size() << endl;
	//add new tuples to relation given that they are not already in the relation
	
	if (input.tupleSet.size() != 0) {
		ruleStorage.push_back(testCase);
	}
	//cout << input.tupleSet.size() << ":: " << ruleStorage.size() << endl;
	for (unsigned int i = 0; i < input.tupleSet.size(); ++i) {
		tupleSet.push_back(input.tupleSet.at(i));
	}

	//erase madrid
	//push back madrid
	//cout << tupleSet.size() << endl;
	

	vector<string> RSone = relationScheme.getStringVec();
	vector<vector<string>> newDoubleVec;
	for (unsigned int i = 0; i < input.tupleSet.size(); ++i) {
		Tuple newTuple = input.tupleSet.at(i);
		vector<string> converter = newTuple.getStringVec();
		newDoubleVec.push_back(converter);
	}
	//cout << "ENTERING TESTING PHASE" << endl;

	for (unsigned int i = 0; i < newDoubleVec.size(); ++i) {
		vector<string> stringVec = newDoubleVec.at(i);
		//cout << stringVec.size() << endl;
		for (unsigned int t = 0; t < stringVec.size(); ++t) {
			//cout << " % " << stringVec.at(t);
		}
		for (unsigned int j = 0; j < RSone.size(); ++j) {
			if (j == 0) { cout << "  "; }
			if (RSone.size() != 1) {
				if (j != RSone.size() - 1) {
					cout << RSone.at(j) << "=" << stringVec.at(j) << ", ";
				}
				else {
					cout << RSone.at(j) << "=" << stringVec.at(j);
				}
			}
			else {
				cout << RSone.at(j) << "=" << stringVec.at(j);
			}
		}
		cout << endl;
	}
	}

	void getResults(Relation main, Relation hasTuples) {
		vector<string> RSone = main.relationScheme.getStringVec();
		vector<vector<string>> doubleVec;
		for (unsigned int i = 0; i < hasTuples.tupleSet.size(); ++i) {
			Tuple newTuple = hasTuples.tupleSet.at(i);
			vector<string> converter = newTuple.getStringVec();
			doubleVec.push_back(converter);
		}		
		//cout << "ENTERING TESTING PHASE" << endl;
		
		for (unsigned int i = 0; i < doubleVec.size(); ++i) {
			vector<string> stringVec = doubleVec.at(i);
			//cout << stringVec.size() << endl;
			for (unsigned int t = 0; t < stringVec.size(); ++t) {
				//cout << " % " << stringVec.at(t);
			}
			for (unsigned int j = 0; j < RSone.size(); ++j) {
				if (j == 0) { cout << "  "; }
				if (RSone.size() != 1) {
					if (j != RSone.size() - 1) {
						cout << RSone.at(j) << "=" << stringVec.at(j) << ", ";
					}
					else {
						cout << RSone.at(j) << "=" << stringVec.at(j);
					}
				}
				else {
					cout << RSone.at(j) << "=" << stringVec.at(j);
				}
			}
			cout << endl;
		}		
	}

	void select(vector<string> inputQuery, Relation relation) {
		//cout << "vector size is " << inputQuery.size() << endl;
		currentInputQuery = inputQuery;
		//cout << "ASDFJLK vector size is " << currentInputQuery.size() << endl;
		Relation newRelation = relation;
		relation.getTuples(inputQuery);
	}
	Relation CREATE_RELATION(string name, Relation relation, vector<string> headerVec) {
		//cout << "in relation" << endl;
		for (unsigned int i = 0; i < headerVec.size(); ++i) {
			//cout << headerVec.at(i) << endl;
		}
		string str = relation.getRelationshipName();
		//cout << name << endl;
		Relation returnRelation;
		returnRelation.tupleSet = relation.tupleSet;
		if (relation.tupleSet.size() != 0) {
			Tuple newT = relation.tupleSet.at(0);
			vector<string> strVr = newT.getStringVec();
			for (unsigned int i = 0; i < strVr.size(); ++i) {
				//cout << strVr.at(i) << endl;
			}
		}
		returnRelation.relationName = name; 
		returnRelation.relationScheme = headerVec;
		return returnRelation;
	}

	Relation join(Relation relation, string rule_input) {
		//combine two relations based upon shared headers and shared values. If no headers are shared, simply add columns together
		//parse headers in for loops to find matches
		vector<string> RELATION_ONE_HEADER = relationScheme.getStringVec();
		vector<string> RELATION_TWO_HEADER = relation.relationScheme.getStringVec();
		vector<vector<string>> RELATION_ONE_TUPLES;
		vector<vector<string>> RELATION_TWO_TUPLES;

		//output headers function
		for (unsigned int i = 0; i < RELATION_ONE_HEADER.size(); ++i) {
			//cout << RELATION_ONE_HEADER.at(i) << endl;
		}
		for (unsigned int i = 0; i < RELATION_TWO_HEADER.size(); ++i) {
			//cout << RELATION_TWO_HEADER.at(i) << endl;
		}
		// end of headers output (for testing purposes)

		Relation returnVal;

		//test function to see if headers have any values in common
		bool commonVar = false;
		bool dumbTest = false;
		for (unsigned int i = 0; i < RELATION_TWO_HEADER.size(); ++i) {
			for (unsigned int j = 0; j < RELATION_ONE_HEADER.size(); ++j) {
				if (RELATION_TWO_HEADER.at(i) == RELATION_ONE_HEADER.at(j)) { dumbTest = true; }
			}
		}

		if (dumbTest == true) {
			commonVar = true;
		}
		else {}

		if (commonVar == true) {
			//cout << "in commonVartrue" << endl;
			if (RELATION_ONE_HEADER == RELATION_TWO_HEADER) {

				returnVal.relationScheme = RELATION_ONE_HEADER;
				vector<vector<string>> giantSet;
				for (unsigned int i = 0; i < tupleSet.size(); ++i) {
					RELATION_ONE_TUPLES.push_back(tupleSet.at(i).getStringVec());
				}
				for (unsigned int i = 0; i < relation.tupleSet.size(); ++i) {
					RELATION_TWO_TUPLES.push_back(relation.tupleSet.at(i).getStringVec());
				}
				//create giantSet of tuples
				for (unsigned int i = 0; i < RELATION_ONE_TUPLES.size(); ++i) {
					if (RELATION_ONE_TUPLES.at(i) == RELATION_TWO_TUPLES.at(i)) {
						giantSet.push_back(RELATION_ONE_TUPLES.at(i));
					}
				}
				std::sort(giantSet.begin(), giantSet.end());
				vector<Tuple> newTset;
				for (unsigned int i = 0; i < giantSet.size(); ++i) {
					vector<string> strV = giantSet.at(i);
					Tuple TU = strV;
					newTset.push_back(TU);
				}
				returnVal.tupleSet = newTset;
			}
			else {
				//cout << "headers are not exactly the same" << endl;
				vector<int> RELATION_ONE_INTVEC;
				vector<int> RELATION_TWO_INTVEC;
				for (unsigned int i = 0; i < RELATION_ONE_HEADER.size(); ++i) {
					for (unsigned int j = 0; j < RELATION_TWO_HEADER.size(); ++j) {
						if (RELATION_ONE_HEADER.at(i) == RELATION_TWO_HEADER.at(j)) {

							RELATION_ONE_INTVEC.push_back(i);
							RELATION_TWO_INTVEC.push_back(j);
							//cout << i << "::" << j << endl;
						}
					}
				}
				for (unsigned int i = 0; i < RELATION_TWO_INTVEC.size(); ++i) {
					//cout << RELATION_TWO_INTVEC.at(i);
				}
				//-> make a vector of ints for each relation to keep track of where matches occur
				//Make vector of vectors to store tuples and populate them with for loops
				for (unsigned int i = 0; i < tupleSet.size(); ++i) {
					RELATION_ONE_TUPLES.push_back(tupleSet.at(i).getStringVec());
				}
				//cout << "ENTERING ONE" << endl;
				for (unsigned int i = 0; i < RELATION_ONE_TUPLES.size(); ++i) {
					vector<string> schooner = RELATION_ONE_TUPLES.at(i);
					for (unsigned int j = 0; j < schooner.size(); ++j) {
						//cout << schooner.at(j);
					}
					//cout << endl;
				}
				

				for (unsigned int i = 0; i < relation.tupleSet.size(); ++i) {
					RELATION_TWO_TUPLES.push_back(relation.tupleSet.at(i).getStringVec());
				}
				//cout << "ENTERING TWO" << endl;
				for (unsigned int i = 0; i < RELATION_TWO_TUPLES.size(); ++i) {
					vector<string> schooner = RELATION_TWO_TUPLES.at(i);
					for (unsigned int j = 0; j < schooner.size(); ++j) {
						//cout << schooner.at(j);
					}
					//cout << endl;
				}
				vector<vector<string>> sharedTupleVec;
				//-> search each matched column for shared values and add to a seperate vector of values. This may need to be sorted later.
				//bool changeOccurred = false;
				if (RELATION_ONE_INTVEC.size() == 1) {
					for (unsigned int i = 0; i < RELATION_ONE_INTVEC.size(); ++i) {
						//cout << RELATION_ONE_INTVEC.at(i) << endl;
						//cout << RELATION_TWO_INTVEC.at(i) << endl;
						for (unsigned int q = 0; q < RELATION_ONE_TUPLES.size(); ++q) {
							vector<string> ONE = RELATION_ONE_TUPLES.at(q);

							for (unsigned int w = 0; w < RELATION_TWO_TUPLES.size(); ++w) {
								vector<string> TWO = RELATION_TWO_TUPLES.at(w);

								//cout << "TOPPER" << endl;
								vector<string> passON;

								if (ONE.at(RELATION_ONE_INTVEC.at(i)) == TWO.at(RELATION_TWO_INTVEC.at(i))) {

									//cout << ONE.at(RELATION_ONE_INTVEC.at(i)) << "::" << TWO.at(RELATION_TWO_INTVEC.at(i)) << endl;
									//-- MAKE A FUNCTION HERE TO ADD THESE TUPLES TOGETHER AND INSERT INTO NEW RELATION-- //

									//create vector of strings

									vector<string> sharedRelation = addVectors(ONE, TWO, RELATION_ONE_INTVEC.at(i), RELATION_TWO_INTVEC.at(i));
									sharedTupleVec.push_back(sharedRelation);

									//delete value for vector given on list two, as well as header. push the rest together

									//push back onto tuple vec

								}



							}
						}
					}
				}
				else {
					for (unsigned int q = 0; q < RELATION_ONE_TUPLES.size(); ++q) {
						vector<string> ONE = RELATION_ONE_TUPLES.at(q);

						for (unsigned int w = 0; w < RELATION_TWO_TUPLES.size(); ++w) {
							vector<string> TWO = RELATION_TWO_TUPLES.at(w);
							vector<string> sharedRelation = surrogate(ONE, TWO, RELATION_TWO_INTVEC);
							//cout << pushpoint
							sharedTupleVec.push_back(sharedRelation);
						}
					}
				}

				// -> add this separate sorted vector to our new relation we will be returning

				//combine headers
				vector<string> newHeader = combineHeaders(RELATION_ONE_HEADER, RELATION_TWO_HEADER, RELATION_TWO_INTVEC);
				for (unsigned int i = 0; i < newHeader.size(); ++i) {
					//cout << newHeader.at(i) << endl;
				}
				//RELATION_ONE_HEADER;
				/*
				if (sharedTupleVec.size() == 0) {
					if (RELATION_ONE_TUPLES.size() != 0) {
						if (RELATION_ONE_TUPLES.at(0).size() < newHeader.size()) {
							vector<string> xVec;
							cout << "this is a potential fix" << endl;
						}
					}
				}
				*/
				//output Shared Tuple Vector
				for (unsigned int i = 0; i < sharedTupleVec.size(); ++i) {
					vector<string> stringVec = sharedTupleVec.at(i);
					//cout << stringVec.size();
					for (unsigned int j = 0; j < stringVec.size(); ++j) {
						//cout << stringVec.at(j) << " ";
					}
					//cout << endl;
				}
				//create tuple Vec from string vec
				vector<Tuple> t_set;
				for (unsigned int i = 0; i < sharedTupleVec.size(); ++i) {
					vector<string> strV = sharedTupleVec.at(i);
					Tuple TU = strV;
					t_set.push_back(TU);
				}
				//cout << sharedTupleVec.size() << "::" << newTset.size() << endl;

				returnVal.relationScheme = newHeader;
				returnVal.tupleSet = t_set;
				return returnVal;

				//TESTING BLOCK ENTERED
			 ///*

			//output headers of new relation
				vector<string> rrv = returnVal.relationScheme.getStringVec();
				for (unsigned int i = 0; i < rrv.size(); ++i) {
					cout << rrv.at(i) << endl;
				}

				//output tuples of new relation
				//cout << t_set.size() << endl;
				for (unsigned int i = 0; i < t_set.size(); ++i) {
					Tuple tuple = t_set.at(i);
					vector<string> VP = tuple.getStringVec();
					for (unsigned int j = 0; j < VP.size(); j++) {
						//cout << "just making sure" << endl;
						cout << VP.at(j);
					}
					cout << endl;
				
				}
				//returnVal.tupleSet = t_set;
			}
		}
		else {
			bool testCase = false;

			for (unsigned int i = 0; i < RELATION_ONE_HEADER.size(); ++i) {
				for (unsigned int j = 0; j < RELATION_TWO_HEADER.size(); ++j) {
					if (RELATION_TWO_HEADER.at(j) == RELATION_ONE_HEADER.at(i)) {
						testCase = true;
					}
				}
			}
			if (testCase == true) {
				//cout << "in testCasetrue" << endl;
				//get headers
				vector<string> theHeaderVec;
				for (unsigned int i = 0; i < RELATION_ONE_HEADER.size(); ++i) {
					theHeaderVec.push_back(RELATION_ONE_HEADER.at(i));
				}
				for (unsigned int j = 0; j < RELATION_TWO_HEADER.size(); ++j) {
					theHeaderVec.push_back(RELATION_TWO_HEADER.at(j));
				}
				returnVal.relationScheme = theHeaderVec;

				//get tuples
				vector<vector<string>> giantSet;
				for (unsigned int i = 0; i < tupleSet.size(); ++i) {
					RELATION_ONE_TUPLES.push_back(tupleSet.at(i).getStringVec());
				}
				for (unsigned int i = 0; i < relation.tupleSet.size(); ++i) {
					RELATION_TWO_TUPLES.push_back(relation.tupleSet.at(i).getStringVec());
				}
				//create giantSet of tuples and populate with values
				if (RELATION_ONE_TUPLES.size() == RELATION_TWO_TUPLES.size()) {
					for (unsigned int i = 0; i < RELATION_ONE_TUPLES.size(); ++i) {
						vector<string> hVac = RELATION_ONE_TUPLES.at(i);
						if (RELATION_TWO_TUPLES.size() > i) {
							vector<string> cPap = RELATION_TWO_TUPLES.at(i);
							for (unsigned int j = 0; j < cPap.size(); ++j) {
								hVac.push_back(cPap.at(j));
							}
						}
						giantSet.push_back(hVac);
					}
				}
				std::sort(giantSet.begin(), giantSet.end());
				vector<Tuple> newTset;
				for (unsigned int i = 0; i < giantSet.size(); ++i) {
					vector<string> strV = giantSet.at(i);
					Tuple TU = strV;
					newTset.push_back(TU);
				}
				returnVal.tupleSet = newTset;

			}
			else {
				//cout << "in testCasefalse" << endl;
				vector<vector<string>> giantSet;
				for (unsigned int i = 0; i < tupleSet.size(); ++i) {
					RELATION_ONE_TUPLES.push_back(tupleSet.at(i).getStringVec());
				}
				for (unsigned int i = 0; i < relation.tupleSet.size(); ++i) {
					RELATION_TWO_TUPLES.push_back(relation.tupleSet.at(i).getStringVec());
				}

				vector<string> left_headers = getHeaderB(rule_input);
				vector<int> matching_values_one;
				for (unsigned int i = 0; i < RELATION_ONE_HEADER.size(); ++i) {
					for (unsigned int j = 0; j < left_headers.size(); ++j) {
						if (left_headers.at(j) == RELATION_ONE_HEADER.at(i)) {
							matching_values_one.push_back(i);
						}
					}
				}

				
				vector<vector<string>> updated_one;
				for (unsigned int i = 0; i < RELATION_ONE_TUPLES.size(); ++i) {
					vector<string> carryOver = RELATION_ONE_TUPLES.at(i);
					vector<string> newCarryOver;
					for (unsigned int j = 0; j < matching_values_one.size(); ++j) {
						newCarryOver.push_back(carryOver.at(matching_values_one.at(j)));
					}
					updated_one.push_back(newCarryOver);
				}

				vector<int> matching_values_two;
				for (unsigned int i = 0; i < RELATION_TWO_HEADER.size(); ++i) {
					for (unsigned int j = 0; j < left_headers.size(); ++j) {
						if (left_headers.at(j) == RELATION_TWO_HEADER.at(i)) {
							matching_values_two.push_back(i);
						}
					}
				}

				vector<vector<string>> updated_two;
				for (unsigned int i = 0; i < RELATION_TWO_TUPLES.size(); ++i) {
					vector<string> carryOver = RELATION_TWO_TUPLES.at(i);
					vector<string> newCarryOver;
					for (unsigned int j = 0; j < matching_values_two.size(); ++j) {
						newCarryOver.push_back(carryOver.at(matching_values_two.at(j)));
					}
					updated_two.push_back(newCarryOver);
				}

				//HEADERS SECTION

				vector<string> updated_headers;
				for (unsigned int i = 0; i < matching_values_one.size(); ++i) {
					updated_headers.push_back(RELATION_ONE_HEADER.at(matching_values_one.at(i)));
				}

				for (unsigned int i = 0; i < matching_values_two.size(); ++i) {
					updated_headers.push_back(RELATION_TWO_HEADER.at(matching_values_two.at(i)));
				}
				returnVal.relationScheme = updated_headers;
				//END HEADERS SECTION

				//multiply tuples
				vector<vector<string>> final_vector;
				for (unsigned int i = 0; i < updated_one.size(); ++i) {	
					for (unsigned int j = 0; j < updated_two.size(); ++j) {
						vector<string> combine_vec = updated_one.at(i);
						vector<string> join_vec = updated_two.at(j);
						for (unsigned int a = 0; a < join_vec.size(); ++a) {
							combine_vec.push_back(join_vec.at(a));
						}
						final_vector.push_back(combine_vec);
					}
				}
				std::sort(final_vector.begin(), final_vector.end());
				for (unsigned int i = 0; i < final_vector.size(); ++i) {
					vector<string> outputher = final_vector.at(i);
					for (unsigned int j = 0; j < outputher.size(); ++j) {
						//cout << outputher.at(j);
					}
					//cout << endl;
				}
				vector<Tuple> newTset;
				for (unsigned int i = 0; i < final_vector.size(); ++i) {
					vector<string> strV = final_vector.at(i);
					Tuple TU = strV;
					newTset.push_back(TU);
				}
				returnVal.tupleSet = newTset;
			}
			
			return returnVal;
		}
		return returnVal;
	}

	vector<string> combineHeaders(vector<string> headerOne, vector<string> headerTwo, vector<int> twoInt) {
		vector<string> returnVec;
		//cout << "LIST OF ONE" << endl;
		//delete value of shared column from TWO
		for (unsigned int i = 0; i < headerTwo.size(); ++i) {
			//cout << headerTwo.at(i);
		}
		for (unsigned int i = 0; i < twoInt.size(); ++i) {
			//cout << twoInt.at(i);
		}
		int sizer = twoInt.size() - 1;
		for ( int i = sizer; i >= 0; --i) {
			headerTwo.erase(headerTwo.begin() + twoInt.at(i));
		}

		for (unsigned int w = 0; w < headerOne.size(); ++w) {
			//cout << headerOne.at(w) << endl;
		}
		for (unsigned int w = 0; w < headerOne.size(); ++w) {
			returnVec.push_back(headerOne.at(w));
		}
		//cout << "LIST OF TWO" << endl;

		for (unsigned int w = 0; w < headerTwo.size(); ++w) {
			//cout << headerTwo.at(w) << endl;
		}
		for (unsigned int w = 0; w < headerTwo.size(); ++w) {
			returnVec.push_back(headerTwo.at(w));
		}
		//cout << "LIST AT NEW VEC" << endl;
		for (unsigned int w = 0; w < returnVec.size(); ++w) {
			//cout << returnVec.at(w) << endl;
		}
		return returnVec;
	}

	vector<string> addVectors(vector<string> ONE, vector<string> TWO, int one, int two) {
		vector<string>returnVec;
		//cout << "LIST OF ONE" << endl;
		//delete value of shared column from TWO
		TWO.erase(TWO.begin() + two);
		
		for (unsigned int w = 0; w < ONE.size(); ++w) {
			//cout << ONE.at(w) << endl;
		}
		for (unsigned int w = 0; w < ONE.size(); ++w) {
			returnVec.push_back(ONE.at(w));
		}
		//cout << "LIST OF TWO" << endl;
	
		for (unsigned int w = 0; w < TWO.size(); ++w) {
			//cout << TWO.at(w) << endl;
		}
		for (unsigned int w = 0; w < TWO.size(); ++w) {
			returnVec.push_back(TWO.at(w));
		}
		//cout << "LIST AT NEW VEC" << endl;
		for (unsigned int w = 0; w < returnVec.size(); ++w) {
			//cout << returnVec.at(w) << endl;
		}
		return returnVec;
	}

	void getTuples(vector<string> inputQuery) {
		//cout << "size is " << tupleSet.size();
		vector<Tuple> newTset;
		//cout << "at beginning, new tset is " << newTset.size() << endl;
		Tuple tupl;
		int testInt = 0;
		//cout << "currentInputQuery.size() " << inputQuery.size() << endl;
		for (unsigned int i = 0; i < tupleSet.size(); ++i) {
			tupl = tupleSet.at(i);
			testInt = tupl.testVals(inputQuery);
			//cout << testInt << " testInt is this " << endl;
			if (testInt == 1) {
				newTset.push_back(tupleSet.at(i));
				//cout << "pushback occurred" << endl;
				//tupleSet.at(i).toString();
			}
			//cout << "new indicator " << endl;
			
		}
		//cout << newTset.size() << "is the size" << endl;
		if (newTset.size() != 0) {
			cout << "Yes(" << newTset.size() << ")" << endl;
			tup.getVariableValues(newTset, inputQuery);
		}
		else {
			cout << "No" << endl;
		}
	}

	void outputRelationName() {
		cout << relationName << endl;
	}
	void selectValue() {} //index and value (relation column and value to select)
	void selectIndex() {} //parameters are indexand index(relation columns to select on same values)
	void project() {} //parameter is list of indices(the columns to keep)
	void rename() {} //parameter is list of names(defines the new scheme)
	void addTupleSet() {
		
	}
	string getRelationshipName() {
		return relationName;
	}
	void toString() {
		//cout << "IN @" <<  endl;
		//cout << relationName << endl;
		Scheme passer;
		passer = relationScheme;
		passer.toString();
	}
	void inputFacts(string input) {
		//inputTupleSet = inputTupleSet;
		relationName = input;
	}
	int getTupleVectorSize() {
		return tupleSet.size();
	}
	vector<string> getTupleVal(int i) {
		Tuple tup = tupleSet.at(i);
		vector<string>returnVal = tup.getStringVec();
		return returnVal;
	}
	string getStringsForVectorFromTuples(int i) {
		Tuple stringHelper;
		string nameString;
		stringHelper = tupleSet.at(i);
		nameString = stringHelper.getHelp();
		return nameString;
	}
	void removeRepeatedValues(vector<int> intVec) {
		//vector<int>testVec = { 2,4,1,10,13,5,7 };
		std::sort(intVec.begin(), intVec.end());
		int size = intVec.size() - 1;

		for (unsigned int i = size; i <= 0; --i) {
			//cout << intVec.at(i) << endl;
			//remove Tuple located at this value
			tupleSet.at(i).toString();
			tupleSet.erase(tupleSet.begin() + intVec.at(i));
		}

		//sortTupleSetFunction ****
		// add tuples to vector of vector of strings
		vector<vector<string>> bigvec;
		for (unsigned int i = 0; i < tupleSet.size(); ++i) {
			bigvec.push_back(tupleSet.at(i).getStringVec());
		}
		std::sort(bigvec.begin(), bigvec.end());
		if (bigvec.size() != 0) {
			//cout << bigvec.at(1).at(1) << endl;
		}
		while (tupleSet.size() != 0){
			tupleSet.erase(tupleSet.begin());
		}
		//cout << tupleSet.size() << endl;
		for (unsigned int i = 0; i < bigvec.size(); ++i) {
			tupleSet.push_back(bigvec.at(i));
		}
		
		//sort this vector by adding each vector to another vector of strings (combined)
		vector<string> newVec;
		for (unsigned int i = 0; i < bigvec.size(); ++i) {
			string tempString = "";
			for (unsigned int t = 0; t < bigvec.at(i).size(); ++t) {
				tempString = tempString + bigvec.at(i).at(t);
			}
			newVec.push_back(tempString);
			//cout << tempString << endl;
		}
		
		//sort this vector
		std::sort(newVec.begin(), newVec.end());
		for (unsigned int i = 0; i < newVec.size(); ++i) {
			//cout << newVec.at(i) << endl;
		}
		//cout << "done" << endl;
		//use this information to sort vector of vectors
		
		//replace tuple set one piece at a time by vector of vectors
	}
	void outputHeaders() {
		vector<string> stringVec = relationScheme.getStringVec();
		cout << stringVec.size() << "IS relationScheme size" << endl;
		for (unsigned int i = 0; i < stringVec.size(); ++i) {
			cout << stringVec.at(i) << endl;
		}
	}
	void outputTuple() {
		cout << "Tuple set size is " << tupleSet.size() << endl;
		for (unsigned int i = 0; i < tupleSet.size(); ++i) {
			tupleSet.at(i).toString();
		}
	}
	void inputTuple(Tuple AttributeList) {
		tupleSet.push_back(AttributeList);
	}
	Scheme getRelationshipAttributes() {
		return relationScheme;
	}
	void verifySize() {
		cout << tupleSet.size() << endl;
		for (unsigned int i = 0; i < tupleSet.size(); ++i) {
			Tuple newTup = tupleSet.at(i);
			vector<string> stringVec = newTup.getStringVec();
			//cout << stringVec.size() << endl;
			for (unsigned int j = 0; j < stringVec.size(); ++j) {
				cout << stringVec.at(j);
			}
			cout << endl;
		}
	}

	vector<string> getHeaderB(string rule) {
		vector<string>returnVal;
		//parse rule for LH headers and push them back
		bool testOne = true;
		bool testTwo = true;
		string tempStr = "";
		for (unsigned int i = 0; i < rule.size(); ++i) {
			if (rule.at(i) == ')') {
				if (testOne == true) {
					returnVal.push_back(tempStr);
					tempStr = "";
				}
				testOne = false;
			}
			if (testOne == true) {
				if (rule.at(i) == ',') {
					returnVal.push_back(tempStr);
					tempStr = "";
				}
			}
			if (testOne == true) {
				if (testTwo == false) {
					if (rule.at(i) != ',') {
						tempStr = tempStr + rule.at(i);
					}
				}
			}
			if (rule.at(i) == '(') {
				testTwo = false;
			}
		}
		//cout << "testing for header B" << endl;
		for (unsigned int i = 0; i < returnVal.size(); ++i) {
			//cout << returnVal.at(i) << endl;
		}
		return returnVal;
	}

	void alignment(Relation input, string testRule) {
		vector<string> headerA = relationScheme.getStringVec();
		vector<string> headerB = getHeaderB(testRule);
		
		//if (headerA == headerB) {
			//cout << "one";
		//}
		//else {
			//cout << "Test" << endl;
			//create new set of tuples with the correct order given from a taken vector of ints
			vector<int> placeHolders; // this should hold reorganized order that needs to be applied to input tuples
			//convert tuples to strings
			vector<string> inputHeaders = input.relationScheme.getStringVec();
			vector<string> mainHeaders = relationScheme.getStringVec();
			vector<vector<string>> mainVec;
			vector<vector<string>> inputVec;

			//TESTER SPACE ---
			///*
			//output input headers
			//cout << inputHeaders.size() << endl;
			for (unsigned int i = 0; i < inputHeaders.size(); ++i) {
				//cout << inputHeaders.at(i) << endl;
			}
			//output main headers
			//cout << "mains" << endl;
			for (unsigned int i = 0; i < mainHeaders.size(); ++i) {
				//cout << ":::::" << mainHeaders.at(i) << endl;
			}
			//*/
			//END TESTER SPACE ---i
			vector<int> constantStorage;
			vector<string> consStrStorage;
			for (unsigned int i = 0; i < mainHeaders.size(); ++i) {
				//cout << "$" << endl;
				string trString = mainHeaders.at(i);
				for (unsigned int j = 0; j < trString.size(); ++j) {
					if (trString.at(j) == '\'') {
						//cout << "#" << endl;
						constantStorage.push_back(i);
						consStrStorage.push_back(mainHeaders.at(i));
						break;
					}
				}
			}

			for (unsigned int i = 0; i < consStrStorage.size(); ++i) {
				//cout << consStrStorage.at(i) << endl;
			}

			for (unsigned int i = 0; i < mainHeaders.size(); ++i) {
				//cout << mainHeaders.at(i) << endl;
			}

			for (unsigned int i = 0; i < tupleSet.size(); ++i) {
				Tuple tuple = tupleSet.at(i);
				vector<string> stringVec = tuple.getStringVec();
				mainVec.push_back(stringVec);
			}
			for (unsigned int i = 0; i < input.tupleSet.size(); ++i) {
				Tuple tuple = input.tupleSet.at(i);
				vector<string> stringVec = tuple.getStringVec();
				inputVec.push_back(stringVec);
			}
			
			vector<vector<string>> newerVector;
			if (constantStorage.size() != 0) {
				//cout << "!" << endl;
				
				for (unsigned int i = 0; i < mainVec.size(); ++i) {
					vector<string> stor_off = mainVec.at(i);
					for (unsigned int j = 0; j < stor_off.size(); ++j) {
						//vector<string> run_off = mainVec.at(j);	
						for (unsigned int t = 0; t < consStrStorage.size(); ++t) {
							if (consStrStorage.at(t) == stor_off.at(j)) {
								//cout << "@" << endl;
								//cout << "identifier" << stor_off.at(j) << endl;
								newerVector.push_back(mainVec.at(i));
							}
						}
					}
				}
			}
			//cout << "NNNNNNOOOOOO" << " " << newerVector.size() << endl;
			if (newerVector.size() != 0) {
				//cout << "YEP" << endl;
				mainVec = newerVector;
			}
			for (unsigned int i = 0; i < mainVec.size(); ++i) {
				vector<string> stringer = mainVec.at(i);
				for (unsigned int j = 0; j < stringer.size(); ++j) {
					//cout << stringer.at(j) << endl;
				}
			}
			
			for (unsigned int i = 0; i < mainHeaders.size(); ++i) {
				for (unsigned int j = 0; j < headerB.size(); ++j) {
					if (mainHeaders.at(i) == headerB.at(j)) {
						placeHolders.push_back(j);
					}
				}
			}
			//}

			//cout << "PLaceholders size is " << placeHolders.size() << endl;
			for (unsigned int i = 0; i < placeHolders.size(); ++i) {
				//cout << placeHolders.at(i) << endl;
			}
			// apply correct order to input.tupleSet
			vector<vector<string>> returnVal;
			for (unsigned int i = 0; i < mainVec.size(); ++i) {
				vector<string> stringVec = mainVec.at(i);
				vector<string> newVec;
				//push back input vec values in the correct order
				for (unsigned int j = 0; j < placeHolders.size(); ++j) {
					newVec.push_back(stringVec.at(placeHolders.at(j)));
				}
				returnVal.push_back(newVec);
			}
			//cout << returnVal.size() << "::" << mainVec.size();
			std::sort(returnVal.begin(), returnVal.end());
			//set return val equal to tupleSet of main
			vector<Tuple> newTset;
			for (unsigned int i = 0; i < returnVal.size(); ++i) {
				Tuple tuple = returnVal.at(i);
				newTset.push_back(tuple);
			}
			tupleSet = newTset;
		//}
		// Sort the Tuples list!! (may have to convert into string and then back into tuples)
	}
	vector<string> surrogate(vector<string> ONE, vector<string> TWO, vector<int> RELATION_TWO_INTVEC) {
		//delete values of two given in relationTwoIntvec
		int it = RELATION_TWO_INTVEC.size() - 1;

		//testcases
		for (unsigned int i = 0; i < TWO.size(); ++i) {
			//cout << TWO.at(i) << endl;
		}
		for (unsigned int i = 0; i < RELATION_TWO_INTVEC.size(); ++i) {
			//cout << RELATION_TWO_INTVEC.at(i) << endl;
		}

		for (int i = it; i >= 0; --i) {
			//cout << i << endl;
			if (i == 0) {
				TWO.erase(TWO.begin());
			}
			else if(i > 0) { TWO.erase(TWO.begin() + i); }
			//else if (i > 100000){ break; }
			
		}

		//--end

		vector<string> returnVal;
		for (unsigned int i = 0; i < ONE.size(); ++i) {
			returnVal.push_back(ONE.at(i));
		}
		for (unsigned int i = 0; i < TWO.size(); ++i) {
			returnVal.push_back(TWO.at(i));
		}
		return returnVal;
	}
	void sortThoseTuples() {
		vector<vector<string>> tuplesVec;
		for (unsigned int i = 0; i < tupleSet.size(); ++i) {
			tuplesVec.push_back(tupleSet.at(i).getStringVec());
		}
		sort(tuplesVec.begin(), tuplesVec.end());
		vector<Tuple> newTupleVec;
		for (unsigned int i = 0; i < tuplesVec.size(); ++i) {
			newTupleVec.push_back(tuplesVec.at(i));
		}
		if (tupleSet.size() == newTupleVec.size()) {
			tupleSet = newTupleVec;
		}
	}
};
#endif