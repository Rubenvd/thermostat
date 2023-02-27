#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "thermostat_interface.h"

#include "room_interface.h"
#include "timer_interface.h"

#include <memory>

class Thermostat : public ThermostatInterface
{
public:
    Thermostat(std::unique_ptr<RoomInterface> room,
                std::unique_ptr<TimerInterface> timer);
    ~Thermostat() override = default;
    void setTemperature(TemperatureRange temp) override;
    TemperatureRange getTemperature() const override;
    ThermostatState getState() const override;
    void turnOn() override;
    void turnOff() override;
    
private:
    TemperatureRange _temperature {0,0};
    ThermostatState _state {ThermostatState::OFF};
    
    std::unique_ptr<RoomInterface> _room;
    std::unique_ptr<TimerInterface> _timer;
    
    ThermostatState getNewState() const;
};

#endif // THERMOSTAT_H
