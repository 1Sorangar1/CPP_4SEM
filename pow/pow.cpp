#include "pow.h"
#include "pch.h"
#include <cmath>

extern "C" {
    POW_API double binaryOperation(double base, double exponent) {
        return std::pow(base, exponent);
    }
}