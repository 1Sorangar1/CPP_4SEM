#include "Calc.h";

Operations::Operations() {
	binary_operations["+"] = [](double a, double b)->double {return a + b; };
	binary_operations["-"] = [](double a, double b)->double {return b-a; };
	binary_operations["*"] = [](double a, double b)->double {return a * b; };
	binary_operations["/"] = [](double a, double b)->double {
		if (b != 0) return b/a;
		throw std::exception("Division by zero!"); 
	};

	operation_priorities["*"] = 2;
	operation_priorities["/"] = 2;
	operation_priorities["+"] = 1;
	operation_priorities["-"] = 1;
};

void Operations::addBinaryOperation(const std::string& dll_filename, binaryOperation& operation, unsigned short priority) {
	binary_operations[dll_filename] = operation;
	operation_priorities[dll_filename] = priority;
}

void Operations::addUnaryOperation(const std::string& dll_filename, unaryOperation& operation, unsigned short priority) {
	unary_operations[dll_filename] = operation;
	operation_priorities[dll_filename] = priority;
}

int Operations::priority(const std::string& operation) {
	return operation_priorities[operation];
}

bool Operations::binaryExistance(const std::string& operation) {
	return binary_operations.find(operation) != binary_operations.end();
}

bool Operations::unaryExistance(const std::string& operation) {
	return unary_operations.find(operation) != unary_operations.end();
}

bool Operations::operationExistance(const std::string& name) {
	return unaryExistance(name) || binaryExistance(name);
}

double Operations::calculation(const std::string& operation, double a, double b) {
	if (unaryExistance(operation)) { return unary_operations[operation](a); }
	if (binaryExistance(operation)) { return binary_operations[operation](a, b); }
	throw std::exception("Operation not found");
	return 0;
};

Operations& Operations::getOperations() {
	static Operations instance;
	return instance;
};
