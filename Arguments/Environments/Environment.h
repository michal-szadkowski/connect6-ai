#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


class Environment
{
protected:
    ~Environment() = default;

public:
    virtual void Run() = 0;
};


#endif //ENVIRONMENT_H
