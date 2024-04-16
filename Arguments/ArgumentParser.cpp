#include <string>
#include <vector>
#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(const int argc, const char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);
    for (auto item = args.begin(); item < args.end(); item++) { Add(item); }
}

void ArgumentParser::Add(std::vector<std::string_view>::const_iterator it)
{
    std::string name, value;
    auto split = it->find('=');
    if (split != std::string_view::npos)
    {
        name = it->substr(0, split);
        value = it->substr(split + 1);
    }
    else
    {
        name = *it;
        it++;
        value = *it;
    }
    arguments[name] = value;
}

