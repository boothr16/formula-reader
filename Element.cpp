// support functions for keeping track of elements in a chemical equation
#include "Element.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Element::Element() //default constructor
{
	Symbol = " ";
	NumAtoms = 0;
}

Element::Element(string s, int n) //overloaded constructor
{
	Symbol = s;
	NumAtoms = n;
}

string Element::getSymbol() const
{
	return Symbol;
}

int Element::getNumAtoms() const
{
	return NumAtoms;
}

void Element::setNumAtoms(int n)
{
	NumAtoms = n;
}

// support for assignments
const Element& Element::operator=(const Element& e)
{
	// bypass self assignment
	if (this != &e)
	{
		Symbol = e.Symbol;
		NumAtoms = e.NumAtoms;
	}
	return *this;
}

// support for output to monitor
ostream& operator<<(ostream& out, const Element& e)
{
	out << setw(20) << e.Symbol << "\t"
		<< setw(20) << e.NumAtoms << "\t";
	return out;
}

// support for comparison of two elements
bool Element::operator==(const Element& rightObj) const
{
	return (Symbol == rightObj.Symbol); //Elements are equal if they have the same symbol
}
// end of the class member functions
