#include "Wrapper.h"
#include "Subject.h"

Wrapper::Wrapper(Subject* subject, MethodPointer method, const std::map<std::string, std::string>& default_args)
    : subject(subject), method(method), default_args(default_args) {
}

std::string Wrapper::execute(const std::map<std::string, std::string>& args) {
    auto merged_args = default_args;

    for (auto it = args.begin(); it != args.end(); ++it) {
        merged_args[it->first] = it->second;
    }

    return (subject->*method)(merged_args);
}

