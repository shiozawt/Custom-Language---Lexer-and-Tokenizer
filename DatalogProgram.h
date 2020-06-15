#ifndef DATALOG_PROGRAM
#define DATALOG_PROGRAM
//#include "Token.h"
#include "Lexer.h"
#include "Rule.h"
#include "Parameter.h"
#include "Interpreter.h"

#include <iostream>
#include <vector>


class DatalogProgram {
private:
	vector<Parameter> domain;
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector <Predicate> queries;
	vector<Rule> rules;
	vector<Predicate> outputSchemes;
	Parameter parameterData;
	Predicate predicateData;
	Rule ruleData;
	Interpreter ipt;
	//Lexer lexerVal;
public:
	DatalogProgram() {}
	DatalogProgram(vector<Parameter> inputdomain, vector<Predicate> inputschemes, vector<Predicate> inputfacts, vector <Predicate> inputqueries, vector<Rule> inputrules) {

		domain = inputdomain;
		schemes = inputschemes;
		facts = inputfacts;
		queries = inputqueries;
		rules = inputrules;
	}
	void schemePasser(vector<Predicate> inputSchemes) {
		
		outputSchemes = inputSchemes;
		//cout << outputSchemes.size() << endl;
		
	}
	vector<Predicate> schemeOutput() {
		cout << "KJDLKJFSL:KS" << outputSchemes.size() << endl;
		return outputSchemes;
	}

	void toString() {
		//cout << "Inside datalog program ToString" << endl;
		//parameterData.toString();
		//cout << "Schemes(" << schemes.size() << "):" << endl;
		int schemeHolder = schemes.size();
		//schemePasser(schemes);
		//schemeOutput();
		ipt.ipt(schemes, facts, queries, rules);
		for (int i = 0; i < schemeHolder; ++i) {
			//cout << "  " << schemes.front().getString() << endl;
			schemes.erase(schemes.begin());
		}
		//cout << "Facts(" << facts.size() << "):" << endl;
		int factsHolder = facts.size();
		for (int i = 0; i < factsHolder; ++i) {
			//cout << "  " << facts.front().getString() << endl;
			facts.erase(facts.begin());
		}
		
		
		ruleData.toString(rules);

		//cout << "Queries(" << queries.size() << "):" << endl;
		int queriesHolder = queries.size();
		for (int i = 0; i < queriesHolder; ++i) {
			//cout << "  " << queries.front().getString() << endl;
			queries.erase(queries.begin());
		}
		parameterData.toString(domain);
	}
	void addToScheme(Predicate input) {
		schemes.push_back(input);
	}
	void createNewParameter(bool ToF, string input) {
		Parameter newParameter(ToF, input);
		addToDomain(newParameter);
	}
	void addToDomain(Parameter input) {
		domain.push_back(input);
	}
	void addToQueries(Predicate input) {
		queries.push_back(input);
	}
	void addToRules(Rule tempString) {
		rules.push_back(tempString);
	}
	void addToFacts(Predicate input) {
		facts.push_back(input);
	}
	Predicate createPredicate(string input){
		Predicate newPredicate(input);
		return newPredicate;
	}
};
#endif