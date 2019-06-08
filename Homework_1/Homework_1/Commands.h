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
#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include "Stack.h"
#include "Operator.h"
#include "ListOfOperators.h"
 //using namespace std;

bool isOperator(char);
bool isDigit(char);
char* prefixToPostfix(char*);
double CalculateSimpleExpression(int, int, char);
double CalculatePostfix(char*);
bool isExpressionValid(char*);
char* ExpressionTranslator(std::string, ListOfOperators*);
ListOfOperators* ReadOperators(std::string);
char* ReadExpression(std::string);
char* PrefixReverse(std::string);

#endif // COMMANDS_H_INCLUDED
