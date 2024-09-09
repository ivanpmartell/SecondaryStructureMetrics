// SSMetrics.cpp : Defines the entry point for the application.
//

#include "SSMetrics.hpp"

using namespace std;

vector<Metric*> GetMetricsToCalculate(const string& metricName, const string& refSequence, const string& predSequence, const double& lambda, const bool& zeroDelta) {
    vector<Metric*> metrics;
    MetricChoice metricEnum = GetEnumFromString(metricName);
    switch (metricEnum) {
        case MetricChoice::All: {
            LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence);
            StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta);
            Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence);
            Sov94* sov94 = new Sov94("Sov94", refSequence, predSequence, zeroDelta);
            Sov99* sov99 = new Sov99("Sov99", refSequence, predSequence, zeroDelta);
            SovRefine* sovRefine = new SovRefine("SovRefine", refSequence, predSequence, zeroDelta, lambda);
            metrics.push_back(looseOverlap);
            metrics.push_back(strictOverlap);
            metrics.push_back(accuracy);
            metrics.push_back(sov94);
            metrics.push_back(sov99);
            metrics.push_back(sovRefine);
            break;
        }
        case MetricChoice::Accuracy: {
            Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence);
            metrics.push_back(accuracy);
            break;
        }
        case MetricChoice::Sov94: {
            Sov94* sov94 = new Sov94("Sov94", refSequence, predSequence, zeroDelta);
            metrics.push_back(sov94);
            break;
        }
        case MetricChoice::Sov99: {
            Sov99* sov99 = new Sov99("Sov99", refSequence, predSequence, zeroDelta);
            metrics.push_back(sov99);
            break;
        }
        case MetricChoice::SovRefine: {
            SovRefine* sovRefine = new SovRefine("SovRefine", refSequence, predSequence, zeroDelta, lambda);
            metrics.push_back(sovRefine);
            break;
        }
        case MetricChoice::LooseOverlap: {
            LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence);
            metrics.push_back(looseOverlap);
            break;
        }
        case MetricChoice::StrictOverlap: {
            StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta);
            metrics.push_back(strictOverlap);
            break;
        }
        default:
            throw runtime_error("Metric choice is invalid");
    }
    return metrics;
}

int main(int argc, char **argv) {
    CLI::App app{"Secondary structure metric calculator"};

    string metricName = "all";
    string referencePath, predictedPath;
    double lambda = 1.0;
    bool zeroDelta = false;
    app.add_option("-m,--metric", metricName, "Name of the metric to calculate. Choices: Accuracy, SOV94, SOV99, SOVrefine, FractionalOverlap, LooseOverlap, StrictOverlap");
    app.add_option("-r,--reference", referencePath, "Path to the reference sequence")
        -> required();
    app.add_option("-p,--predicted", predictedPath, "Path to the predicted sequence")
        -> required();
    app.add_option("-l,--lambda", lambda, "Adjustable scale parameter for SOVrefine");
    app.add_flag("-z,--zeroDelta", zeroDelta, "Ignore the delta value (δ = 0)");
    CLI11_PARSE(app, argc, argv);

    transform(metricName.begin(), metricName.end(), metricName.begin(), [](unsigned char c){ return std::tolower(c); });

    string refSequence = ReadSingleEntryFastaSequence(referencePath);
    string predSequence = ReadSingleEntryFastaSequence(predictedPath);
    
    vector<Metric*> calculatedMetrics = GetMetricsToCalculate(metricName, refSequence, predSequence, lambda, zeroDelta);
    for (Metric* metric : calculatedMetrics) {
        for (char const& secondaryStructure : metric->GetSecondaryStructureClasses()) {
            cout << metric->name << "_i\t" << secondaryStructure << "\t" << fixed << setprecision(3) << metric->CalculateOneClass(secondaryStructure) << endl;
        }
        cout << metric->name << "\t" << fixed << setprecision(3) << metric->CalculateAllClasses() << endl;
    }

    return 0;
}