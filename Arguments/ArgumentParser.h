#ifndef CONNECT6_AI_ARGUMENTPARSER_H
#define CONNECT6_AI_ARGUMENTPARSER_H


#include <map>

class ArgumentParser {
private:
    std::map<std::string, std::string> arguments;
    void Add(std::vector<std::string_view>::const_iterator it);
public:
    ArgumentParser(int argc, const char **argv);

    bool TryGet(const std::string &name, std::string &out) const;
};


#endif //CONNECT6_AI_ARGUMENTPARSER_H
