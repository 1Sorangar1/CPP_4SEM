#pragma once
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include "Operations.h"
#include "Importer.h"

class Calculator
{
public:
	std::vector<std::string> parsing(const std::string& input_data);
	std::stack<double> numbers;
	Operations operations;
	Importer importer;
public:
	Calculator() = default;
	~Calculator() = default;
	double calculate(const std::string& expression);
	Calculator(Importer const& importer) : importer(importer), numbers(), operations(Operations::getOperations()) {};
};


std::string numberExtract(const std::string& input, int& index) {
	std::string number = "";
	int current = 0;
	while ((isdigit(input[index]) || input[index] == '.')) {
		if (input[index] == '.') { current++; }
		if (current == 2) { throw std::exception("Invalid number input"); }
		number += input[index];
		index++;
	}
	return number;
}


std::string operationExtract(const std::string& input, int& index) {
	std::string operation = "";
	while (isalpha(input[index]) || (input[index]) == '^') {
		operation += input[index];
		index++;
	}
	if ((input[index] != '(') && (input[index - 1] != '^')) {
		throw std::exception("Operation is provided in incorrect way");
		return "";
	}
	return operation;
}

