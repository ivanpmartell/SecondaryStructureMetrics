# CMakeList.txt : CMake project for SSMetrics, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable(SSMetrics "SSMetrics.cpp" "Utils.cpp" "Regions/Region.cpp" "Regions/SSBlock.cpp" "Regions/OverlapBlock.cpp" "Metrics/Interfaces/IMetric.cpp" "Metrics/Accuracy.cpp" "Metrics/Sov94.cpp"  "Metrics/LooseOverlap.cpp" "Metrics/StrictOverlap.cpp" "Metrics/Sov99.cpp" "Metrics/SovRefine.cpp" "Metrics/Interfaces/PrecalculatedMetric.cpp" "Metrics/Interfaces/Metric.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SSMetrics PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(SSMetrics PRIVATE CLI11::CLI11)
