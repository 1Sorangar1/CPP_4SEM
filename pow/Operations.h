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
    static Operations& getOperations();

};

