// App.hpp : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <stdexcept>
#include <filesystem>
#include <fmt/format.h>
#include <CLI/CLI.hpp>
#include "Utils.hpp"
#include "../../Metrics/SSMetrics/include/Accuracy.hpp"
#include "../../Metrics/SSMetrics/include/Sov94.hpp"
#include "../../Metrics/SSMetrics/include/LooseOverlap.hpp"
#include "../../Metrics/SSMetrics/include/StrictOverlap.hpp"
#include "../../Metrics/SSMetrics/include/Sov99.hpp"
#include "../../Metrics/SSMetrics/include/SovRefine.hpp"

#include "../../Metrics/MutMetrics/include/MutAccuracy.hpp"
#include "../../Metrics/MutMetrics/include/MutConsistency.hpp"
#include "../../Metrics/MutMetrics/include/MutPrecision.hpp"

#include "../../Metrics/StatMetrics/include/ConfusionMatrix.hpp"
#include "../../Metrics/StatMetrics/include/StatAccuracy.hpp"
#include "../../Metrics/StatMetrics/include/StatPosPredVal.hpp"
#include "../../Metrics/StatMetrics/include/StatNegPredVal.hpp"
#include "../../Metrics/StatMetrics/include/StatFalsePosRate.hpp"
#include "../../Metrics/StatMetrics/include/StatFalseNegRate.hpp"
#include "../../Metrics/StatMetrics/include/StatFalseDiscoveryRate.hpp"
#include "../../Metrics/StatMetrics/include/StatFalseOmissionRate.hpp"
#include "../../Metrics/StatMetrics/include/StatSensitivity.hpp"
#include "../../Metrics/StatMetrics/include/StatSpecificity.hpp"
#include "../../Metrics/StatMetrics/include/StatMatthewsCorrelationCoefficient.hpp"