#include "room.h"

std::uint32_t Room::getTemperature() const { return _temperature; }

void Room::setTemperature(std::uint32_t temp) { _temperature = temp; }
