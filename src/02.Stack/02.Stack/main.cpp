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
	try {
		double res = Calculator::Calculate(postExp, head);
		std::cout << "Result: " << res << std::endl;

	}
	catch (std::string k) {
		std::cout << k << std::endl;
	}
	while (head->next != nullptr) {
		Calculator::Operand* tmp = head;
		while (tmp->next->next != nullptr) {
			tmp = tmp->next;
		}
		delete tmp->next;
		tmp->next = nullptr;
	}
	delete head;
}