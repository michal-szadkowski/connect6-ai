#ifndef CONNECT6_AI_INFOLOGGER_H
#define CONNECT6_AI_INFOLOGGER_H


#include <string>

class InfoLogger {
public:
    virtual void WriteInfo(__attribute__((unused)) const std::string &info) {};
    virtual ~InfoLogger() = default;
};


#endif //CONNECT6_AI_INFOLOGGER_H

