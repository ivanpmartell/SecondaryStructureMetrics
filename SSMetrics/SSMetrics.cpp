// SSMetrics.cpp : Defines the entry point for the application.
//

#include "SSMetrics.hpp"

using namespace std;

static vector<Metric*> GetMetricsToCalculate(string& metricName, const string& refSequence, const string& predSequence, const double& lambda, const bool& zeroDelta, PrecalculatedMetric* precalculation, PrecalculatedNormMetric* normPrecalculation) {
    transform(metricName.begin(), metricName.end(), metricName.begin(), [](unsigned char c){ return std::tolower(c); });
    vector<Metric*> metrics;
    if (metricName == "all") {
        normPrecalculation = new PrecalculatedNormMetric(refSequence, predSequence, precalculation);
        LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence, precalculation);
        StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta, precalculation);
        Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence, precalculation);
        Sov94* sov94 = new Sov94("Sov_94", refSequence, predSequence, zeroDelta, precalculation);
        Sov99* sov99 = new Sov99("Sov_99", refSequence, predSequence, zeroDelta, normPrecalculation, precalculation);
        SovRefine* sovRefine = new SovRefine("SovRefine", refSequence, predSequence, zeroDelta, lambda, normPrecalculation, precalculation);
        metrics.push_back(looseOverlap);
        metrics.push_back(strictOverlap);
        metrics.push_back(accuracy);
        metrics.push_back(sov94);
        metrics.push_back(sov99);
        metrics.push_back(sovRefine);
        return metrics;
    }
    else if (metricName == "accuracy") {
        Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence, precalculation);
        metrics.push_back(accuracy);
        return metrics;
    }
    else if (metricName == "sovrefine") {
        SovRefine* sovRefine = new SovRefine("SovRefine", refSequence, predSequence, zeroDelta, lambda, nullptr, precalculation);
        metrics.push_back(sovRefine);
        return metrics;
    }
    else if (metricName == "sov99") {
        Sov99* sov99 = new Sov99("Sov_99", refSequence, predSequence, zeroDelta, nullptr, precalculation);
        metrics.push_back(sov99);
        return metrics;
    }
    else if (metricName == "Sov94") {
        Sov94* sov94 = new Sov94("Sov_94", refSequence, predSequence, zeroDelta, precalculation);
        metrics.push_back(sov94);
        return metrics;
    }
    else if (metricName == "strictoverlap") {
        StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta, precalculation);
        metrics.push_back(strictOverlap);
        return metrics;
    }
    else if (metricName == "looseoverlap") {
        LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence, precalculation);
        metrics.push_back(looseOverlap);
        return metrics;
    }
    throw runtime_error("Metric choice is invalid");
}

static void run(string& metricName, const string& refSequence, const string& predSequence, const double& lambda, const bool& zeroDelta) {
    PrecalculatedMetric* precalculation = new PrecalculatedMetric(refSequence, predSequence);
    PrecalculatedNormMetric* normPrecalculation = nullptr;

    vector<Metric*> calculatedMetrics = GetMetricsToCalculate(metricName, refSequence, predSequence, lambda, zeroDelta, precalculation, normPrecalculation);
    for (Metric* metricPtr : calculatedMetrics) {
        Metric& metric = *metricPtr;
        string& mName = metric.GetName();
        for (const auto& secondaryStructure : metric.GetSecondaryStructureClasses()) {
            fmt::print("{0}_i\t{1}\t{2:.3f}\n", mName, secondaryStructure, metric.CalculateOneClass(secondaryStructure));
        }
        fmt::print("{0}\t{1:.3f}\n", mName, metric.CalculateAllClasses());
        delete metricPtr;
    }
    calculatedMetrics.clear();
    delete normPrecalculation;
    delete precalculation;
}

int main(int argc, char **argv) {
    CLI::App app{"Secondary structure metric calculator"};

    string metricName = "all";
    string reference, predicted;
    double lambda = 1.0;
    bool zeroDelta = false;
    app.add_option("-r,--reference", reference, "Reference sequence (Fasta file also accepted)")
        -> required();
    app.add_option("-p,--predicted", predicted, "Predicted sequence (Fasta file also accepted)")
        -> required();
    app.add_option("-m,--metric", metricName, "Name of the metric to calculate. Ignore to calculate all metrics.\nMetric Choices: Accuracy, SOV94, SOV99, SOVrefine, LooseOverlap, StrictOverlap");
    app.add_option("-l,--lambda", lambda, "Adjustable scale parameter for SOVrefine");
    app.add_flag("-z,--zeroDelta", zeroDelta, "This will omit the delta value (delta = 0)");
    CLI11_PARSE(app, argc, argv);

    try {
        if (filesystem::exists(reference)) {
            auto refFastaFile = FastaReader(reference);
            auto predFastaFile = FastaReader(predicted);
            while(refFastaFile.ReadNextSequence()) {
                if (predFastaFile.ReadNextSequence()) {
                    fmt::print("Metrics calculated for reference {0} and prediction {1}\n", refFastaFile.GetId(), predFastaFile.GetId());
                    run(metricName, refFastaFile.GetSequence(), predFastaFile.GetSequence(), lambda, zeroDelta);
                }
                else {
                    throw runtime_error("Reference fasta file contains more records than predicted file");
                }
            }
            if (predFastaFile.ReadNextSequence()) {
                throw runtime_error("Predicted fasta file contains more records than reference file.");
            }
        }
        else {
            run(metricName, reference, predicted, lambda, zeroDelta);
        }
        return 0;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}