#ifndef MOCK_TIMER_H
#define MOCK_TIMER_H

#include "timer_interface.h"

#include "gmock/gmock.h"

class MockTimer : public TimerInterface
{
public:
    MockTimer() = default;
    ~MockTimer() override {
        _onDelete();
    }
    
    void setOnDelete(std::function<void()> cb) {
         // helper for working with smart pointers
         _onDelete = cb;
    }
    
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, configure, (std::chrono::seconds, std::function<void()>), (override));
private:
    std::function<void()> _onDelete;
};

#endif // MOCK_TIMER_H
