// SSMetrics.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <iomanip>
#include <CLI/CLI.hpp>
#include <stdexcept>
#include "Utils.hpp"
#include "Regions/SSBlock.hpp"
#include "Regions/OverlapBlock.hpp"
#include "Metrics/Interfaces/Metric.hpp"
#include "Metrics/Accuracy.hpp"
#include "Metrics/Sov94.hpp"
#include "Metrics/LooseOverlap.hpp"
#include "Metrics/StrictOverlap.hpp"
#include "Metrics/Sov99.hpp"
#include "Metrics/SovRefine.hpp"