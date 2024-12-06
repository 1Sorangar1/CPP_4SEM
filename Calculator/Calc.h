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


