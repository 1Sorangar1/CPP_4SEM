#ifndef WRAPPER_H
#define WRAPPER_H

#include <string>
#include <map>
#include "Subject.h"

class Wrapper {
public:
    using MethodPointer = std::string(Subject::*)(const std::map<std::string, std::string>&);

    Wrapper(Subject* subject, MethodPointer method, const std::map<std::string, std::string>& default_args);
    std::string execute(const std::map<std::string, std::string>& args);

private:
    Subject* subject;
    MethodPointer method;
    std::map<std::string, std::string> default_args;
};

#endif
