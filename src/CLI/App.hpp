// App.hpp : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <stdexcept>
#include <filesystem>
#include <fmt/format.h>
#include <CLI/CLI.hpp>
#include "Utils.hpp"
#include "../Metrics/include/Accuracy.hpp"
#include "../Metrics/include/Sov94.hpp"
#include "../Metrics/include/LooseOverlap.hpp"
#include "../Metrics/include/StrictOverlap.hpp"
#include "../Metrics/include/Sov99.hpp"
#include "../Metrics/include/SovRefine.hpp"
