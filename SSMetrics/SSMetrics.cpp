// SSMetrics.cpp : Defines the entry point for the application.
//

#include "SSMetrics.hpp"

using namespace std;

int main(int argc, char **argv) {
    CLI::App app{"Secondary structure metric calculator"};

    string metric, referencePath, predictedPath;
    double lambda = 1.0;
    bool zeroDelta = false;
    app.add_option("-m,--metric", metric, "Name of the metric to calculate. Choices: Accuracy, SOV94, SOV99, SOVrefine, FractionalOverlap, LooseOverlap, StrictOverlap")
        -> required();
    app.add_option("-r,--reference", referencePath, "Path to the reference sequence")
        -> required();
    app.add_option("-p,--predicted", predictedPath, "Path to the predicted sequence")
        -> required();
    app.add_option("-l,--lambda", lambda, "Adjustable scale parameter for SOVrefine");
    app.add_flag("-z,--zeroDelta", zeroDelta, "Ignore the delta value (δ = 0)");
    CLI11_PARSE(app, argc, argv);

    transform(metric.begin(), metric.end(), metric.begin(), [](unsigned char c){ return std::tolower(c); });
    MetricChoice metricEnum = GetEnumFromString(metric);

    string refSequence = ReadSingleEntryFastaSequence(referencePath);
    string predSequence = ReadSingleEntryFastaSequence(predictedPath);
    unordered_map<char, SSEsequence*> refBlocks = GetBlocksForSequence(refSequence);
    unordered_map<char, SSEsequence*> predBlocks = GetBlocksForSequence(predSequence);

    auto results = CalculateOverlappingBlocks(refBlocks, predBlocks);
    unordered_map<char, vector<OverlapBlock*>>* overlappingBlocks = &results.first;
    unordered_map<char, vector<SSBlock*>>* nonOverlappingBlocks = &results.second;

    switch (metricEnum)
    {
        case MetricChoice::Accuracy:
        {
            Accuracy acc = Accuracy(overlappingBlocks, refSequence.length());
            cout << acc.CalculateAllClasses() << endl;
            cout << acc.CalculateOneClass('C') << endl;
            cout << acc.CalculateOneClass('H') << endl;
            break;
        }
        case MetricChoice::Sov94:
            //instance.ZeroDelta = zeroDelta;
            break;
        case MetricChoice::Sov99:
            break;
        case MetricChoice::SovRefine:
            //instance.Lambda = lambda;
            break;
        case MetricChoice::LooseOverlap:
            break;
        case MetricChoice::StrictOverlap:
            break;
        default:
            throw runtime_error("Metric choice is invalid");
    }

    //instance.Precomputation();
    //cout << instance.ComputeAllClasses() << endl;
    //cout << instance.ComputeOneClass('H') << endl;
    //cout << instance.ComputeOneClass('C') << endl;

    return 0;
}