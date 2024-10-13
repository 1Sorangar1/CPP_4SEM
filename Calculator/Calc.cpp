#include "Calc.h"

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


std::vector<std::string> Calculator::parsing(const std::string& expression) {
    std::string expr = expression;
    std::vector<std::string> result;
    std::stack<std::string> stack;
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    for (int i = 0; i < expr.size();) {
        char cur_sym = expr[i];
        if (isdigit(cur_sym)) {
            result.push_back(numberExtract(expr, i));
        }
        else if (isalpha(cur_sym)) {
            std::string func = operationExtract(expr, i);
            if (func == "^") {
                func = "pow";
            }
            if (!operations.operationExistance(func)) {
                importer.loadDll(func, operations);
            }
            while (!stack.empty() && operations.priority(func) <= operations.priority(stack.top())) {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(func);
        }
        else if (cur_sym == '(') {
            stack.push("(");
            ++i;
        }
        else if (cur_sym == ')') {
            while (!stack.empty() && stack.top() != "(") {
                result.push_back(stack.top());
                stack.pop();
            }
            if (stack.empty() || stack.top() != "(") {
                throw std::exception("Incorrect bracket sequence");
            }
            stack.pop();
            ++i;
        }
        else if (operations.operationExistance({ cur_sym })) {
            std::string op(1, cur_sym);
            while (!stack.empty() && operations.priority(op) <= operations.priority(stack.top())) {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(op);
            ++i;
        }
        else {
            throw std::exception("Invalid symbol in expression");
        }
    }
    while (!stack.empty()) {
        if (stack.top() == "(") {
            throw std::exception("Incorrect bracket sequence");
        }
        result.push_back(stack.top());
        stack.pop();
    }

    return result;
}


double Calculator::calculate(const std::string& input) {
    std::vector<std::string> parsed_string = parsing(input);
    std::stack<double> stek;

    for (const auto& symbol : parsed_string) {
        if (isdigit(symbol[0])) {
            stek.push(std::stod(symbol));
        }
        else {
            double argument1 = stek.top();
            stek.pop();
            double result;
            if (operations.binaryExistance(symbol)) {
                if (stek.empty()) throw std::exception("Not enough arguments for binary operation");
                double argument2 = stek.top(); 
                stek.pop();
                result = operations.calculation(symbol, argument1, argument2);
            }
            else if (operations.unaryExistance(symbol)) {
                result = operations.calculation(symbol, argument1, 0);
            }
            else {
                throw std::exception("Unknown operation");
            }
            stek.push(result);
        }
    }
    return stek.top();
}
