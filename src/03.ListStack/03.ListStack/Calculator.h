#pragma once

#include "TArrayStack.h"
#include "TListStack.h"
#include <iostream>
#include <string>
#include <cstdlib>

class Calculator {
public:
	struct Operand {
		std::string name;
		double value;
		Operand* next;
	};
private:
	TStack<char>* operators;
	TStack<std::string>* operands;
	TStack<std::string>* reverseStackOfOperands;
	TStack<double>* calc;
	enum class TypeSymbol {
		operation, operand, number, space, openingBracket, closingBracket, invalid
	};
	void AddUnique(const std::string&, Operand*&);
	bool IsVarExist(const std::string&, Operand*);
	double GetValue(const std::string&, Operand*);
	TypeSymbol GetType(const char);
	int PriorityOperations(const char);
	bool IsNumber(Operand*);
public:
	explicit Calculator(bool isTListStack = false);
	~Calculator();
	std::string ToPostfixForm(const std::string&);
	double Calculate(const std::string&, Operand*&);
	void Fill(Operand*&, const std::string&);
};