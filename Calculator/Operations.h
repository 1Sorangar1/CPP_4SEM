#pragma once
#include <map>
#include <string>
#include <iostream>

using unaryOperation = double(*)(double);
using binaryOperation = double(*)(double, double);

class Operations {
private:
    std::map<std::string, binaryOperation> binary_operations;
    std::map<std::string, unaryOperation> unary_operations;
    std::map<std::string, unsigned short> operation_priorities;
public:
	Operations();
	~Operations() = default;
    void addBinaryOperation(const std::string& dll_filename, binaryOperation& operation, unsigned short priority);
    void addUnaryOperation(const std::string& dll_filename, unaryOperation& operation, unsigned short priority);
    int priority(const std::string& operation);
    bool binaryExistance(const std::string& operation);
    bool unaryExistance(const std::string& operation);
	double calculation(const std::string& operation, double a, double b);
	bool operationExistance(const std::string& name);
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

bool Operations::unaryExistance(const std::string& operation) {
	return binary_operations.find(operation) != binary_operations.end();
}

bool Operations::binaryExistance(const std::string& operation) {
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

