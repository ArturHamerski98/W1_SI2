#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <string>


int checkCharacter(char c) {

	if (c == '+')
		return 1;
	else if (c == '-')
		return 1;
	else if (c == '*')
		return 2;
	else if (c == '/')
		return 2;
	else if (c == '^')
		return 3;
	else if (c == '(')
		return 0;
	else if (c == ')')
		return 5;
	else if (c == 'R') {
		return 6;
	}
	else
		return -1;
}
double calculatingONP(std::vector<std::string> expression) {
	std::stack<double> myStack;

	for (int i = 0; i < expression.size(); i++) {

		
		

		if (expression[i] == "+") {
			double a = myStack.top();
			myStack.pop();
			double b = myStack.top();
			myStack.pop();
			myStack.push(a + b);
		}
		else if (expression[i] == "-") {
			double a = myStack.top();
			myStack.pop();
			if (myStack.empty()) {
				myStack.push(0 - a);
			}
			else {
				double b = myStack.top();
				myStack.pop();
				myStack.push(b - a);
			}
		}
		else if (expression[i] == "*") {
			double a = myStack.top();
			myStack.pop();
			double b = myStack.top();
			myStack.pop();
			myStack.push(a * b);
		}
		else if (expression[i] == "/") {
			double a = myStack.top();
			myStack.pop();
			double b = myStack.top();
			myStack.pop();
			myStack.push(b / a);
		}
		else if (expression[i] == "R") {
			double a = myStack.top();
			myStack.pop();
			double b = myStack.top();
			myStack.pop();
			myStack.push(pow(a, 1 / b));
		}
		else if (expression[i] == "^") {
			double a = myStack.top();
			myStack.pop();
			double b = myStack.top();
			myStack.pop();
			myStack.push(pow(b, a));
		}
		else {
			double a = std::stod(expression[i]);
			myStack.push(a);
		}
	}
	return myStack.top();
}

std::vector<std::string> stringToVector(std::string expression) {

	std::vector<std::string> vec;
	std::string temp{};
	bool isLastCharacterOperator = true;
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] == ' ') {
			continue;
		}
		else if (checkCharacter(expression[i]) >= 0) {

			if (isLastCharacterOperator) {

				if (expression[i] == '-' && !vec.empty() && vec.back()[0] != '(' && vec.back()[0] != ')') {
					temp += expression[i];
				}
				else {
					std::string s(1, expression[i]);
					vec.push_back(s);
				}
			}
			else {
				vec.push_back(temp);
				temp.clear();
				std::string s(1, expression[i]);
				vec.push_back(s);

			}
			isLastCharacterOperator = true;

		}
		else {
			temp += expression[i];
			isLastCharacterOperator = false;
		}
	}
	vec.push_back(temp);
	return vec;
}

std::vector<std::string> toONP(std::vector<std::string> expression) {
	std::vector<std::string> output;
	std::stack<std::string> myStack;
	char last{};
	for (auto i : expression) {
		if (i != "") {
			last = i[i.length() - 1];
		}
		if (i == "") {
			continue;
		}

		else if (std::isdigit(last)) {
			output.push_back(i);
		}
		else if (myStack.empty()) {
			myStack.push(i);
		}
		else if (checkCharacter(i[0]) == 0) {
			myStack.push(i);
		}
		
		else if (checkCharacter(i[0]) == 5) {
			while (myStack.top()[0] != '(') {
				output.push_back(myStack.top());
				myStack.pop();
			}
			myStack.pop();
		}
		else if (checkCharacter(i[0]) <= checkCharacter(myStack.top()[0])) {
			output.push_back(myStack.top());
			myStack.pop();
			myStack.push(i);
		}
		else {
			myStack.push(i);
		}
	}


	while (!myStack.empty()) {
		output.push_back(myStack.top());
		myStack.pop();
	}


	return output;
}
int main() {
	std::string egzample1 = "5*((3 - 7)*2 - 3*(5 + 1)) - 3";
	std::string egzample2 = "((2^3)-1*5)R64";

	std::cout << "Egzample1: " << egzample1 << "\n" << "Transform to ONP:";
	std::vector<std::string> vecEgz1 = toONP(stringToVector(egzample1));
	for (auto v : vecEgz1)
	{
		std::cout << v<<" ";
	}
	std::cout << "\nResult:"<<calculatingONP(vecEgz1);
	std::cout << "\n---------------------\n";

	std::cout << "Egzample2: " << egzample2 << "\n" << "Transform to ONP:";
	std::vector<std::string> vecEgz2 = toONP(stringToVector(egzample2));
	for (auto v : vecEgz2)
	{
		std::cout << v<<" ";
	}
	std::cout << "\nResult:" << calculatingONP(vecEgz2);
	std::cout << "\n---------------------\n";
	
	while (true)
	{
		std::string equation;
		std::cout << "Write your own equation:";
		std::cin >> equation;
		std::cout << "Your equation: " << equation << "\n" << "Transform to ONP:";
		std::vector<std::string> vecEquation = toONP(stringToVector(equation));
		for (auto v : vecEquation)
		{
			std::cout << v << " ";
		}
		std::cout << "\nResult:" << calculatingONP(vecEquation);
		std::cout << "\n---------------------\n";
		system("pause");

	}
	

	return 0;
}