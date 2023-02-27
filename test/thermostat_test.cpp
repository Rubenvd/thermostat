#include <gtest/gtest.h>

#include "thermostat.h"

#include "mock_room.h"
#include "mock_timer.h"

using testing::_;
using testing::Return;

class ThermostatTest : public ::testing::Test {
  protected:
    ThermostatTest() {}
    ~ThermostatTest() override {}

    void SetUp() override {
        _timerDeleted = false;
        _roomDeleted = false;

        _timer = new MockTimer();
        _room = new MockRoom();

        _timer->setOnDelete([&]() { _timerDeleted = true; });
        _room->setOnDelete([&]() { _roomDeleted = true; });
    }

    void TearDown() override {
        if (!_timerDeleted) {
            delete _timer;
        }

        if (!_roomDeleted) {
            delete _room;
        }
    }

    MockTimer *_timer{nullptr};
    MockRoom *_room{nullptr};
    bool _timerDeleted;
    bool _roomDeleted;
};

TEST_F(ThermostatTest, SetTemperatureNormal) {
    std::unique_ptr<TimerInterface> _timerPtr(_timer);
    std::unique_ptr<RoomInterface> _roomPtr(_room);

    Thermostat t(std::move(_roomPtr), std::move(_timerPtr));

    t.setTemperature(TemperatureRange(20, 28));

    ASSERT_EQ(TemperatureRange(20, 28), t.getTemperature());
}

TEST_F(ThermostatTest, SetTemperatureWrong) {
    std::unique_ptr<TimerInterface> _timerPtr(_timer);
    std::unique_ptr<RoomInterface> _roomPtr(_room);

    Thermostat t(std::move(_roomPtr), std::move(_timerPtr));

    t.setTemperature(TemperatureRange(33, 28));

    ASSERT_EQ(TemperatureRange(28, 28), t.getTemperature());
}

TEST_F(ThermostatTest, startThermostat) {
    std::unique_ptr<TimerInterface> _timerPtr(_timer);
    std::unique_ptr<RoomInterface> _roomPtr(_room);

    Thermostat t(std::move(_roomPtr), std::move(_timerPtr));

    EXPECT_CALL(*_timer, configure(_, _));
    EXPECT_CALL(*_timer, start());
    t.turnOn();
}

TEST_F(ThermostatTest, newStateShouldHeat) {
    std::unique_ptr<TimerInterface> _timerPtr(_timer);
    std::unique_ptr<RoomInterface> _roomPtr(_room);

    Thermostat t(std::move(_roomPtr), std::move(_timerPtr));

    t.setTemperature(TemperatureRange(22, 25));
    ON_CALL(*_room, getTemperature).WillByDefault(Return(20));
    t.turnOn();

    ASSERT_EQ(t.getState(), ThermostatState::HEATING);
}

TEST_F(ThermostatTest, newStateShouldCool) {
    std::unique_ptr<TimerInterface> _timerPtr(_timer);
    std::unique_ptr<RoomInterface> _roomPtr(_room);

    Thermostat t(std::move(_roomPtr), std::move(_timerPtr));

    t.setTemperature(TemperatureRange(22, 25));
    ON_CALL(*_room, getTemperature).WillByDefault(Return(44));
    t.turnOn();

    ASSERT_EQ(t.getState(), ThermostatState::COOLING);
}

TEST_F(ThermostatTest, newStateShouldBeIdle) {
    std::unique_ptr<TimerInterface> _timerPtr(_timer);
    std::unique_ptr<RoomInterface> _roomPtr(_room);

    Thermostat t(std::move(_roomPtr), std::move(_timerPtr));

    t.setTemperature(TemperatureRange(22, 25));
    ON_CALL(*_room, getTemperature).WillByDefault(Return(23));
    t.turnOn();

    ASSERT_EQ(t.getState(), ThermostatState::IDLE);
}

TEST_F(ThermostatTest, turnOff) {
    std::unique_ptr<TimerInterface> _timerPtr(_timer);
    std::unique_ptr<RoomInterface> _roomPtr(_room);

    Thermostat t(std::move(_roomPtr), std::move(_timerPtr));

    EXPECT_CALL(*_timer, stop());
    t.turnOff();

    ASSERT_EQ(t.getState(), ThermostatState::OFF);
}
