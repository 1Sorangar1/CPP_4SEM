#include "pow.h"
#include "pch.h"
#include <cmath>

extern "C" double binaryOperation(double base, double exponent) {
	return std::pow(base, exponent);
}