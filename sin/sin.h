#pragma once

#ifdef SIN_EXPORTS
#define SIN_API __declspec(dllexport)
#else
#define SIN_API __declspec(dllimport)
#endif

extern "C" SIN_API double unaryOperation(double value);