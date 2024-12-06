#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <map>
#include <vector>
#include <functional>

class Wrapper;

class Engine {
private:
    std::map<std::string, Wrapper*> command_map;

public:
    void register_command(Wrapper* wrapper, const std::string& command_name);

    std::vector<std::string> execute(const std::vector<std::string>& commands,
        const std::vector<std::map<std::string, std::string>>& args_list);
};

#endif 
