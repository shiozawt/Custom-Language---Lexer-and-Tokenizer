#ifndef INTERPRETER
#define INTERPRETER
#include "Database.h"
#include "ParserMain.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Interpreter
{
private:
	vector<Tuple> tupleVec;
	vector<Relation> RelationVector;
	Relation test;
	Scheme testtwo;
	Database DataB;
	vector<string> schemeVector;
	vector<Predicate> PredicateVector;
	//DatalogProgram data;
	//ParserMain obj;
public:
	Interpreter() {}
	void Interpret() {
		schemeInterpreter();
		//createRelation();
	}
	//obj(myLexer.getTokens());
	//obj = 

	void ipt(vector<Predicate> scheme_input, vector<Predicate> fact_input, vector <Predicate> queries, vector<Rule> rules) {
		PredicateVector = scheme_input;
		int schemeSize = PredicateVector.size();
		for (int i = 0; i < schemeSize; ++i) {
			string str = PredicateVector.front().getString();
			getSchemeParts(str);
			//cout << str << endl;
			//schemeVector.push_back(str);
			PredicateVector.erase(PredicateVector.begin());
		}
		int factSize = fact_input.size();
		//vector<Predicate> factInputHolder;
		//factInputHolder = fact_input;
		for (int i = 0; i < factSize; ++i) {
			string str = fact_input.front().getString();
			//cout << fact_input.at(i).getString() << endl;
			getFactParts(fact_input.front().getString());
			fact_input.erase(fact_input.begin());
		}
		DataB.getString();
			//myset.insert (it,25);    
		//testFunction();
		DataB.testIfFactIsStored();
		//DataB.removeDuplicateFacts();
		
		rulesOut(rules);
		cout << endl;
		cout << "Query Evaluation" << endl;
		queriesOut(queries);
	}
	void rulesOut(vector<Rule> rules) {
		
		//-- declared a vector of strings, input rules as strings, and passed to Database function "ruleEval"

		vector<string> ruleVec;
		for (unsigned int i = 0; i < rules.size(); ++i) {
			string str = rules.at(i).getString();
			ruleVec.push_back(str);
		}
		cout << "Rule Evaluation" << endl;
		DataB.ruleEval(ruleVec);
	}
	void queriesOut(vector<Predicate>queries) {
		int queriesSize = queries.size();
		for (int i = 0; i < queriesSize; ++i) {
			string str = queries.front().getString();
			cout << str << " ";
			DataB.getQueries(str);
			queries.erase(queries.begin());
		}

		//TODO!!
		//Test Relations against queries based on names. good luck
	}
	void testFunction() {
		
		//string, vector<string>, set<Tuple>
		string name;
		vector<string> newStringVec;
		set<Tuple> NewTupleSet;
		//Relation R(name, newStringVec, NewTupleSet);
		//RelationVector.push_back(R);

		//RelationVector.at(0).addTupleSet();
		for (unsigned int i = 0; i < RelationVector.size(); i++) {
			string getString = RelationVector.at(0).getRelationshipName();
			Scheme getScheme = RelationVector.at(0).getRelationshipAttributes();
		}
	}


	void getFactParts(string input) {
		
		vector<string> AttributeList;
		vector<string> nameHolder;
		string nameString = "";
		int charCounter = 0;
		//tupleSet.insert(nameHolder,AttributeList);
		int sizeInt = input.size();

		for (int i = 0; i < sizeInt; ++i) {
			if (input.at(i) != '(') {
				nameString = nameString + input.at(i);
				charCounter += 1;
			}
			else {
				charCounter += 1;
				break;
			}
		}
		nameHolder.push_back(nameString);

		string AtrStr = "";

		for (int i = charCounter; i < sizeInt; ++i) {
			//cout << "input is " << input.at(i) << " and i is " << i << endl;
			if (input.at(i) == ',') {
				//cout << "this is a comma" << endl;
				AttributeList.push_back(AtrStr);
				//cout << AtrStr;
				AtrStr = "";
			}
			else if (input.at(i) == ')') {
				//cout << "this is a right parenthesis" << endl;
				AttributeList.push_back(AtrStr);
				//cout << AttributeList.at(1);
				AtrStr = "";
				break;
			}
			else {
				AtrStr = AtrStr + input.at(i);
			}
		}
		Tuple newTuple(AttributeList);
		Tuple nameTuple(nameHolder);
		//newTuple.toString();
		tupleVec.push_back(AttributeList);
		//cout << tupleVec.size() << endl;
		DataB.addFactToMap(AttributeList, nameString);
	}
	void createSchemeRelation(string nameString, vector<string> AttributeList) {
		//cout << nameString << endl;
	for (unsigned int i = 0; i < AttributeList.size(); i++) {
		//cout << AttributeList.at(i) << endl;
	}
	Scheme myScheme(AttributeList);
	//myScheme.toString();
	vector<Tuple> tupleSet;
	Relation relation(nameString, myScheme, tupleSet);
		
	DataB.AddToMap(nameString, relation);
	//mymap.insert ( std::pair<char,int>('a',100) );
	}

	void getSchemeParts(string input) {
		int sizeInt = input.size();
		int charCounter = 0;
		string nameString = "";
		for (int i = 0; i < sizeInt; ++i) {
			if (input.at(i) != '(') {
				nameString = nameString + input.at(i);
				charCounter += 1;
			}
			else {
				charCounter += 1;
				break;
			}
		}
		//cout << nameString << endl;
		//cout << charCounter << " " << sizeInt << endl;
		
		vector<string> AttributeList;
		string AtrStr = "";

		for (int i = charCounter; i < sizeInt; ++i) {
			//cout << "input is " << input.at(i) << " and i is " << i << endl;
			if (input.at(i) == ',') {
				//cout << "this is a comma" << endl;
				AttributeList.push_back(AtrStr);
				//cout << AttributeList.front();
				AtrStr = "";
			}
			else if (input.at(i) == ')') {
				//cout << "this is a right parenthesis" << endl;
				AttributeList.push_back(AtrStr);
				//cout << AttributeList.at(1);
				AtrStr = "";
				break;
			}
			else {
				AtrStr = AtrStr + input.at(i);
			}
		}
		//cout << AttributeList.front() << endl;
		//cout << "attribute count" << AttributeList.size() << endl;
		createSchemeRelation(nameString, AttributeList);
	}

	void schemeInterpreter() {
		//pass in schemes
		// for each scheme, create a relation
		// for said relation, use name and parameter for given scheme
	} 
	//for each scheme ‘s’ create a relation using nameand parameter values from ‘s’
	void createRelation() {
		string name = "one";
		Scheme scheme;
		vector<Tuple> newSet;
		vector<string> TupleInput;
		//newSet.insert(TupleInput);
		Relation newRelation(name, scheme, newSet);
		//cout << "newRelation created" << endl;
		//std::string inputRelationName, Scheme inputRelationScheme, std::set<Tuple> inputTupleSet
	}
	void factInterpreter() {
	//pass in facts
	// for each fact, make a tuple
	// add fact and tuple to given relation with the same name as 'f'
	} 
	//for each fact ‘f’ make a tuple ‘t’ using the values from ‘f’ and add ‘t’ to relation with the same name as ‘f’ 

	void queryInterpreter() {
	
	} 
	// for each query ‘q’ get the relation ‘r’ with the same name as the query ‘q’
	// select the tuples that match the query ‘q’ (run a select for each parameter in the query) project using the positions of the variables in ‘q’
	// rename to match the names of variables in ‘q’ print the resulting relation
								
};
#endif
