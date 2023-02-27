#include "thermostat.h"

#include <iostream>

Thermostat::Thermostat(std::unique_ptr<RoomInterface> room,
                       std::unique_ptr<TimerInterface> timer)
    : ThermostatInterface::ThermostatInterface(), _room(std::move(room)),
      _timer(std::move(timer)) {}

void Thermostat::setTemperature(TemperatureRange range) {
    if (range.first > range.second) {
        // Min mustn't be more than max
        range.first = range.second;
    }

    _temperature = range;
}

TemperatureRange Thermostat::getTemperature() const { return _temperature; }

ThermostatState Thermostat::getState() const { return _state; }

void Thermostat::turnOn() {
    _state = getNewState();
    _timer->configure(std::chrono::seconds(20), [this]() {
        std::cout << "Checking room temperature." << std::endl;
        _state = getNewState();
    });
    _timer->start();
}

void Thermostat::turnOff() {
    std::cout << "Turning off thermostat system." << std::endl;

    _state = ThermostatState::OFF;
    _timer->stop();
}

ThermostatState Thermostat::getNewState() const {
    std::cout << "Room temperature: " << _room->getTemperature() << std::endl;
    std::cout << "Configured temperature range: " << _temperature.first << " - "
              << _temperature.second << std::endl;
    if (_room->getTemperature() < _temperature.first) {
        std::cout << "Turning on heating systems." << std::endl;
        return ThermostatState::HEATING;
    } else if (_room->getTemperature() > _temperature.second) {
        std::cout << "Turning on cooling systems." << std::endl;
        return ThermostatState::COOLING;
    } else {
        std::cout << "Ideal temperature achieved. Systems set to idle."
                  << std::endl;
        return ThermostatState::IDLE;
    }
}
