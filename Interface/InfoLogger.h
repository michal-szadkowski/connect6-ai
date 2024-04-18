#ifndef CONNECT6_AI_INFOLOGGER_H
#define CONNECT6_AI_INFOLOGGER_H


#include <string>

/**
 * Interface for players to write information
 */
class InfoLogger
{
public:
    /**
     * Logs iformation from player
     * @param prefix Name of player, put in square braces
     * @param info Message to log
     */
    virtual void WriteInfo(const std::string &prefix, const std::string &info) = 0;
    virtual ~InfoLogger() = default;
};


#endif // CONNECT6_AI_INFOLOGGER_H
