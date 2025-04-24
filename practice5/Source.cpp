#include <iostream>
#include <queue>
#include <functional>
#include <string>
#include <cmath>

template <typename T>
class queuef {
private:
    std::queue<std::function<T(T)>> functions;
public:
    template <typename... Funcs>
    void create(Funcs... funcs) {
        (functions.push(funcs), ...);
    }

    T run(T input) {
        T result = input;
        std::queue<std::function<T(T)>> tempQueue = functions;
        while (!tempQueue.empty()) {
            auto func = tempQueue.front();
            result = func(result);
            tempQueue.pop();
        }
        return result;
    }
};

int main() {
    queuef<double> doubleQueue;
    doubleQueue.create(
        [](double x) { return x + 2.0; },
        [](double x) { return x * 3.0; },
        [](double x) { return x / 6.0; } 
    );

    double result = doubleQueue.run(4.0);

    std::cout << "double input: " << "4.0" << std::endl;
    std::cout << "double output: " << result << std::endl;


    queuef<std::string> stringQueue;
    stringQueue.create(
        [](const std::string& s) { return s + " qwe"; },
        [](const std::string& s) {
            std::string upper = s;
            for (char& c : upper) c = std::toupper(c);
            return upper;
        },
        [](const std::string& s) { return "rty, " + s; }
        );

    std::string stringResult = stringQueue.run("test");
    std::cout << "string input: " << "test" << std::endl;
    std::cout << "string output: " << stringResult << std::endl;

    return 0;
}
