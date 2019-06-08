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
#include "Commands.h"
using namespace std;

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/') {
		return true;
	}
	return false;
}

bool isDigit(char c)
{
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}

double CalculateSimpleExpression(int op1, int op2, char operate)
{
	switch (operate) {
	case '+': {
		return (op1 + op2); break;
	}
	case '-': {
		return (op1 - op2); break;
	}
	case '*': {
		return (op1 * op2); break;
	}
	case '/': {
		return (op1 / op2); break;
	}
	default: {
		cerr << "Error";
		return 0;
	}
	}
}

double CalculatePostfix(char* postfix)
{
	Stack<double> st;
	for (int i = 0; postfix[i] != '\0'; i++) {
		if (postfix[i] == ' ') {
			continue;
		}
		else if (isOperator(postfix[i])) {
			double op2 = st.top();
			st.pop();
			double op1 = st.top();
			st.pop();
			double res = CalculateSimpleExpression(op1, op2, postfix[i]);
			st.push(res);
		}
		else if (isDigit(postfix[i])) {
			double op = 0;
			while (postfix[i] != '\0' && isDigit(postfix[i])) {
				op = (10 * op) + (postfix[i] - '0');
				i++;
			}
			i--;
			st.push(op);
		}
	}
	return st.top();
}

char* prefixToPostfix(char* prefix)
{
	Stack<double> ints;
	Stack<char> ops;
	int expLength = 0;
	while (prefix[expLength] != '\0') {
		expLength++;
	}
	char* postfix = new char[expLength + 1];
	postfix[0] = '\0';
	char* pointer = NULL;
	char* nextToAdd = new char[64];
	for (pointer = prefix; *pointer != '\0'; ) {

		if (isDigit(*pointer)) {
			ints.push(strtod(pointer, &pointer));
			pointer++;
		}
		else {
			ops.push(*pointer);
			pointer++;
			pointer++;
		}

		if (ints.getSize() == 2) {
			int op2 = ints.top();
			ints.pop();
			int op1 = ints.top();
			ints.pop();
			char op = ops.top();
			ops.pop();
			_itoa(op1, nextToAdd, 10);
			strcat(postfix, nextToAdd);
			nextToAdd[0] = ' ';
			nextToAdd[1] = '\0';
			strcat(postfix, nextToAdd);
			_itoa(op2, nextToAdd, 10);
			strcat(postfix, nextToAdd);
			nextToAdd[0] = ' ';
			nextToAdd[1] = '\0';
			strcat(postfix, nextToAdd);
			nextToAdd[0] = op;
			nextToAdd[1] = '\0';
			strcat(postfix, nextToAdd);
			nextToAdd[0] = ' ';
			nextToAdd[1] = '\0';
			strcat(postfix, nextToAdd);
		}
	}

	if (*pointer == '\0') {
		while (!ints.isEmpty()) {
			int nxt = ints.top();
			_itoa(nxt, nextToAdd, 10);
			strcat(postfix, nextToAdd);
			ints.pop();
			nextToAdd[0] = ' ';
			nextToAdd[1] = '\0';
			strcat(postfix, nextToAdd);
		}
		while (!ops.isEmpty()) {
			char op = ops.top();
			nextToAdd[0] = op;
			nextToAdd[1] = '\0';
			strcat(postfix, nextToAdd);
			ops.pop();
			nextToAdd[0] = ' ';
			nextToAdd[1] = '\0';
			strcat(postfix, nextToAdd);
		}
	}
	postfix[expLength] = '\0';
	return postfix;
}

//TODO:
bool isExpressionValid(char* pre)
{
	return true;
}

char* ExpressionTranslator(string expression, ListOfOperators* operators)
{
	char* newExpression = new char[expression.length() + 1];
	for (unsigned int i = 0; i < expression.length(); i++) {
		if (!isDigit(expression[i]) && expression[i] != ' ' && !isDigit(expression[i + 1])) {
			newExpression[i] = operators->getTrueOperator(expression[i]);
		}
		else {
			newExpression[i] = expression[i];
		}
		newExpression[expression.length()] = '\0';
	}
	return newExpression;
}

ListOfOperators* ReadOperators(string fileOperators)
{
	ListOfOperators* operators = new ListOfOperators();
	ifstream fileOp;
	fileOp.open(fileOperators.c_str());
	if (fileOp.is_open()) {
		while (fileOp.peek() != EOF) {
			string info;
			getline(fileOp, info);
			operators->Append(info[0], info[2], (info[4] - '0'));
		}
		return operators;
	}
	fileOp.close();
	cerr << "Error\n";
	exit(0);
	return NULL;
}

char* ReadExpression(string fileExpression)
{
	string exp;
	char* expression;
	ifstream fileExp;
	fileExp.open(fileExpression.c_str());
	if (fileExp.is_open()) {
		getline(fileExp, exp);
		expression = new char[exp.length() + 1];
		for (unsigned int i = 0; i < exp.length(); i++) {
			expression[i] = exp[i];
		}
		expression[exp.length()] = '\0';
		return expression;
	}
	fileExp.close();
	cerr << "Error\n";
	exit(0);
	return 0;
}

char* PrefixReverse(string fileExpression)
{
	Stack<char*> reversed;
	char buffer[64];
	int length = 0;
	char space[] = { ' ', '\0' };
	ifstream fileExp;
	fileExp.open(fileExpression.c_str());
	if (fileExp.is_open()) {
		while (fileExp >> buffer) {
			char* str = new char[strlen(buffer) + 1];
			strcpy(str, buffer);
			reversed.push(str);
			length += strlen(buffer) + 1;
		}
	}
	char* prefix = new char[length];
	prefix[0] = '\0';
	while (!reversed.isEmpty()) {
		strcat(prefix, reversed.top());
		reversed.pop();
		strcat(prefix, space);
	}
	return prefix;
}
