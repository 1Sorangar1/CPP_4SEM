#include "Calc.h";

Operations::Operations() {
	binary_operations["+"] = [](double a, double b)->double {return a + b; };
	binary_operations["-"] = [](double a, double b)->double {return a - b; };
	binary_operations["*"] = [](double a, double b)->double {return a * b; };
	binary_operations["/"] = [](double a, double b)->double {
		if (b != 0) return a / b;
		throw std::exception("Division by zero!"); 
	};

	operation_priorities["*"] = 2;
	operation_priorities["/"] = 2;
	operation_priorities["+"] = 1;
	operation_priorities["-"] = 1;
};