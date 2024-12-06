#include "Importer.h"
#include <fstream>

void Importer::loadDll(const std::string& dllFilename, Operations& operations) {
    std::string path = "./plugins\\" + dllFilename;
    //std::ifstream file(path);
    //if (file) {
    //    throw std::exception(("DLL not found: " + path).c_str());
    //}

    HMODULE hModule = LoadLibraryA(path.c_str());

    if (hModule) {
        std::string op = dllFilename.substr(0, dllFilename.find(".dll"));

        unaryOperation unop = (unaryOperation)GetProcAddress(hModule, "unaryOperation");

        if (!unop) {
            binaryOperation biop = (binaryOperation)GetProcAddress(hModule, "binaryOperation");
            if (!biop) throw std::exception(("Failed to load operation from: " + dllFilename).c_str());
            operations.addBinaryOperation(op, biop, 4);
            std::cout << op + " was loaded" << std::endl;
        }
        else {
            operations.addUnaryOperation(op, unop, 3);
            std::cout << op + " was loaded" << std::endl;
        }
    }
    else {
        throw std::exception(("Failed to load DLL: " + dllFilename + "\n").c_str());
    }
}
