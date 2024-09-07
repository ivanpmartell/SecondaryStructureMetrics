// SSMetrics.cpp : Defines the entry point for the application.
//

#include "SSMetrics.hpp"

using namespace std;

int main(int argc, char **argv) {
    CLI::App app{"Secondary structure metric calculator"};

    string metric = "all";
    string referencePath, predictedPath;
    double lambda = 1.0;
    bool zeroDelta = false;
    app.add_option("-m,--metric", metric, "Name of the metric to calculate. Choices: Accuracy, SOV94, SOV99, SOVrefine, FractionalOverlap, LooseOverlap, StrictOverlap");
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
    unordered_map<char, vector<SSBlock*>> refBlocks = GetBlocksForSequence(refSequence);
    unordered_map<char, vector<SSBlock*>> predBlocks = GetBlocksForSequence(predSequence);
    
    auto blockResults = CalculateOverlappingBlocks(refBlocks, predBlocks);
    unordered_map<char, vector<OverlapBlock*>>* overlappingBlocks = &blockResults.first;
    unordered_map<char, vector<SSBlock*>>* nonOverlappingBlocks = &blockResults.second;

    vector<char> secondaryStructureClasses;
    for(auto const& kvPairs: refBlocks)
        secondaryStructureClasses.push_back(kvPairs.first);
    
    unordered_map<MetricChoice, unordered_map<char, double>> results;
    switch (metricEnum) {
        case MetricChoice::All: {
            Accuracy acc = Accuracy(overlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "Accuracy_i\t" << sse << "\t" << fixed << setprecision(3) << acc.CalculateOneClass(sse) << endl;
            }
            LooseOverlap looseOverlap = LooseOverlap(overlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "LooseOverlap_i\t" << sse << "\t" << fixed << setprecision(3) << looseOverlap.CalculateOneClass(sse) << endl;
            }
            StrictOverlap strictOverlap = StrictOverlap(overlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "StrictOverlap_i\t" << sse << "\t" << fixed << setprecision(3) << strictOverlap.CalculateOneClass(sse) << endl;
            }
            Sov94 sov94 = Sov94(overlappingBlocks, refSequence.length(), zeroDelta);
            for (char const& sse : secondaryStructureClasses) {
                cout << "SOV_94_i\t" << sse << "\t" << fixed << setprecision(3) << sov94.CalculateOneClass(sse) << endl;
            }
            Sov99 sov99 = Sov99(overlappingBlocks, nonOverlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "SOV_99_i\t" << sse << "\t" << fixed << setprecision(3) << sov99.CalculateOneClass(sse) << endl;
            }
            SovRefine sovRefine = SovRefine(overlappingBlocks, nonOverlappingBlocks, refSequence.length(), refBlocks.size(), lambda);
            for (char const& sse : secondaryStructureClasses) {
                cout << "SOV_refine_i\t" << sse << "\t" << fixed << setprecision(3) << sovRefine.CalculateOneClass(sse) << endl;
            }
            cout << "Accuracy\t" << fixed << setprecision(3) << acc.CalculateAllClasses() << endl;
            cout << "LooseOverlap\t" << fixed << setprecision(3) << looseOverlap.CalculateAllClasses() << endl;
            cout << "StrictOverlap\t" << fixed << setprecision(3) << strictOverlap.CalculateAllClasses() << endl;
            cout << "SOV_94\t" << fixed << setprecision(3) << sov94.CalculateAllClasses() << endl;
            cout << "SOV_99\t" << fixed << setprecision(3) << sov99.CalculateAllClasses() << endl;
            cout << "SOV_refine\t" << fixed << setprecision(3) << sovRefine.CalculateAllClasses() << endl;
            break;
        }
        case MetricChoice::Accuracy: {
            Accuracy acc = Accuracy(overlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "Accuracy_i\t" << sse << "\t" << fixed << setprecision(3) << acc.CalculateOneClass(sse) << endl;
            }
            cout << "Accuracy\t" << fixed << setprecision(3) << acc.CalculateAllClasses() << endl;
            break;
        }
        case MetricChoice::Sov94: {
            Sov94 sov94 = Sov94(overlappingBlocks, refSequence.length(), zeroDelta);
            for (char const& sse : secondaryStructureClasses) {
                cout << "SOV_94_i\t" << sse << "\t" << fixed << setprecision(3) << sov94.CalculateOneClass(sse) << endl;
            }
            cout << "SOV_94\t" << fixed << setprecision(3) << sov94.CalculateAllClasses() << endl;
            break;
        }
        case MetricChoice::Sov99: {
            Sov99 sov99 = Sov99(overlappingBlocks, nonOverlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "SOV_99_i\t" << sse << "\t" << fixed << setprecision(3) << sov99.CalculateOneClass(sse) << endl;
            }
            cout << "SOV_99\t" << fixed << setprecision(3) << sov99.CalculateAllClasses() << endl;
            break;
        }
        case MetricChoice::SovRefine: {
            SovRefine sovRefine = SovRefine(overlappingBlocks, nonOverlappingBlocks, refSequence.length(), refBlocks.size(), lambda);
            for (char const& sse : secondaryStructureClasses) {
                cout << "SOV_refine_i\t" << sse << "\t" << fixed << setprecision(3) << sovRefine.CalculateOneClass(sse) << endl;
            }
            cout << "SOV_refine\t" << fixed << setprecision(3) << sovRefine.CalculateAllClasses() << endl;
            break;
        }
        case MetricChoice::LooseOverlap: {
            LooseOverlap looseOverlap = LooseOverlap(overlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "LooseOverlap_i\t" << sse << "\t" << fixed << setprecision(3) << looseOverlap.CalculateOneClass(sse) << endl;
            }
            cout << "LooseOverlap\t" << fixed << setprecision(3) << looseOverlap.CalculateAllClasses() << endl;
            break;
        }
        case MetricChoice::StrictOverlap: {
            StrictOverlap strictOverlap = StrictOverlap(overlappingBlocks, refSequence.length());
            for (char const& sse : secondaryStructureClasses) {
                cout << "StrictOverlap_i\t" << sse << "\t" << fixed << setprecision(3) << strictOverlap.CalculateOneClass(sse) << endl;
            }
            cout << "StrictOverlap\t" << fixed << setprecision(3) << strictOverlap.CalculateAllClasses() << endl;
            break;
        }
        default:
            throw runtime_error("Metric choice is invalid");
    }

    return 0;
}