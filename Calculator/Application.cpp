#include "Calc.h"

int main()
{
	Importer importer;
	Calculator calculator = Calculator(importer);
	std::string input;
	std::cout << "Enter input(enter ~ to escape):" << std::endl;
	std::getline(std::cin, input);
	while (input != "~") {
		try {
			std::cout << input << "=" << calculator.calculate(input) << std::endl;
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
		}
		std::cout << "Enter input(enter ~ to escape):" << std::endl;
		std::getline(std::cin, input);
	}

	return 0;
}