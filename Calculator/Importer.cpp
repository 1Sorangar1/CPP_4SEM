#include "Importer.h"
#include <filesystem>


void Importer::loadDll(const std::string& dllFilename, Operations& operations) {
    std::string path = "./plugins/" + dllFilename;

    //HMODULE hModule = LoadLibraryA(path.c_str());
    HMODULE load = LoadLibrary(L"pow.dll");

    if (load) {
        std::string op = dllFilename.substr(0, dllFilename.find(".dll"));
        unaryOperation unop = (unaryOperation)GetProcAddress(load, "unaryOperation");

        if (!unop) {
            binaryOperation biop = (binaryOperation)GetProcAddress(load, "binaryOperation");
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



//void Importer::loadDll(const std::string& dllFilename, Operations& operations) {
//    try {
//        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
//            if (entry.path().extension() == ".dll") {
//                HMODULE hModule = LoadLibraryA(entry.path().string().c_str());
//                if (!hModule) {
//                    throw std::runtime_error("Failed to load DLL: " + entry.path().string());
//                }
//
//                //loaded_modules.push_back(hModule);
//                std::cout << "DLL " << entry.path() << " loaded!" << std::endl;
//
//                std::string function_suffix = entry.path().stem().string().substr(8);
//                std::string full_function_name = "calc_" + function_suffix;
//
//                FARPROC func = GetProcAddress(hModule, full_function_name.c_str());
//                if (func) {
//                    function_map[function_suffix] = func;
//                    std::cout << "Function " << full_function_name << " loaded from " << entry.path() << std::endl;
//                }
//            }
//        }
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error while loading plugins: " << e.what() << std::endl;
//        abort();
//    }
//}
