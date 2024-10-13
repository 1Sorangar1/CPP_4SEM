#pragma once
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include "Operations.h"

class Calculator
{
	std::vector<std::string> parsing(const std::string& input_data);
	std::stack<double> numbers;
	Operations operations;
public:
	Calculator() = default;
	~Calculator() = default;
	double calculate(const std::string& expression);
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


