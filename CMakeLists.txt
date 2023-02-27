cmake_minimum_required (VERSION 3.0.0)
project (Thermostat)

# needed for googletest
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# grab googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

# needed for windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
enable_testing()

# Main executable
add_executable(thermostat src/main.cpp 
                          src/thermostat.cpp 
                          src/room.cpp 
                          src/timer.cpp)
target_include_directories (thermostat PUBLIC include)
target_link_libraries(thermostat Threads::Threads)

# Test executable
add_executable(thermostat_test test/thermostat_test.cpp
                               test/room_test.cpp
                               test/timer_test.cpp
                               
                               src/room.cpp
                               src/timer.cpp
                               src/thermostat.cpp)
target_include_directories (thermostat_test PUBLIC include)
target_link_libraries(thermostat_test GTest::gtest_main GTest::gmock_main Threads::Threads)
include(GoogleTest)
gtest_discover_tests(thermostat_test)
