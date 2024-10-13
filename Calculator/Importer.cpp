#include "Importer.h"

void Importer::loadDll(const std::string& dllFilename, Operations& operations) {
	std::string path = "./plugins\\" + dllFilename;

	HMODULE hModule = LoadLibraryA(path.c_str());

	if (hModule) {
		std::string op = dllFilename.substr(0, dllFilename.find(".dll"));

		unaryOperation unop = (unaryOperation)GetProcAddress(hModule, "unaryOperation");

		if (!unop) {
			binaryOperation biop = (binaryOperation)GetProcAddress(hModule, "binaryOperation");
			if (!biop) throw std::exception();
			operations.addBinaryOperation(op, biop, 4);
			//std::cout << operation + " was loaded";
		}
		else {
			operations.addUnaryOperation(op, unop, 3);
			//std::cout << operation + " was loaded";
		}
	}
	else {
		throw std::exception(("Failed to load: " + dllFilename + "\n").c_str());
		std::cout << "\n";
	}
}