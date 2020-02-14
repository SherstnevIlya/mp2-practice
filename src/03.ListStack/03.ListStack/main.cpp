#include "Calculator.h"
#include <iostream>
#include <string>

void testList() {
	TList<int, std::string> test;
	std::string ExamsMood[5] = {"denial", "anger", "bargaining", "depression", "acceptance"};

	std::cout << "Insert <" << ExamsMood[2] << "> at the beginning" << std::endl;
	test.InsertBegin(2, &ExamsMood[2]);
	std::cout << test << std::endl;

	std::cout << "Insert <" << ExamsMood[0] << "> before" << std::endl;
	test.InsertBefore(2, 0, &ExamsMood[0]);
	std::cout << test << std::endl;

	std::cout << "Insert <" << ExamsMood[1] << "> after" << std::endl;
	test.InsertAfter(0, 1, &ExamsMood[1]);
	std::cout << test << std::endl;

	std::cout << "Insert <" << ExamsMood[4] << "> at the end" << std::endl;
	test.InsertEnd(4, &ExamsMood[4]);
	std::cout << test << std::endl;

	std::cout << "Insert <" << ExamsMood[3] << "> before" << std::endl;
	test.InsertBefore(4, 3, &ExamsMood[3]);
	std::cout << test << std::endl;

	std::cout << "Remove element with key 3" << std::endl;
	test.Remove(3);
	std::cout << test << std::endl;

	std::cout << "Remove element with key 0" << std::endl;
	test.Remove(0);
	std::cout << test << std::endl;

	std::cout << "Testing copy constructor" << std::endl;
	std::cout << TList<int, std::string>(test) << std::endl;

	std::cout << "Testing node->list constructor" << std::endl;
	std::cout << TList<int, std::string>(&TNode<int, std::string>(6, &ExamsMood[0])) << std::endl;
	
	try {
		std::cout << "Insert <" << ExamsMood[0] << "> before wrong key" << std::endl;
		test.InsertBefore(15, 0, &ExamsMood[0]);
		std::cout << test << std::endl;
	}
	catch (std::string k) {
		std::cout << k << std::endl;
	}

	try {
		std::cout << "Insert <" << ExamsMood[0] << "> after wrong key" << std::endl;
		test.InsertAfter(15, 0, &ExamsMood[0]);
		std::cout << test << std::endl;
	}
	catch (std::string k) {
		std::cout << k << std::endl;
	}

	try {
		std::cout << "Remove element with wrong key" << std::endl;
		test.Remove(15);
		std::cout << test << std::endl;
	}
	catch (std::string k) {
		std::cout << k << std::endl;
	}
}

void testStack() {
	std::cout << "For using array stack type '0', for using list stack type '1': ";
	int i;
	std::cin >> i;
	std::cin.ignore();
	if (i == 0) 
		std::cout << "Array stack has been selected" << std::endl;
	else
		std::cout << "List stack has been selected" << std::endl;
	std::string Exp, postExp;
	double res;
	Calculator::Operand* head = nullptr;
	std::cout << "Enter expression: ";
	std::getline(std::cin, Exp);
	try {
		Calculator kek(i);
		postExp = kek.ToPostfixForm(Exp);
		std::cout << "Postfix form: " << postExp << std::endl;
		kek.Fill(head, postExp);
		res = kek.Calculate(postExp, head);
		std::cout << "Result: " << res;
	}
	catch (std::string k) {
		std::cout << k << std::endl;
		return;
	}
}

void main() {
	std::cout << "Testing list: " << std::endl;
	testList();
	std::cout << "Testing stack: " << std::endl;
	testStack();
	int k;
	std::cin >> k;
}