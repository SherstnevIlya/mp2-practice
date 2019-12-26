#pragma once

#include "TStack.h"
#include <iostream>
#include <string>
#include <cstdlib>

static class Calculator {
public:
	struct Operand {
		std::string name;
		double value;
		Operand* next;
	};

	static std::string ToPostfixForm(const std::string&);
	static double Calculate(const std::string&, Operand*&);
	static void Fill(Operand*&, const std::string&);

private:
	enum class TypeSymbol {
		operation, operand, number, space, openingBracket, closingBracket, invalid
	};
	static void AddUnique(const std::string&, Operand*&);
	static bool IsVarExist(const std::string&, Operand*);
	static double GetValue(const std::string&, Operand*);
	static TypeSymbol GetType(const char);
	static int PriorityOperations(const char);
	static bool IsNumber(Operand*);
};