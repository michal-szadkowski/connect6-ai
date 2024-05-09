#ifndef CONNECT6_AI_INFOLOGGER_H
#define CONNECT6_AI_INFOLOGGER_H


#include <string>

class InfoLogger
{
public:
        virtual void WriteInfo(const std::string &prefix, const std::string &info) = 0;
    virtual ~InfoLogger() = default;
};


#endif // CONNECT6_AI_INFOLOGGER_H
