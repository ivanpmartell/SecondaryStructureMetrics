# Add source to this project's executable.
add_executable(ssmetrics "App.cpp" "Utils.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ssmetrics PROPERTY CXX_STANDARD 20)
endif()

# Packages / Libraries to install
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(ssmetrics PRIVATE CLI11::CLI11)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(ssmetrics PRIVATE fmt::fmt)

target_link_libraries(ssmetrics PRIVATE metrics)