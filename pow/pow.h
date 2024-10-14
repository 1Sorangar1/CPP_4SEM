#pragma once

#ifdef POW_EXPORTS
#define POW_API __declspec(dllexport)
#else
#define POW_API __declspec(dllimport)
#endif

extern "C" {
    POW_API double binaryOperation(double base, double exponent);
}
