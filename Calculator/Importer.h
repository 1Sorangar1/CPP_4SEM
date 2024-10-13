#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "Operations.h"
#include<Windows.h>

class Importer {
public:
    void loadDll(const std::string& dllFilename, Operations& operations);
};

