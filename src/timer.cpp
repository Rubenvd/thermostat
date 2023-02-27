#include <timer.h>

#include <stdio.h>

Timer::~Timer()
{
    if (getSafeRunning()) {
        stop();
    }
}

void Timer::start()
{
    if (!getSafeRunning()) {
        setSafeRunning(true);
        _thread = std::thread(timerThreadFunc, this);
    }
}

void Timer::stop()
{
    if (getSafeRunning()) {
        setSafeRunning(false);
        _thread.join();
    }
}

void Timer::configure(std::chrono::seconds timeout, std::function<void()> cb)
{
    std::lock_guard<std::mutex> lk(_mutex);
    _cb = cb;
    _timeout = timeout;
}

void Timer::timerThreadFunc(Timer *timer)
{
    while (timer->getSafeRunning()) {
        timer->_cb();
        std::unique_lock<std::mutex> lk(timer->_mutex);
        timer->_cv.wait_for(lk, timer->_timeout);
    }
}

void Timer::setSafeRunning(bool running)
{
    {
        std::lock_guard<std::mutex> lk(_mutex);
        _running = running;
    }
    _cv.notify_all();
}

bool Timer::getSafeRunning()
{
    std::lock_guard<std::mutex> lk(_mutex);
    return _running;
}
