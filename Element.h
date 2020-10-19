//declaration of class to support elements in a chemical formula
#ifndef ELEMENT
#define ELEMENT

#include <iostream>
#include <string>
using namespace std;

class Element
{
public: //member functions
   //constructors
	Element(); //default constructor
	Element(string, int); //parameterized constructor

	//extractors
	string getSymbol() const;
	int getNumAtoms() const;

	//mutators
	void setNumAtoms(int);

	//support for assignments, output, and comparison
	const Element& operator=(const Element&);
	friend ostream& operator<<(ostream&, const Element&);
	bool operator==(const Element& rightObj) const; //allows for comparison of two fractions

private: //data attributes
	string Symbol;
	int NumAtoms;
};

#endif //end of class
