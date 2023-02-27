#ifndef THERMOSTAT_INTERFACE_H
#define THERMOSTAT_INTERFACE_H

#include <cstdint>
#include <utility>

enum class ThermostatState {
    OFF,
    IDLE,
    HEATING,
    COOLING
};

using TemperatureRange = std::pair<std::uint32_t, std::uint32_t>;

class ThermostatInterface
{
public:
    ThermostatInterface() = default;
    virtual ~ThermostatInterface() = default;
    virtual void setTemperature(TemperatureRange temp) = 0;
    virtual TemperatureRange getTemperature() const = 0;
    virtual ThermostatState getState() const = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

#endif // THERMOSTAT_INTERFACE_H
