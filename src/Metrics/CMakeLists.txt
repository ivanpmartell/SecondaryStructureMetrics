add_library(metrics "Accuracy.cpp" "LooseOverlap.cpp" "StrictOverlap.cpp" "Sov94.cpp" "Sov99.cpp" "SovRefine.cpp" "Interfaces/IMetric.cpp" "Interfaces/Metric.cpp" "Interfaces/INormMetric.cpp" "Interfaces/NormMetric.cpp" "Interfaces/PrecalculatedMetric.cpp" "Interfaces/PrecalculatedNormMetric.cpp" "Regions/OverlapBlock.cpp" "Regions/SSBlock.cpp" "Regions/Region.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET metrics PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(metrics PUBLIC "include")