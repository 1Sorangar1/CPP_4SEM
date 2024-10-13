#include "Calc.h"


std::vector<std::string> Calculator::parsing(const std::string& input_data) {
    std::string expression = input_data;
    std::vector<std::string> result;
    std::stack<std::string> stek;
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
    for (int i = 0; i < expression.size();) {
        char current_symbol = expression[i];
        if (isdigit(current_symbol)) {
            result.push_back(numberExtract(expression, i));
        }
        else if (current_symbol == '(') {
            stek.push("(");
            ++i;
        }
        else if (current_symbol == ')') {
            while (!stek.empty() && stek.top() != "(") {
                result.push_back(stek.top());
                stek.pop();
            }
            if (stek.empty() || stek.top() != "(") {
                throw std::exception("Incorrect brackets sequence");
            }
            stek.pop();
            ++i;
        }
        else if (operations.operationExistance({ current_symbol })) {
            std::string op(1, current_symbol);
            while (!stek.empty() && operations.priority(op) <= operations.priority(stek.top())) {
                result.push_back(stek.top());
                stek.pop();
            }
            stek.push(op);
            ++i;
        }
        else {
            throw std::exception("Invalid symbol in expression");
        }
    }
    while (!stek.empty()) {
        if (stek.top() == "(") {
            throw std::exception("Mismatched parentheses");
        }
        result.push_back(stek.top());
        stek.pop();
    }

    return result;
}


double Calculator::calculate(const std::string& input_data) {
    std::vector<std::string> parsed_string = parsing(input_data);
    std::stack<double> result;
    double argument1 = 0, argument2 = 0;

    for (auto& element : parsed_string) {
        if (isdigit(element[0])) {
            result.push(std::stod(element));
        }
        else {
            if (result.empty()) { throw std::exception("Operation is in lack of argumrnts"); }
            argument1 = result.top();
            result.pop();

            if (operations.binaryExistance(element)) {
                if (result.empty()) { throw std::exception("Operation is in lack of argumrnts"); }
                argument2 = result.top();
                result.pop();
                result.push(operations.calculation(element, argument2, argument1));
            }
        }
    }
    return result.top();
}
