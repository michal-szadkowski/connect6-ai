#ifndef CONNECT6_AI_ARGUMENTPARSER_H
#define CONNECT6_AI_ARGUMENTPARSER_H


#include <map>

class ArgumentParser
{
private:
    std::map<std::string, std::string> arguments;
    void Add(std::vector<std::string_view>::const_iterator it);

public:
    ArgumentParser(int argc, const char **argv);
    template <typename T>
    bool TryGetT(const std::string &name, T &out) const;
};

template <typename T>
bool ArgumentParser::TryGetT(const std::string &name, T &out) const
{
    if (arguments.contains(name))
    {
        try
        {
            out = static_cast<T>(arguments.at(name));
            return true;
        }
        catch (std::exception &ex)
        {}
    }
    return false;
}

template <>
inline bool ArgumentParser::TryGetT<int>(const std::string &name, int &out) const
{
    if (arguments.contains(name))
    {
        try
        {
            auto tmp = std::stoi(arguments.at(name));
            out = tmp;
            return true;
        }
        catch (std::exception &ex)
        {}
    }
    return false;
}

template <>
inline bool ArgumentParser::TryGetT<double>(const std::string &name, double &out) const
{
    if (arguments.contains(name))
    {
        try
        {
            auto tmp = std::stod(arguments.at(name));
            out = tmp;
            return true;
        }
        catch (std::exception &ex)
        {}
    }
    return false;
}

#endif // CONNECT6_AI_ARGUMENTPARSER_H
