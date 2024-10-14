#include "Calc.h"

int main()
{
	Importer importer;
	Calculator calculator = Calculator(importer);

	try {
		calculator.importer.loadDll("sin.dll", calculator.operations);
		calculator.importer.loadDll("pow.dll", calculator.operations);
		std::cout << "Plugins loaded successfully." << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << "Error loading plugins: " << ex.what() << std::endl;
		return -1; // Завершаем программу, если не удалось загрузить плагины
	}

	std::string input;
	std::cout << "Enter expession or ~ to exit:" << std::endl;
	std::getline(std::cin, input);
	while (input != "~") {
		try {
			std::cout << input << "=" << calculator.calculate(input) << std::endl;
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
		}
		std::cout << "Enter expession or ~ to exit:" << std::endl;
		std::getline(std::cin, input);
	}

	return 0;
}