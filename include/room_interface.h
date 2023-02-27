#ifndef ROOM_INTERFACE_H
#define ROOM_INTERFACE_H

#include <cstdint>

class RoomInterface {
  public:
    RoomInterface() = default;
    virtual ~RoomInterface() = default;

    virtual std::uint32_t getTemperature() const = 0;
    virtual void setTemperature(std::uint32_t) = 0;
};

#endif // ROOM_INTERFACE_H
