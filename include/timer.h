#ifndef TIMER_H
#define TIMER_H

#include "timer_interface.h"

#include <condition_variable>
#include <mutex>
#include <thread>

class Timer : public TimerInterface
{
public:
    Timer() = default;
    ~Timer() override;
    void start() override;
    void stop() override;
    void configure(std::chrono::seconds, std::function<void()>) override;
    
private:
    std::function<void()> _cb {nullptr};
    std::chrono::seconds _timeout {0};
    
    static void timerThreadFunc(Timer *timer);
    
    void setSafeRunning(bool running);
    bool getSafeRunning();
    
    std::thread _thread;
    std::mutex _mutex;
    std::condition_variable _cv;
    bool _running {};
};

#endif // TIMER_H
