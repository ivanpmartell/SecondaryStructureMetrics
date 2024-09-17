// SSMetrics.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <stdexcept>
#include <filesystem>
#include <fmt/format.h>
#include <CLI/CLI.hpp>
#include "Metrics/Interfaces/NormMetric.hpp"
#include "Metrics/Interfaces/Metric.hpp"
#include "Metrics/Accuracy.hpp"
#include "Metrics/Sov94.hpp"
#include "Metrics/LooseOverlap.hpp"
#include "Metrics/StrictOverlap.hpp"
#include "Metrics/Sov99.hpp"
#include "Metrics/SovRefine.hpp"
#include "Utils.hpp"