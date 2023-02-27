#include "room.h"
#include "thermostat.h"
#include "timer.h"

#include <stdio.h>
#include <thread>

int main() {
    {
        std::unique_ptr<TimerInterface> timer_ptr = std::make_unique<Timer>();
        std::unique_ptr<RoomInterface> room_ptr = std::make_unique<Room>();
        Thermostat thermostat(std::move(room_ptr), std::move(timer_ptr));
        TemperatureRange range(20, 28);
        thermostat.setTemperature(range);
        thermostat.turnOn();

        // simulate 100 seconds of simulation
        std::this_thread::sleep_for(std::chrono::seconds(100));
    }
    return 0;
}
