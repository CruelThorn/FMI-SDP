/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task 1
 * @compiler VC
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"
#include "Commands.h"
using namespace std;

int main()
{
	string fileOperators, fileExpression;
	cin >> fileExpression;
	cin >> fileOperators;
	ListOfOperators* oplist = ReadOperators(fileOperators);
	char* expressionFromFile = ReadExpression(fileExpression);
	if (!isExpressionValid(expressionFromFile)) {
		cerr << "Error";
		return 0;
	}

	char* prefixExpressionWithOperators = new char[strlen(ExpressionTranslator(expressionFromFile, oplist)) + 1];
	prefixExpressionWithOperators = ExpressionTranslator(expressionFromFile, oplist);
	prefixExpressionWithOperators[strlen(ExpressionTranslator(expressionFromFile, oplist))] = '\0';

	char* postFixWithSymbols = prefixToPostfix(expressionFromFile);
	char* postFixWithOperators = prefixToPostfix(prefixExpressionWithOperators);

	double result = CalculatePostfix(postFixWithOperators);

	for (int i = 0; postFixWithSymbols[i] != '\0'; i++) {
		cout << postFixWithSymbols[i];
	}
	cout << "\n" << result << "\n";
	return 0;
}
