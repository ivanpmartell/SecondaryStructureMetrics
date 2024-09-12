// SSMetrics.cpp : Defines the entry point for the application.
//

#include "SSMetrics.hpp"

using namespace std;

vector<Metric*> GetMetricsToCalculate(const string& metricName, const string& refSequence, const string& predSequence, const double& lambda, const bool& zeroDelta, PrecalculatedMetric* precalculation) {
    vector<Metric*> metrics;
    const MetricChoice& metricEnum = GetEnumFromString(metricName);
    switch (metricEnum) {
        case MetricChoice::All: {
            LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence, precalculation);
            StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta, precalculation);
            Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence, precalculation);
            Sov94* sov94 = new Sov94("Sov_94", refSequence, predSequence, zeroDelta, precalculation);
            Sov99* sov99 = new Sov99("Sov_99", refSequence, predSequence, zeroDelta, precalculation);
            SovRefine* sovRefine = new SovRefine("SovRefine", refSequence, predSequence, zeroDelta, lambda, precalculation);
            metrics.push_back(looseOverlap);
            metrics.push_back(strictOverlap);
            metrics.push_back(accuracy);
            metrics.push_back(sov94);
            metrics.push_back(sov99);
            metrics.push_back(sovRefine);
            break;
        }
        case MetricChoice::Accuracy: {
            Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence, precalculation);
            metrics.push_back(accuracy);
            break;
        }
        case MetricChoice::Sov94: {
            Sov94* sov94 = new Sov94("Sov_94", refSequence, predSequence, zeroDelta, precalculation);
            metrics.push_back(sov94);
            break;
        }
        case MetricChoice::Sov99: {
            Sov99* sov99 = new Sov99("Sov_99", refSequence, predSequence, zeroDelta, precalculation);
            metrics.push_back(sov99);
            break;
        }
        case MetricChoice::SovRefine: {
            SovRefine* sovRefine = new SovRefine("SovRefine", refSequence, predSequence, zeroDelta, lambda, precalculation);
            metrics.push_back(sovRefine);
            break;
        }
        case MetricChoice::LooseOverlap: {
            LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence, precalculation);
            metrics.push_back(looseOverlap);
            break;
        }
        case MetricChoice::StrictOverlap: {
            StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta, precalculation);
            metrics.push_back(strictOverlap);
            break;
        }
        default:
            throw runtime_error("Metric choice is invalid");
    }
    return metrics;
}

void run(string& metricName, const string& reference, const string& predicted, const double& lambda, const bool& zeroDelta, const bool& useFasta) {
    transform(metricName.begin(), metricName.end(), metricName.begin(), [](unsigned char c){ return std::tolower(c); });
    
    string refSequence, predSequence;
    if (useFasta) {
        refSequence = ReadSingleEntryFastaSequence(reference);
        predSequence = ReadSingleEntryFastaSequence(predicted);
    }
    else {
        refSequence = reference;
        predSequence = predicted;
    }
    PrecalculatedMetric* precalculation = new PrecalculatedMetric(refSequence, predSequence);

    vector<Metric*> calculatedMetrics = GetMetricsToCalculate(metricName, refSequence, predSequence, lambda, zeroDelta, precalculation);
    for (Metric* metric : calculatedMetrics) {
        for (const auto& secondaryStructure : metric->GetSecondaryStructureClasses()) {
            cout << metric->name << "_i\t" << secondaryStructure << "\t" << fixed << setprecision(3) << metric->CalculateOneClass(secondaryStructure) << endl;
        }
        cout << metric->name << "\t" << fixed << setprecision(3) << metric->CalculateAllClasses() << endl;
        delete metric;
    }
    calculatedMetrics.clear();
    delete precalculation;
}

int main(int argc, char **argv) {
    CLI::App app{"Secondary structure metric calculator"};

    string metricName = "all";
    string reference, predicted;
    double lambda = 1.0;
    bool zeroDelta = false;
    bool useFasta = false;
    app.add_flag("-f,--fasta", useFasta, "Reference and predicted sequences are taken as fasta files");
    app.add_option("-r,--reference", reference, "Path to the reference sequence")
        -> required();
    app.add_option("-p,--predicted", predicted, "Path to the predicted sequence")
        -> required();
    app.add_option("-m,--metric", metricName, "Name of the metric to calculate. Ignore to calculate all metrics.\nMetric Choices: Accuracy, SOV94, SOV99, SOVrefine, LooseOverlap, StrictOverlap");
    app.add_option("-l,--lambda", lambda, "Adjustable scale parameter for SOVrefine");
    app.add_flag("-z,--zeroDelta", zeroDelta, "This will omit the delta value (delta = 0)");
    CLI11_PARSE(app, argc, argv);

    try {
        run(metricName, reference, predicted, lambda, zeroDelta, useFasta);
        return 0;
    }
    catch (const exception& e) {
        cerr << e.what();
        return 1;
    }
}