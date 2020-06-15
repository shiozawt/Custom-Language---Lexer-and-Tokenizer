#ifndef SCHEME
#define SCHEME
#include <vector>
#include <string>
using namespace std;
class Scheme
{
private:
	//A scheme is a list of attribute names
	vector<string> attributeNameSet;
public:
	Scheme() {}
	//Each scheme in the program defines a relation in the database
	Scheme(std::vector<std::string> inputNameSet) {
		attributeNameSet = inputNameSet;
	}
	vector<string> getStringVec() {
		return attributeNameSet;
	}
	void toString() {
		//cout << "IN 3" << attributeNameSet.size() << endl;
		
		for (unsigned int i = 0; i < attributeNameSet.size(); ++i) {
			cout << attributeNameSet.at(i) << endl;
		}
	}
};
#endif

