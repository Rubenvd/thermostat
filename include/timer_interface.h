#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include <chrono>
#include <functional>

class TimerInterface
{
public:
    TimerInterface() = default;
    virtual ~TimerInterface() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void configure(std::chrono::seconds, std::function<void()>) = 0;
};

#endif // TIMER_INTERFACE_H
