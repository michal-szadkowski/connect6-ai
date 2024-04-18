#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


/**
 * Abstract class being strategy of main program
 */
class Environment
{
protected:
    ~Environment() = default;

public:
    /**
     * Starts the environment
     */
    virtual void Run() = 0;
};


#endif //ENVIRONMENT_H
