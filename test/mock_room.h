#ifndef MOCK_ROOM_H
#define MOCK_ROOM_H

#include "room_interface.h"

#include <gmock/gmock.h>

class MockRoom : public RoomInterface {
  public:
    MockRoom() = default;
    ~MockRoom() override { _onDelete(); }

    void setOnDelete(std::function<void()> cb) {
        // helper for working with smart pointers
        _onDelete = cb;
    }
    MOCK_METHOD(std::uint32_t, getTemperature, (), (const, override));
    MOCK_METHOD(void, setTemperature, (std::uint32_t), (override));

  private:
    std::function<void()> _onDelete;
};

#endif // MOCK_ROOM_H
