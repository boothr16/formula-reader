/***********************************************************************************
AtomCounter v1 (by Robert Booth)
--------------
Gets a chemical formula from the user and counts the number of atoms of each element in the formula.
TWO LIMITATIONS:
1) All subscripts must be less than 10 (single-digit subscripts only)
2) Each element in the formula can only appear once
*************************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <set>
#include "Element.h"
using namespace std;

int findElement(Element, Element[], int);
void addElement(Element, Element[], int&);
void parseFormula(string, Element[]);


int main()
{
	// Object used to store data
	string formula;
	const int LIST_LENGTH = 10;
	

	// 1. Display descriptive message to user
	cout << "This program takes an chemical formula as input and returns the symbol and number of each element as output."
		 << "\nAll input is case-sensitive. Subscripts in the formula must be less than 10." << endl;

	// 2. Declare array of LIST_LENGTH Elements
	Element list[LIST_LENGTH];

	// 3. Prompt user for input and store input as a string
	cout << "\nEnter a valid chemical formula (case-sensitive): ";
	cin >> formula;

	// 4. Read out formula using parseFormula() function
	parseFormula(formula, list);
}

int findElement(Element Atom, Element List[], int NumElements)
{
	// 1. Assume that the item is NOT in the list
	int Save = -1; //placeholder variable

	// 2. Loop over the list length
	for (int i = 0; i < NumElements; i++)
	{
		if (List[i] == Atom)
		{
			Save = i;
			break;
		}
	}
	return Save;
}

void addElement(Element Atom, Element List[], int& NumElements)
{

	// 1. search for element in list of elements in formula
	int index = findElement(Atom, List, NumElements);

	// 2. If the element is NOT in the list
	if (index == -1)
	{
		List[NumElements] = Atom; //adds new item to list with all associated attributes
		NumElements++;
	}

	// 3. Else element is already in list
	else
	{
		List[index].setNumAtoms(Atom.getNumAtoms() + List[index].getNumAtoms()); //add to element's atom count
	}
}

void parseFormula(string formula, Element list[])
{
	string segment;
	int subscript;
	int posRightParen;
	int parenSub;
	int numElements = 0;
	posRightParen = formula.find(')'); //find position in formula of partner right parenthesis. Returns -1 if no parenthesis is found.
	if (posRightParen != -1) //if a right parenthesis is found
		parenSub = stoi(formula.substr(posRightParen + 1, 1)); //stores subscript outside of parentheses

	// 5. Iterate through formula, adding element symbols and number of each atom to list of elements
	for (int i = 0; i < formula.length(); i++)
	{
		if (i != 0 && formula[i - 1] == '(') //to avoid repeating elements in parentheses
			i = (posRightParen + 1); //skip to next element, assuming a digit follows the right parenthesis

		if (isupper(formula[i])) //if current character is upper-case
		{
			if (isupper(formula[i + 1])) //if next letter is upper-case
			{
				segment = formula.substr(i, 1);
				Element elem(segment, 1); //set atoms of this element equal to 1
				addElement(elem, list, numElements);
			}
			else if (isdigit(formula[i + 1])) //if next character is a number
			{
				segment = formula.substr(i, 1);
				subscript = stoi(formula.substr(i + 1, 1));
				Element elem(segment, subscript); //set atoms of this element equal to the subscript
				addElement(elem, list, numElements);
			}
			else if (islower(formula[i + 1])) //if next letter is lower-case, the chemical symbol has 2 letters
			{
				if (isdigit(formula[i + 2])) //checks to see if 2-letter symbol has a subscript
				{
					segment = formula.substr(i, 2);
					subscript = stoi(formula.substr(i + 2, 1));
					Element elem(segment, subscript);
					addElement(elem, list, numElements);
				}
				else
				{
					segment = formula.substr(i, 2);
					Element elem(segment, 1);
					addElement(elem, list, numElements);
				}
			}
			else if (formula[i + 1] == '\0') //if at the end of formula
			{
				segment = formula.substr(i, 1);
				Element elem(segment, 1);
				addElement(elem, list, numElements);
			}
			else
			{
				cout << "Input error!" << endl;
				break;
			}
		} //end if

		else if (formula[i] == '(') // if current character is a left parenthesis
		{
			for (int j = i + 1; j < posRightParen; j++)
			{
				if (isupper(formula[j])) //if current character in parentheses is upper-case
				{
					if (isupper(formula[j + 1]))
					{
						segment = formula.substr(j, 1);
						Element elem(segment, parenSub); //sets number of atoms equal to subscript outside of parentheses
						addElement(elem, list, numElements);
					}
					else if (isdigit(formula[j + 1]))
					{
						segment = formula.substr(j, 1);
						subscript = stoi(formula.substr(j + 1, 1));
						Element elem(segment, (subscript * parenSub)); //sets number of atoms equal to element subscript times subscript outside of parentheses
						addElement(elem, list, numElements);
					}
					else if (islower(formula[j + 1])) //if next letter is lower-case, the chemical symbol has 2 letters
					{
						if (isdigit(formula[j + 2])) //checks to see if 2-letter symbol has a subscript
						{
							segment = formula.substr(j, 2);
							subscript = stoi(formula.substr(j + 2, 1));
							Element elem(segment, (subscript * parenSub));
							addElement(elem, list, numElements);
						}
						else
						{
							segment = formula.substr(j, 2);
							Element elem(segment, parenSub);
							addElement(elem, list, numElements);
						}
					}
					else if (formula[j + 1] == ')') //if at the end of group in parentheses
					{
						segment = formula.substr(j, 1);
						Element elem(segment, parenSub);
						addElement(elem, list, numElements);
						i = posRightParen;
					}
					else
					{
						cout << "Input error!" << endl;
						break;
					}
				}
			} //end for
		} //end else if
	} //end for

	for (int i = 0; i < numElements; i++)
	{
		cout << list[i].getSymbol() << " " << list[i].getNumAtoms() << endl;
	}
}



