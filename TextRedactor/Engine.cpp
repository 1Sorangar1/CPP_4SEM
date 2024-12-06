#include "Engine.h"
#include "Wrapper.h"
#include <stdexcept>


void Engine::register_command(Wrapper* wrapper, const std::string& command_name) {
    command_map[command_name] = wrapper;
}

std::vector<std::string> Engine::execute(
    const std::vector<std::string>& command_names,
    const std::vector<std::map<std::string, std::string>>& args_list) {

    if (command_names.size() != args_list.size()) {
        throw std::invalid_argument("Mismatch between command names and argument lists.");
    }

    std::vector<std::string> results;

    for (size_t i = 0; i < command_names.size(); ++i) {
        const std::string& command_name = command_names[i];
        const std::map<std::string, std::string>& args = args_list[i];

        if (command_map.find(command_name) == command_map.end()) {
            throw std::runtime_error("Command not registered: " + command_name);
        }

        results.push_back(command_map[command_name]->execute(args));
    }

    return results;
}
