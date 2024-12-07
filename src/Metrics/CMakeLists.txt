if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.11)
    file(GLOB_RECURSE metrics_src CONFIGURE_DEPENDS *.cpp)
else()
    file(GLOB metrics_src *.cpp */*.cpp)
endif()

add_library(metrics ${metrics_src})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET metrics PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(metrics PUBLIC "SSMetrics/include" "MutMetrics/include" "StatMetrics/include")