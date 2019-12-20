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
	static double Calculate(std::string, Operand*);
	static void Fill(Operand*&, std::string);
	static bool IsNumber(Operand*);

private:
	enum class TypeSymbol {
		operation, operand, number, space, openingBracket, closingBracket, invalid
	};
	static void AddUnique(std::string, Operand*&);
	static bool IsVarExist(std::string, Operand*);
	static double GetValue(std::string, Operand*);
	static TypeSymbol GetType(const char);
	static int PriorityOperations(const char);
};