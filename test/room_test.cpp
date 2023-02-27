#include <gtest/gtest.h>

#include "room.h"

TEST(RoomTest, Temperature) {
    Room r;
    r.setTemperature(58);
    ASSERT_EQ(r.getTemperature(), 58);
}
