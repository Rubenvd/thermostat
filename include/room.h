#ifndef ROOM_H
#define ROOM_H

#include "room_interface.h"

class Room : public RoomInterface {
  public:
    Room() = default;
    ~Room() override = default;

    std::uint32_t getTemperature() const override;
    void setTemperature(std::uint32_t) override;

  private:
    std::uint32_t _temperature{};
};

#endif // ROOM_H
