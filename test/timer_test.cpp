#include <gtest/gtest.h>

#include "timer.h"

TEST(TimerTest, Timeout) {
    Timer t;
    uint32_t counter = 0;
    t.configure(std::chrono::seconds(1), [&]() { counter++; });
    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    t.stop();

    // Counter is raised immediately after starting the timer, and 1 second
    // after
    ASSERT_EQ(counter, 2);
}

TEST(TimerTest, multipleStartsGiveNoProblem) {
    Timer t;
    uint32_t counter = 0;
    t.configure(std::chrono::seconds(1), [&]() { counter++; });
    t.start();
    t.start();
    t.start();
    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    t.stop();

    ASSERT_EQ(counter, 2);
}

TEST(TimerTest, multipleStopsGiveNoProblem) {
    Timer t;
    uint32_t counter = 0;
    t.configure(std::chrono::seconds(1), [&]() { counter++; });
    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    t.stop();
    t.stop();
    t.stop();
    t.stop();
    t.stop();

    ASSERT_EQ(counter, 2);
}

TEST(TimerTest, TimerDoesntAutomaticallyStart) {
    Timer t;
    uint32_t counter = 0;
    t.configure(std::chrono::seconds(1), [&]() { counter++; });
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    ASSERT_EQ(counter, 0);
}
