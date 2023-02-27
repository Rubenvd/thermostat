#ifndef MOCK_THERMOSTAT_H
#define MOCK_THERMOSTAT_H

#include "thermostat_interface.h"

#include "gtest/gtest.h"

class MockThermostat : public ThermostatInterface
{
public:
    MockThermostat() = default;
    ~MockThermostat() override = default;
    
    MOCK_METHOD(std::uint32_t, getTemperature,(), (const, override);
    MOCK_METHOD(void, setTemperature, (TemperatureRange), (override));
    MOCK_METHOD(TemperatureRange, getTemperature, (), (const, override));
    MOCK_METHOD(ThermostatState, getState, (), (const, override));
    MOCK_METHOD(void, turnOn, (), (override));
    MOCK_METHOD(void, turnOff, (), (override));
};

#endif // MOCK_THERMOSTAT_H
