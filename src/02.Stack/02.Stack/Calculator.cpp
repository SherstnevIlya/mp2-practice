#include "Calculator.h"

void Calculator::AddUnique(const std::string& op, Calculator::Operand*& head) {
	if (!head) {
		head = new Operand;
		head->name = op;
		head->value = 0.0;
		head->next = nullptr;
	}
	else if(!IsVarExist(op, head)){
		Operand* tmp = head;
		while (tmp->next != nullptr)
			tmp = tmp->next;
		tmp->next = new Operand;
		tmp->next->name = op;
		tmp->next->value = 0.0;
		tmp->next->next = nullptr;
	}
}

bool Calculator::IsVarExist(const std::string& k, Calculator::Operand* tmp) {
	while (tmp != nullptr) {
		if (tmp->name == k) 
			return true;
		tmp = tmp->next;
	}
	return false;
}

void Calculator::Fill(Calculator::Operand*& head, const std::string& postfixForm) {
	std::string name = "";
	char lastSymbol = '(';
	TypeSymbol type, ltype;
	for (size_t i = 0; i < postfixForm.length(); i++) {
		type = GetType(postfixForm[i]);
		ltype = GetType(lastSymbol);
		if (type == TypeSymbol::operand || type == TypeSymbol::number) {
			name.append(1, postfixForm[i]);
		}
		else if (type == TypeSymbol::space && (ltype == TypeSymbol::operand || ltype == TypeSymbol::number)) {
			AddUnique(name, head);
			name.clear();
		}
		lastSymbol = postfixForm[i];
	}
	Calculator::Operand* tmp = head;
	while (tmp != nullptr) {
		if (!Calculator::IsNumber(tmp)) {
			std::cout << tmp->name << " = ";
			std::cin >> tmp->value;
		}
		tmp = tmp->next;
	}
}

double Calculator::GetValue(const std::string& wtf, Calculator::Operand* head) {
	Operand* tmp = head;
	while (tmp != nullptr) {
		if (tmp->name == wtf)
			return tmp->value;
		tmp = tmp->next;
	}
	throw (std::string)"Operand doesn`t exist";
}

bool Calculator::IsNumber(Calculator::Operand* op) {
	if ((!op->name.empty()) && (op->name.find_first_not_of("0123456789.") == op->name.npos)) {
		op->value = atof((op->name).c_str());
		return true;
	}
	else return false;
}

Calculator::TypeSymbol Calculator::GetType(char temp)
{
	if ((temp == '*') || (temp == '/') || (temp == '+') || (temp == '-'))
		return TypeSymbol::operation;
	if (temp == ')')
		return TypeSymbol::closingBracket;
	if (temp == '(')
		return TypeSymbol::openingBracket;
	if (isalpha(temp))
		return TypeSymbol::operand;
	if ((temp == '0') || (temp == '1') || (temp == '2') || (temp == '3') || (temp == '4') || (temp == '5') || (temp == '6') || (temp == '7') || (temp == '8') || (temp == '9') || (temp == '.'))
		return TypeSymbol::number;
	if (temp == ' ')
		return TypeSymbol::space;
	else
		return TypeSymbol::invalid;
}

int Calculator::PriorityOperations(const char op)
{
	if ((op == '*') || (op == '/')) return 3;
	if ((op == '+') || (op == '-')) return 2;
	if (op == ')') return 1;
	return 0;
}

std::string Calculator::ToPostfixForm(const std::string& expression)
{
	std::string buffer;
	int lengthOfExpression = expression.length();
	int numberOfOperators = 0, numberOfOperands = 0, numberOfLeftBrackets = 0, numberOfRightBrackets = 0;
	TypeSymbol type, ltype;
	char lastSymbol = 0;
	std::string postfixForm = "";

	TStack<char> operators(lengthOfExpression);
	TStack<std::string> operands(lengthOfExpression);

	for (int i = 0; i < lengthOfExpression; i++)
	{
		type = GetType(expression[i]);
		ltype = GetType(lastSymbol);
		if (buffer.length() != 0)
		{
			if (type == TypeSymbol::operation || type == TypeSymbol::openingBracket || type == TypeSymbol::closingBracket || type == TypeSymbol::space)
			{
				numberOfOperands++;
				operands.Push(buffer);
				buffer.clear();
			}
		}

		if (type == TypeSymbol::space);
		else if (type == TypeSymbol::operand || type == TypeSymbol::number)
		{
			if (numberOfOperands == (numberOfOperators + 1))
			{
				throw (std::string)"Extra operand";
			}

			buffer.push_back(expression[i]);
			if (i == (lengthOfExpression - 1))
			{
				numberOfOperands++;
				operands.Push(buffer);
				buffer.clear();
			}
		}
		else if (type == TypeSymbol::openingBracket)
		{
			if (ltype == TypeSymbol::operand || ltype == TypeSymbol::number)
			{
				throw (std::string)"No operation between operand and opening bracket";
			}
			numberOfLeftBrackets++;
			operators.Push(expression[i]);
		}
		else if (type == TypeSymbol::closingBracket)
		{
			if (ltype == TypeSymbol::operation || ltype == TypeSymbol::openingBracket) {
				throw (std::string)"Right bracket after operation or opening bracket";
			}
			if (numberOfRightBrackets >= numberOfLeftBrackets) {
				throw (std::string)"Extra right bracket";
			}
			numberOfRightBrackets++;
			while (operators.Top() != '(')
			{
				std::string tmp;
				try
				{
					tmp.push_back(operators.Top());
					operators.Pop();
					operands.Push(tmp);
				}
				catch (std::string k)
				{
					throw k;
				}
			}
			operators.Pop();
		}
		else if (operators.Empty())
		{
			if (lastSymbol == 0)
			{
				throw (std::string)"Extra operator";
			}
			operators.Push(expression[i]);
			numberOfOperators++;
		}
		else if (PriorityOperations(expression[i]) > PriorityOperations(operators.Top()))
		{
			operators.Push(expression[i]);
			numberOfOperators++;
		}
		else
		{
			while ((!operators.Empty()) && (operators.Top() != '(')
				&& (PriorityOperations(expression[i]) <= PriorityOperations(operators.Top())))
			{
				std::string tmp;
				tmp.push_back(operators.Top());
				operators.Pop();
				operands.Push(tmp);
			}
			operators.Push(expression[i]);
			numberOfOperators++;
		}

		if (type != TypeSymbol::space)
			lastSymbol = expression[i];
	}

	if (numberOfOperands != numberOfOperators + 1)
	{
		throw (std::string)"Wrong amount of operands/operators";
	}
	if (numberOfLeftBrackets != numberOfRightBrackets)
	{
		throw (std::string)"Wrong amount of brackets";
	}

	while (!operators.Empty())
	{
		std::string tmp;
		tmp.push_back(operators.Top());
		operators.Pop();
		operands.Push(tmp);
	}

	TStack<std::string> reverseStackOfOperands(lengthOfExpression);
	for (; !operands.Empty(); operands.Pop())
		reverseStackOfOperands.Push(operands.Top());

	int startPosition = 0;
	while (!reverseStackOfOperands.Empty())
	{
		startPosition = postfixForm.length();
		postfixForm.insert(startPosition, reverseStackOfOperands.Top());
		reverseStackOfOperands.Pop();
		buffer = ' ';
		postfixForm.insert(postfixForm.length(), buffer);
	}
	return postfixForm;
}

double Calculator::Calculate(const std::string& postfixForm, Calculator::Operand*& head)
{
	size_t sizeForm = postfixForm.size();
	TStack<double> calc(sizeForm);
	double res = 0.0;
	std::string Name;
	char lastSymbol = '(';
	for (size_t i = 0; i < sizeForm; i++) {
		TypeSymbol type = GetType(postfixForm[i]);
		TypeSymbol ltype = GetType(lastSymbol);
		if (type == TypeSymbol::operand || type == TypeSymbol::number)
			Name.append(1, postfixForm[i]);
		else if (type == TypeSymbol::operation) {
			double a, b;
			try {
				b = calc.Top();
				calc.Pop();
				a = calc.Top();
				calc.Pop();
			}
			catch (std::string k) {
				throw (std::string)"Wrong postfix form: " + k;
			}
			switch (postfixForm[i]) {
			case '+':
				calc.Push(a + b);
				break;
			case '-':
				calc.Push(a - b);
				break;
			case '*':
				calc.Push(a * b);
				break;
			case '/':
				if (b == 0)
					throw (std::string)"Division by zero";
				calc.Push(a / b);
				break;
			default:
				throw (std::string)"Wrong operation";
				break;
			}
		}
		else if ((type == TypeSymbol::space && ltype == TypeSymbol::operand) || (type == TypeSymbol::space && ltype == TypeSymbol::number)) {
			try { 
				calc.Push(GetValue(Name, head)); 
			}
			catch (std::string k) {
				std::cout << k << std::endl;
			}
			Name.clear();
		}
		if(type != TypeSymbol::space)
			lastSymbol = postfixForm[i];
	}
	try {
		res = calc.Top();
		calc.Pop();
	}
	catch (std::string k) {
		throw k;
	}
	while (head->next != nullptr) {
		Operand* tmp = head;
		while (tmp->next->next != nullptr) {
			tmp = tmp->next;
		}
		delete tmp->next;
		tmp->next = nullptr;
	}
	delete head;
	if (calc.Empty())
		return res;
	else
		throw (std::string)"Stack isn`t empty after calculating";
}