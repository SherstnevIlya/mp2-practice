#include "Calculator.h"
#include <iostream>
#include <string>

void main() {
	std::string Exp, postExp;
	Calculator::Operand* head = nullptr;
	std::cout << "Enter expression: ";
	std::getline(std::cin, Exp);
	try {
		postExp = Calculator::ToPostfixForm(Exp);
		std::cout << "Postfix form: " << postExp << std::endl;
	}
	catch (std::string k) {
		std::cout << k << std::endl;
		return;
	}
	try {
		Calculator::Fill(head, postExp);
	}
	catch (std::string k) {
		std::cout << k << std::endl;
		return;
	}
	Calculator::Operand* tmp = head;
	while (tmp != nullptr) {
		if (!Calculator::IsNumber(tmp)) {
			std::cout << tmp->name << " = ";
			std::cin >> tmp->value;
		}
		tmp = tmp->next;
	}
	try {
		double res = Calculator::Calculate(postExp, head);
		std::cout << "Result: " << res << std::endl;
	}
	catch (std::string k) {
		std::cout << k << std::endl;
	}
}