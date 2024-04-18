#ifndef CONNECT6_AI_ARGUMENTPARSER_H
#define CONNECT6_AI_ARGUMENTPARSER_H


#include <map>

class ArgumentParser
{
private:
    std::map<std::string, std::string> arguments;
    void Add(std::vector<std::string_view>::const_iterator it);

public:
    /**
     * Creates parser with raw program arguments
     */
    ArgumentParser(int argc, const char** argv);


    /**
     * Reads argument by name
     * @tparam T Return type of argument
     * @param name Name of argument
     * @param out Argument value to write to, if there is no argument or parsing error occurs it is left unchanged
     * @return Whteather argument was read correctyl
     */
    template <typename T>
    bool TryGetT(const std::string& name, T& out) const;
};

template <typename T>
bool ArgumentParser::TryGetT(const std::string& name, T& out) const
{
    if (arguments.contains(name))
    {
        try
        {
            out = static_cast<T>(arguments.at(name));
            return true;
        }
        catch (std::exception& ex) {}
    }
    return false;
}

template <>
inline bool ArgumentParser::TryGetT<int>(const std::string& name, int& out) const
{
    if (arguments.contains(name))
    {
        try
        {
            auto tmp = std::stoi(arguments.at(name));
            out = tmp;
            return true;
        }
        catch (std::exception& ex) {}
    }
    return false;
}

template <>
inline bool ArgumentParser::TryGetT<double>(const std::string& name, double& out) const
{
    if (arguments.contains(name))
    {
        try
        {
            auto tmp = std::stod(arguments.at(name));
            out = tmp;
            return true;
        }
        catch (std::exception& ex) {}
    }
    return false;
}

#endif //CONNECT6_AI_ARGUMENTPARSER_H
