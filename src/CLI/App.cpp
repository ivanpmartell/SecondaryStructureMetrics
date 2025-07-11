// App.cpp : Defines the entry point for the application.
//

#include "include/App.hpp"

using namespace std;

static vector<Metric*> GetMetricsToCalculate(const string& metricName, const string& refSequence, const string& predSequence, const double& lambda, const bool& zeroDelta, PrecalculatedMetric* precalculation, PrecalculatedNormMetric* normPrecalculation) {
    vector<Metric*> metrics;
    if (metricName == "all") {
        normPrecalculation = new PrecalculatedNormMetric(refSequence, predSequence, precalculation);
        LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence, precalculation);
        StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta, precalculation);
        Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence, precalculation);
        Sov94* sov94 = new Sov94("SOV_94", refSequence, predSequence, zeroDelta, false, precalculation);
        Sov99* sov99 = new Sov99("SOV_99", refSequence, predSequence, zeroDelta, normPrecalculation, precalculation);
        SovRefine* sovRefine = new SovRefine("SOV_refine", refSequence, predSequence, zeroDelta, lambda, normPrecalculation, precalculation);
        metrics.push_back(looseOverlap);
        metrics.push_back(strictOverlap);
        metrics.push_back(accuracy);
        metrics.push_back(sov94);
        metrics.push_back(sov99);
        metrics.push_back(sovRefine);
    }
    else if (metricName == "accuracy") {
        Accuracy* accuracy = new Accuracy("Accuracy", refSequence, predSequence, precalculation);
        metrics.push_back(accuracy);
    }
    else if (metricName == "sovrefine") {
        SovRefine* sovRefine = new SovRefine("SOV_refine", refSequence, predSequence, zeroDelta, lambda, nullptr, precalculation);
        metrics.push_back(sovRefine);
    }
    else if (metricName == "sov99") {
        Sov99* sov99 = new Sov99("SOV_99", refSequence, predSequence, zeroDelta, nullptr, precalculation);
        metrics.push_back(sov99);
    }
    else if (metricName == "Sov94") {
        Sov94* sov94 = new Sov94("SOV_94", refSequence, predSequence, zeroDelta, false, precalculation);
        metrics.push_back(sov94);
    }
    else if (metricName == "strictoverlap") {
        StrictOverlap* strictOverlap = new StrictOverlap("StrictOverlap", refSequence, predSequence, zeroDelta, precalculation);
        metrics.push_back(strictOverlap);
    }
    else if (metricName == "looseoverlap") {
        LooseOverlap* looseOverlap = new LooseOverlap("LooseOverlap", refSequence, predSequence, precalculation);
        metrics.push_back(looseOverlap);
    }
    else {
        throw runtime_error("Metric choice is invalid");
    }
    return metrics;
}

static void RunDefault(const string& metricName, const string& refSequence, const string& predSequence, const double& lambda, const bool& zeroDelta) {
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

static int DefaultCalculator(const bool& useFasta, const string& reference, const string& predicted, const string& metricName, const double& lambda, const bool& zeroDelta) {
    if (useFasta) {
        CheckFile("reference" ,reference);
        CheckFile("predicted" ,predicted);
        auto refFastaFile = FastaReader(reference);
        auto predFastaFile = FastaReader(predicted);
        while(refFastaFile.ReadNextSequence()) {
            if (predFastaFile.ReadNextSequence()) {
                fmt::print("Metrics calculated for reference {0} and prediction {1}\n", refFastaFile.GetId(), predFastaFile.GetId());
                RunDefault(metricName, refFastaFile.GetSequence(), predFastaFile.GetSequence(), lambda, zeroDelta);
            }
            else {
                throw runtime_error("Reference fasta file contains more records than predicted file");
            }
        }
        if (predFastaFile.ReadNextSequence()) {
            throw runtime_error("Predicted fasta file contains more records than reference file");
        }
    }
    else {
        if (HasFastaEnding(reference) || HasFastaEnding(predicted)) {
            cerr << "WARNING: You are most likely (unintentionally) using the fasta FILENAME as a sequence itself. Please add -f flag to read the fasta file" << endl;
        }
        RunDefault(metricName, reference, predicted, lambda, zeroDelta);
    }
    return 0;
}

static vector<MutMetric*> GetMutationMetricsToCalculate(const string& metricName, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred, const double& lambda, const bool& zeroDelta) {
    vector<MutMetric*> metrics;
    if (metricName == "accuracy") {
        MutAccuracy* mutationAccuracy = new MutAccuracy("Accuracy", consensusRef, mutatedRef, consensusPred, mutatedPred);
        metrics.push_back(mutationAccuracy);
    }
    else if (metricName == "consistency") {
        MutConsistency* mutationConsistency = new MutConsistency("Consistency", consensusRef, mutatedRef, consensusPred, mutatedPred);
        metrics.push_back(mutationConsistency);
    }
    else if (metricName == "precision") {
        MutPrecision* mutationPrecision = new MutPrecision("Precision", consensusRef, mutatedRef, consensusPred, mutatedPred, lambda, zeroDelta);
        metrics.push_back(mutationPrecision);
    }
    else {
        throw runtime_error("Metric choice is invalid");
    }
    return metrics;
}

static void RunMutation(const string& metricName, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred, const double& lambda, const bool& zeroDelta, const string& subMetric) {
    vector<MutMetric*> calculatedMetrics = GetMutationMetricsToCalculate(metricName, consensusRef, mutatedRef, consensusPred, mutatedPred, lambda, zeroDelta);
    for (MutMetric* metricPtr : calculatedMetrics) {
        MutMetric& metric = *metricPtr;
        string& mName = metric.GetName();
        string lowercaseSubMetric;
        lowercaseSubMetric.reserve(subMetric.size());
        for (size_t i = 0; i < subMetric.size(); ++i) {
            lowercaseSubMetric += std::tolower(static_cast<unsigned char>(subMetric[i]));
        }
        if (lowercaseSubMetric != "") {
            mName += "-" + lowercaseSubMetric;
        }
        fmt::print("{0}\t{1:.3f}\n", mName, metric.Calculate(lowercaseSubMetric));
        fmt::print(">{0}\n{1}\n", "Resulting Reference sequence", metric.GetResultingRefSequence());
        fmt::print(">{0}\n{1}\n", "Resulting Prediction sequence", metric.GetResultingPredSequence());
        delete metricPtr;
    }
    calculatedMetrics.clear();
}

static int MutationalCalculator(const bool& useFasta, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred, const string& metricName, const double& lambda, const bool& zeroDelta, const string& subMetric) {
    if (useFasta) {
        CheckFile("consensus reference" ,consensusRef);
        CheckFile("consensus mutation" ,mutatedRef);
        CheckFile("predicted reference" ,consensusPred);
        CheckFile("predicted mutation" ,mutatedPred);
        auto consensusRefFastaFile = FastaReader(consensusRef);
        auto mutatedRefFastaFile = FastaReader(mutatedRef);
        auto consensusPredFastaFile = FastaReader(consensusPred);
        auto mutatedPredFastaFile = FastaReader(mutatedPred);
        while(consensusRefFastaFile.ReadNextSequence()) {
            if (!mutatedRefFastaFile.ReadNextSequence()) {
                throw runtime_error("Consensus reference fasta file contains more records than mutated reference file");
            }
            if (!consensusPredFastaFile.ReadNextSequence()) {
                throw runtime_error("Consensus reference fasta file contains more records than consensus prediction file");
            }
            if (!mutatedPredFastaFile.ReadNextSequence()) {
                throw runtime_error("Consensus reference fasta file contains more records than mutated prediction file");
            }
            fmt::print("Mutation metrics calculated for consensus ({0}, {1}) and prediction ({2}, {3})\n", consensusRefFastaFile.GetId(), mutatedRefFastaFile.GetId(), consensusPredFastaFile.GetId(), mutatedPredFastaFile.GetId());
            RunMutation(metricName, consensusRefFastaFile.GetSequence(), mutatedRefFastaFile.GetSequence(), consensusPredFastaFile.GetSequence(), mutatedPredFastaFile.GetSequence(), lambda, zeroDelta, subMetric);
        }
        if (mutatedRefFastaFile.ReadNextSequence()) {
            throw runtime_error("Mutated reference fasta file contains more records than consensus reference file");
        }
        if (consensusPredFastaFile.ReadNextSequence()) {
            throw runtime_error("Consensus prediction fasta file contains more records than consensus reference file");
        }
        if (mutatedPredFastaFile.ReadNextSequence()) {
            throw runtime_error("Mutated prediction fasta file contains more records than consensus reference file");
        }
    }
    else {
        if (HasFastaEnding(consensusRef) || HasFastaEnding(mutatedRef) || HasFastaEnding(consensusPred) || HasFastaEnding(mutatedPred)) {
            cerr << "WARNING: You are most likely (unintentionally) using the fasta FILENAME as a sequence itself. Please add -f flag to read the fasta file" << endl;
        }
        RunMutation(metricName, consensusRef, mutatedRef, consensusPred, mutatedPred, lambda, zeroDelta, subMetric);
    }
    return 0;
}

static vector<StatMetric*> GetStatisticalMetricsToCalculate(const string& metricName, const string& reference, const string& predicted, const char posClass) {
    vector<StatMetric*> metrics;
    ConfusionMatrix* confusionMatrix = new ConfusionMatrix(reference, predicted, posClass);
    if (metricName == "all") {
        StatAccuracy* statAccuracy = new StatAccuracy("Accuracy", confusionMatrix);
        StatSensitivity* statSensitivity = new StatSensitivity("Sensitivity", confusionMatrix);
        StatSpecificity* statSpecificity = new StatSpecificity("Specificity", confusionMatrix);
        StatPosPredVal* statPosPredVal = new StatPosPredVal("PositivePredictiveValue", confusionMatrix);
        StatNegPredVal* statNegPredVal = new StatNegPredVal("NegativePredictiveValue", confusionMatrix);
        StatFalsePosRate* statFalsePosRate = new StatFalsePosRate("FalsePositiveRate", confusionMatrix);
        StatFalseNegRate* statFalseNegRate = new StatFalseNegRate("FalseNegativeRate", confusionMatrix);
        StatFalseOmissionRate* statFalseOmissionRate = new StatFalseOmissionRate("FalseOmissionRate", confusionMatrix);
        StatFalseDiscoveryRate* statFalseDiscoveryRate = new StatFalseDiscoveryRate("FalseDiscoveryRate", confusionMatrix);
        StatMatthewsCorrelationCoefficient* statMatthewsCorrelationCoefficient = new StatMatthewsCorrelationCoefficient("MatthewsCorrelationCoefficient", confusionMatrix);
        metrics.push_back(statAccuracy);
        metrics.push_back(statSensitivity);
        metrics.push_back(statSpecificity);
        metrics.push_back(statPosPredVal);
        metrics.push_back(statNegPredVal);
        metrics.push_back(statFalsePosRate);
        metrics.push_back(statFalseNegRate);
        metrics.push_back(statFalseOmissionRate);
        metrics.push_back(statFalseDiscoveryRate);
        metrics.push_back(statMatthewsCorrelationCoefficient);
    }
    else if (metricName == "accuracy") {
        StatAccuracy* statAccuracy = new StatAccuracy("Accuracy", confusionMatrix);
        metrics.push_back(statAccuracy);
    }
    else if (metricName == "sensitivity") {
        StatSensitivity* statSensitivity = new StatSensitivity("Sensitivity", confusionMatrix);
        metrics.push_back(statSensitivity);
    }
    else if (metricName == "specificity") {
        StatSpecificity* statSpecificity = new StatSpecificity("Specificity", confusionMatrix);
        metrics.push_back(statSpecificity);
    }
    else if (metricName == "ppv") {
        StatPosPredVal* statPosPredVal = new StatPosPredVal("PositivePredictiveValue", confusionMatrix);
        metrics.push_back(statPosPredVal);
    }
    else if (metricName == "npv") {
        StatNegPredVal* statNegPredVal = new StatNegPredVal("NegativePredictiveValue", confusionMatrix);
        metrics.push_back(statNegPredVal);
    }
    else if (metricName == "fpr") {
        StatFalsePosRate* statFalsePosRate = new StatFalsePosRate("FalsePositiveRate", confusionMatrix);
        metrics.push_back(statFalsePosRate);
    }
    else if (metricName == "fnr") {
        StatFalseNegRate* statFalseNegRate = new StatFalseNegRate("FalseNegativeRate", confusionMatrix);
        metrics.push_back(statFalseNegRate);
    }
    else if (metricName == "for") {
        StatFalseOmissionRate* statFalseOmissionRate = new StatFalseOmissionRate("FalseOmissionRate", confusionMatrix);
        metrics.push_back(statFalseOmissionRate);
    }
    else if (metricName == "fdr") {
        StatFalseDiscoveryRate* statFalseDiscoveryRate = new StatFalseDiscoveryRate("FalseDiscoveryRate", confusionMatrix);
        metrics.push_back(statFalseDiscoveryRate);
    }
    else if (metricName == "mcc") {
        StatMatthewsCorrelationCoefficient* statMatthewsCorrelationCoefficient = new StatMatthewsCorrelationCoefficient("MatthewsCorrelationCoefficient", confusionMatrix);
        metrics.push_back(statMatthewsCorrelationCoefficient);
    }
    else {
        throw runtime_error("Metric choice is invalid");
    }
    return metrics;
}

static void RunStatistics(const string& metricName, const string& reference, const string& predicted, const char posClass) {
    vector<StatMetric*> calculatedMetrics = GetStatisticalMetricsToCalculate(metricName, reference, predicted, posClass);
    for (StatMetric* metricPtr : calculatedMetrics) {
        StatMetric& metric = *metricPtr;
        string& mName = metric.GetName();
        fmt::print("{0}\t{1:.3f}\n", mName, metric.Calculate());
        delete metricPtr;
    }
    calculatedMetrics.clear();
}

static int StatisticalCalculator(const bool& useFasta, const string& reference, const string& predicted, const string& metricName, const char posClass) {
    if (useFasta) {
        CheckFile("reference", reference);
        CheckFile("predicted", predicted);
        auto refFastaFile = FastaReader(reference);
        auto predFastaFile = FastaReader(predicted);
        while(refFastaFile.ReadNextSequence()) {
            if (predFastaFile.ReadNextSequence()) {
            fmt::print("Mutation metrics calculated for {0}\n", refFastaFile.GetId());
            RunStatistics(metricName, refFastaFile.GetSequence(), predFastaFile.GetSequence(), posClass);
            }
            else {
                throw runtime_error("Reference fasta file contains more records than predicted file");
            }
        }
        if (predFastaFile.ReadNextSequence()) {
            throw runtime_error("Predicted fasta file contains more records than reference file");
        }
    }
    else {
        if (HasFastaEnding(reference) || HasFastaEnding(predicted)) {
            cerr << "WARNING: You are most likely (unintentionally) using the fasta FILENAME as a sequence itself. Please add -f flag to read the fasta file" << endl;
        }
        RunStatistics(metricName, reference, predicted, posClass);
    }
    return 0;
}

int main(int argc, char **argv) {
    CLI::App app{"Protein structure metric calculator"};

    bool useFasta{false};
    app.add_flag("-f,--fasta", useFasta, "Reference and predicted inputs are taken as fasta file paths");

    auto ss = app.add_subcommand("2d", "Calculate secondary structure metrics");

    string reference, predicted;
    string metricName{"all"};
    double lambda{1.0};
    bool zeroDelta{false};
    ss->add_option("-r,--reference", reference, "Reference sequence (Add -f for fasta files)")
        -> required();
    ss->add_option("-p,--predicted", predicted, "Predicted sequence (Add -f for fasta files)")
        -> required();
    ss->add_option("-m,--metric", metricName, "Name of the metric to calculate. Ignore to calculate all metrics.\nMetric Choices: Accuracy, SOV94, SOV99, SOVrefine, LooseOverlap, StrictOverlap");
    ss->add_option("-l,--lambda", lambda, "Adjustable scale parameter for SOVrefine");
    ss->add_flag("-z,--zeroDelta", zeroDelta, "This will omit the delta value (delta = 0)");

    auto mutational = app.add_subcommand("mutational", "Calculate mutational metrics");

    vector<string> references, predictions;
    string subMetric{""};
    mutational->add_option("-r,--reference", references, "Reference consensus and mutated sequences (Add -f for fasta files)")
        ->expected(2,2);
    mutational->add_option("-p,--predicted", predictions, "Predicted consensus and mutated sequences (Add -f for fasta files)")
        ->expected(2,2);
    mutational->add_option("-m,--metric", metricName, "Name of the metric to calculate.\nMetric Choices: Accuracy, Consistency, Precision")
        -> required();
    mutational->add_option("-l,--lambda", lambda, "Adjustable scale parameter for SOVrefine in MutationPrecision calculation");
    mutational->add_flag("-z,--zeroDelta", zeroDelta, "This will omit the delta value (delta = 0) in MutationPrecision calculation");
    mutational->add_option("-s,--subMetric", subMetric, "Sub-metric to utilize in the calculation of the mutational metric.\nChoices for consistency: Binary metrics. Choices for precision: 2d metrics");

    auto statistical = app.add_subcommand("binary", "Calculate two-class statistical metrics");

    char posClass;
    statistical->add_option("-r,--reference", reference, "Reference sequence (Add -f for fasta files)")
        -> required();
    statistical->add_option("-p,--predicted", predicted, "Predicted sequence (Add -f for fasta files)")
        -> required();
    statistical->add_option("-m,--metric", metricName, "Name of the metric to calculate. Ignore to calculate all metrics.\nMetric Choices: Accuracy, Sensitivity, Specificity, PPV, NPV, FPR, FNR, FOR, FDR, MCC");
    statistical->add_option("-c,--class,", posClass, "Positive class in your binary classification problem")
        -> required();

    CLI11_PARSE(app, argc, argv);

    try {
        transform(metricName.begin(), metricName.end(), metricName.begin(), [](unsigned char c){ return std::tolower(c); });
        if(app.got_subcommand(statistical)) {
            return StatisticalCalculator(useFasta, reference, predicted, metricName, posClass);
        }
        if(app.got_subcommand(mutational)) {
            if (metricName == "consistency" || metricName == "precision") {
                if (subMetric == "") {
                    cerr << "WARNING: A sub-metric can also be used. Use -s or --subMetric with your choice. Use --help for a list of choices" << endl;
                }
            }
            string consensusRef = references[0];
            string mutatedRef = references[1];
            string consensusPred = predictions[0];
            string mutatedPred = predictions[1];
            return MutationalCalculator(useFasta, consensusRef, mutatedRef, consensusPred, mutatedPred, metricName, lambda, zeroDelta, subMetric);
        }
        else if(app.got_subcommand(ss)){
            return DefaultCalculator(useFasta, reference, predicted, metricName, lambda, zeroDelta);
        }
        else {
            throw runtime_error("Please use one of the available subcommands");
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}