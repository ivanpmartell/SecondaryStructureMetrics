#include <gtest/gtest.h>
#include <Accuracy.hpp>
#include <Sov94.hpp>
#include <LooseOverlap.hpp>
#include <StrictOverlap.hpp>
#include <Sov99.hpp>
#include <SovRefine.hpp>

static bool compare(const double value1, const double value2, const int precision)
{
    return std::abs(value1 - value2) < 0.0055;
}

TEST(Rost94, AccuracyTestFig3a) {
  string refSequence_6dfr  = "....HHHHHHHHHHH....EEEEHHHHHHH.........EEEE..........EEE..HHHHHH..........EEE...HHHHHHHHHH..EEEEEEE..............HHHEEEEEEEEE.........EEEEEEEE.";
  string predSequence_3dfr = "....HHHHHHHHH.....EEEEEHHHHHH.........EEEEE...........EEE..HHHHHHHHHH.....EEE...HHHHHH.HHH..EEEEEEE.......EE.....HHHEEEEEEEEEE....HHH.EEEEEEEE.";
  Accuracy acc = Accuracy("Accuracy", refSequence_6dfr, predSequence_3dfr, nullptr);
  EXPECT_TRUE(compare(acc.CalculateAllClasses(), 0.86, 2));
  EXPECT_TRUE(compare(acc.CalculateOneClass('H'), 0.87, 2));
  EXPECT_TRUE(compare(acc.CalculateOneClass('E'), 0.97, 2));
  EXPECT_TRUE(compare(acc.CalculateOneClass('.'), 0.79, 2));
}

TEST(Rost94, Sov94TestFig3a) {
  string refSequence_6dfr  = "....HHHHHHHHHHH....EEEEHHHHHHH.........EEEE..........EEE..HHHHHH..........EEE...HHHHHHHHHH..EEEEEEE..............HHHEEEEEEEEE.........EEEEEEEE.";
  string predSequence_3dfr = "....HHHHHHHHH.....EEEEEHHHHHH.........EEEEE...........EEE..HHHHHHHHHH.....EEE...HHHHHH.HHH..EEEEEEE.......EE.....HHHEEEEEEEEEE....HHH.EEEEEEEE.";
  Sov94 sov94 = Sov94("Sov94", refSequence_6dfr, predSequence_3dfr, false, true, nullptr);
  EXPECT_TRUE(compare(sov94.CalculateAllClasses(), 0.97, 2));
  EXPECT_TRUE(compare(sov94.CalculateOneClass('H'), 0.96, 2));
  EXPECT_TRUE(compare(sov94.CalculateOneClass('E'), 0.98, 2));
  EXPECT_TRUE(compare(sov94.CalculateOneClass('.'), 0.97, 2));
}

TEST(Rost94, AccuracyTestFig3b) {
    string refSequence_ifdl  = "....HHHHHHHHHH...........HHHHHHHHHHH......EEEE...EEEE....EE.....................HHHHH....HHHHHHHHHHHH...HHHH...HHHH.....HHHHH.....";
    string predSequence_21z2 = "....HHHHHHHHHH...........HHHHHHHHHH.......EEE.....EEE....EE.....................HHH........HHHHHHHH.....HHHH.HHHHHH......HHH......";
    Accuracy acc = Accuracy("Accuracy", refSequence_ifdl, predSequence_21z2, nullptr);
    EXPECT_TRUE(compare(acc.CalculateAllClasses(), 0.9, 2));
    EXPECT_TRUE(compare(acc.CalculateOneClass('H'), 0.82, 2));
  EXPECT_TRUE(compare(acc.CalculateOneClass('E'), 0.80, 2));
  EXPECT_TRUE(compare(acc.CalculateOneClass('.'), 0.97, 2));
}

TEST(Rost94, Sov94TestFig3b) {
    string refSequence_ifdl  = "....HHHHHHHHHH...........HHHHHHHHHHH......EEEE...EEEE....EE.....................HHHHH....HHHHHHHHHHHH...HHHH...HHHH.....HHHHH.....";
    string predSequence_21z2 = "....HHHHHHHHHH...........HHHHHHHHHH.......EEE.....EEE....EE.....................HHH........HHHHHHHH.....HHHH.HHHHHH......HHH......";
    Sov94 sov94 = Sov94("Sov94", refSequence_ifdl, predSequence_21z2, false, true, nullptr);
    EXPECT_TRUE(compare(sov94.CalculateAllClasses(), 0.98, 2));
    EXPECT_TRUE(compare(sov94.CalculateOneClass('H'), 1.0, 2));
  EXPECT_TRUE(compare(sov94.CalculateOneClass('E'), 1.0, 2));
  EXPECT_TRUE(compare(sov94.CalculateOneClass('.'), 0.95, 2));
}

TEST(Rost94, Sov94TestFigA1a) {
    string refSequence_observer  = ".HHHHH...";
    string predSequence_1        = "...HHHHHH";
    string predSequence_2        = ".HHHH....";
    string predSequence_3        = "HHH.HH...";
    Sov94 sov94_1 = Sov94("Sov94", refSequence_observer, predSequence_1, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_1.CalculateOneClass('H'), 0.38, 2));
    Sov94 sov94_2 = Sov94("Sov94", refSequence_observer, predSequence_2, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_2.CalculateOneClass('H'), 0.80, 2));
    Sov94 sov94_3 = Sov94("Sov94", refSequence_observer, predSequence_3, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_3.CalculateOneClass('H'), 0.73, 2));
}

TEST(Rost94, LooseOverlapTestFigA1a) {
    string refSequence_observer  = ".HHHHH...";
    string predSequence_1        = "...HHHHHH";
    string predSequence_2        = ".HHHH....";
    string predSequence_3        = "HHH.HH...";
    LooseOverlap looseOv_1 = LooseOverlap("LooseOverlap", refSequence_observer, predSequence_1, nullptr);
    EXPECT_TRUE(compare(looseOv_1.CalculateOneClass('H'), 1.0, 2));
    LooseOverlap looseOv_2 = LooseOverlap("LooseOverlap", refSequence_observer, predSequence_2, nullptr);
    EXPECT_TRUE(compare(looseOv_2.CalculateOneClass('H'), 1.0, 2));
    LooseOverlap looseOv_3 = LooseOverlap("LooseOverlap", refSequence_observer, predSequence_3, nullptr);
    EXPECT_TRUE(compare(looseOv_3.CalculateOneClass('H'), 0.0, 2));
}

TEST(Rost94, StrictOverlapTestFigA1a) {
    string refSequence_observer  = ".HHHHH...";
    string predSequence_1        = "...HHHHHH";
    string predSequence_2        = ".HHHH....";
    string predSequence_3        = "HHH.HH...";
    StrictOverlap strictOv_1 = StrictOverlap("StrictOverlap", refSequence_observer, predSequence_1, false, nullptr);
    EXPECT_TRUE(compare(strictOv_1.CalculateOneClass('H'), 0.0, 2));
    StrictOverlap strictOv_2 = StrictOverlap("StrictOverlap", refSequence_observer, predSequence_2, false, nullptr);
    EXPECT_TRUE(compare(strictOv_2.CalculateOneClass('H'), 1.0, 2));
    StrictOverlap strictOv_3 = StrictOverlap("StrictOverlap", refSequence_observer, predSequence_3, false, nullptr);
    EXPECT_TRUE(compare(strictOv_3.CalculateOneClass('H'), 0.0, 2));
}

TEST(Rost94, StrictOverlapTestFigA1b) {
    string refSequence_pairs  = "..HHHHH.";
    string predSequence_pair1 = ".HHHHH..";
    string predSequence_pair2 = "...HHHHH";
    string predSequence_pair3 = ".HHHHHH.";
    string predSequence_pair4 = "..HHHHHH";
    string predSequence_pair5 = "..HHHH..";
    string predSequence_pair6 = "...HHHH.";
    StrictOverlap strictOv_1 = StrictOverlap("StrictOverlap", refSequence_pairs, predSequence_pair1, false, nullptr);
    EXPECT_TRUE(compare(strictOv_1.CalculateOneClass('H'), 1.0, 2));
    StrictOverlap strictOv_2 = StrictOverlap("StrictOverlap", refSequence_pairs, predSequence_pair2, false, nullptr);
    EXPECT_TRUE(compare(strictOv_2.CalculateOneClass('H'), 1.0, 2));
    StrictOverlap strictOv_3 = StrictOverlap("StrictOverlap", refSequence_pairs, predSequence_pair3, false, nullptr);
    EXPECT_TRUE(compare(strictOv_3.CalculateOneClass('H'), 1.0, 2));
    StrictOverlap strictOv_4 = StrictOverlap("StrictOverlap", refSequence_pairs, predSequence_pair4, false, nullptr);
    EXPECT_TRUE(compare(strictOv_4.CalculateOneClass('H'), 1.0, 2));
    StrictOverlap strictOv_5 = StrictOverlap("StrictOverlap", refSequence_pairs, predSequence_pair5, false, nullptr);
    EXPECT_TRUE(compare(strictOv_5.CalculateOneClass('H'), 1.0, 2));
    StrictOverlap strictOv_6 = StrictOverlap("StrictOverlap", refSequence_pairs, predSequence_pair6, false, nullptr);
    EXPECT_TRUE(compare(strictOv_6.CalculateOneClass('H'), 1.0, 2));
}

TEST(Zemla99, Sov99TestFig1) {
    string refObserved  = "CCEEECCCCCCEEEEEECCC";
    string predSequence = "CCCCCCCEEEEECCCEECCC";
    Sov99 sov99 = Sov99("Sov99", refObserved, predSequence, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99.CalculateOneClass('E'), 0.28, 2));
}

TEST(Zemla99, Sov99TestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CCCHHHHHCCCC";
    string predSequence3 = "CHHHCHHHCHHC";
    string predSequence4 = "CHHCCHHHHHCC";
    string predSequence5 = "CCCHHHHHHCCC";
    Sov99 sov99_1 = Sov99("Sov99", refObserved, predSequence1, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_1.CalculateAllClasses(), 0.125, 2));
    Sov99 sov99_2 = Sov99("Sov99", refObserved, predSequence2, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_2.CalculateAllClasses(), 0.632, 2));
    Sov99 sov99_3 = Sov99("Sov99", refObserved, predSequence3, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_3.CalculateAllClasses(), 0.406, 2));
    Sov99 sov99_4 = Sov99("Sov99", refObserved, predSequence4, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_4.CalculateAllClasses(), 0.523, 2));
    Sov99 sov99_5 = Sov99("Sov99", refObserved, predSequence5, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_5.CalculateAllClasses(), 0.806, 2));
}

TEST(Zemla99, Sov99ZeroDeltaTestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CCCHHHHHCCCC";
    string predSequence3 = "CHHHCHHHCHHC";
    string predSequence4 = "CHHCCHHHHHCC";
    string predSequence5 = "CCCHHHHHHCCC";
    Sov99 sov99_1 = Sov99("Sov99", refObserved, predSequence1, true, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_1.CalculateAllClasses(), 0.125, 2));
    Sov99 sov99_2 = Sov99("Sov99", refObserved, predSequence2, true, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_2.CalculateAllClasses(), 0.465, 2));
    Sov99 sov99_3 = Sov99("Sov99", refObserved, predSequence3, true, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_3.CalculateAllClasses(), 0.313, 2));
    Sov99 sov99_4 = Sov99("Sov99", refObserved, predSequence4, true, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_4.CalculateAllClasses(), 0.386, 2));
    Sov99 sov99_5 = Sov99("Sov99", refObserved, predSequence5, true, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_5.CalculateAllClasses(), 0.556, 2));
}

TEST(Zemla99, Sov94TestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CCCHHHHHCCCC";
    string predSequence3 = "CHHHCHHHCHHC";
    string predSequence4 = "CHHCCHHHHHCC";
    string predSequence5 = "CCCHHHHHHCCC";
    Sov94 sov94_1 = Sov94("Sov94", refObserved, predSequence1, false, false, nullptr);
    EXPECT_TRUE(compare(sov94_1.CalculateAllClasses(), 0.958, 2));
    Sov94 sov94_2 = Sov94("Sov94", refObserved, predSequence2, false, false, nullptr);
    EXPECT_TRUE(compare(sov94_2.CalculateAllClasses(), 0.882, 2));
    Sov94 sov94_3 = Sov94("Sov94", refObserved, predSequence3, false, false, nullptr);
    EXPECT_TRUE(compare(sov94_3.CalculateAllClasses(), 1.5, 2));
    Sov94 sov94_4 = Sov94("Sov94", refObserved, predSequence4, false, false, nullptr);
    EXPECT_TRUE(compare(sov94_4.CalculateAllClasses(), 1.292, 2));
    Sov94 sov94_5 = Sov94("Sov94", refObserved, predSequence5, false, false, nullptr);
    EXPECT_TRUE(compare(sov94_5.CalculateAllClasses(), 0.889, 2));
}

TEST(Zemla99, Sov94ZeroDeltaTestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CCCHHHHHCCCC";
    string predSequence3 = "CHHHCHHHCHHC";
    string predSequence4 = "CHHCCHHHHHCC";
    string predSequence5 = "CCCHHHHHHCCC";
    Sov94 sov94_1 = Sov94("Sov94", refObserved, predSequence1, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_1.CalculateAllClasses(), 0.542, 2));
    Sov94 sov94_2 = Sov94("Sov94", refObserved, predSequence2, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_2.CalculateAllClasses(), 0.465, 2));
    Sov94 sov94_3 = Sov94("Sov94", refObserved, predSequence3, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_3.CalculateAllClasses(), 0.833, 2));
    Sov94 sov94_4 = Sov94("Sov94", refObserved, predSequence4, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_4.CalculateAllClasses(), 0.708, 2));
    Sov94 sov94_5 = Sov94("Sov94", refObserved, predSequence5, true, false, nullptr);
    EXPECT_TRUE(compare(sov94_5.CalculateAllClasses(), 0.556, 2));
}

TEST(Zemla99, AccuracyTestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CCCHHHHHCCCC";
    string predSequence3 = "CHHHCHHHCHHC";
    string predSequence4 = "CHHCCHHHHHCC";
    string predSequence5 = "CCCHHHHHHCCC";
    Accuracy acc_1 = Accuracy("Q3", refObserved, predSequence1, nullptr);
    EXPECT_TRUE(compare(acc_1.CalculateAllClasses(), 0.583, 2));
    Accuracy acc_2 = Accuracy("Q3", refObserved, predSequence2, nullptr);
    EXPECT_TRUE(compare(acc_2.CalculateAllClasses(), 0.583, 2));
    Accuracy acc_3 = Accuracy("Q3", refObserved, predSequence3, nullptr);
    EXPECT_TRUE(compare(acc_3.CalculateAllClasses(), 0.833, 2));
    Accuracy acc_4 = Accuracy("Q3", refObserved, predSequence4, nullptr);
    EXPECT_TRUE(compare(acc_4.CalculateAllClasses(), 0.75, 2));
    Accuracy acc_5 = Accuracy("Q3", refObserved, predSequence5, nullptr);
    EXPECT_TRUE(compare(acc_5.CalculateAllClasses(), 0.667, 2));
}

TEST(Liu18, AccuracyTestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CHHHCHHHCHHC";
    string predSequence3 = "CHHCCHHHHHCC";
    string predSequence4 = "CCCHHHHCCCCC";
    string predSequence5 = "CCCHHHHHCCCC";
    string predSequence6 = "CCCHHHHHHCCC";
    string predSequence7 = "CCCHHHHHHHCC";
    string predSequence8 = "CCCHHHHHHHHC";
    Accuracy acc_1 = Accuracy("Q3", refObserved, predSequence1, nullptr);
    EXPECT_TRUE(compare(acc_1.CalculateAllClasses(), 0.583, 2));
    Accuracy acc_2 = Accuracy("Q3", refObserved, predSequence2, nullptr);
    EXPECT_TRUE(compare(acc_2.CalculateAllClasses(), 0.833, 2));
    Accuracy acc_3 = Accuracy("Q3", refObserved, predSequence3, nullptr);
    EXPECT_TRUE(compare(acc_3.CalculateAllClasses(), 0.75, 2));
    Accuracy acc_4 = Accuracy("Q3", refObserved, predSequence4, nullptr);
    EXPECT_TRUE(compare(acc_4.CalculateAllClasses(), 0.50, 2));
    Accuracy acc_5 = Accuracy("Q3", refObserved, predSequence5, nullptr);
    EXPECT_TRUE(compare(acc_5.CalculateAllClasses(), 0.583, 2));
    Accuracy acc_6 = Accuracy("Q3", refObserved, predSequence6, nullptr);
    EXPECT_TRUE(compare(acc_6.CalculateAllClasses(), 0.667, 2));
    Accuracy acc_7 = Accuracy("Q3", refObserved, predSequence7, nullptr);
    EXPECT_TRUE(compare(acc_7.CalculateAllClasses(), 0.75, 2));
    Accuracy acc_8 = Accuracy("Q3", refObserved, predSequence8, nullptr);
    EXPECT_TRUE(compare(acc_8.CalculateAllClasses(), 0.833, 2));
}

TEST(Liu18, Sov99TestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CHHHCHHHCHHC";
    string predSequence3 = "CHHCCHHHHHCC";
    string predSequence4 = "CCCHHHHCCCCC";
    string predSequence5 = "CCCHHHHHCCCC";
    string predSequence6 = "CCCHHHHHHCCC";
    string predSequence7 = "CCCHHHHHHHCC";
    string predSequence8 = "CCCHHHHHHHHC";
    Sov99 sov99_1 = Sov99("Q3", refObserved, predSequence1, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_1.CalculateAllClasses(), 0.125, 2));
    Sov99 sov99_2 = Sov99("Q3", refObserved, predSequence2, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_2.CalculateAllClasses(), 0.406, 2));
    Sov99 sov99_3 = Sov99("Q3", refObserved, predSequence3, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_3.CalculateAllClasses(), 0.523, 2));
    Sov99 sov99_4 = Sov99("Q3", refObserved, predSequence4, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_4.CalculateAllClasses(), 0.544, 2));
    Sov99 sov99_5 = Sov99("Q3", refObserved, predSequence5, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_5.CalculateAllClasses(), 0.632, 2));
    Sov99 sov99_6 = Sov99("Q3", refObserved, predSequence6, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_6.CalculateAllClasses(), 0.806, 2));
    Sov99 sov99_7 = Sov99("Q3", refObserved, predSequence7, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_7.CalculateAllClasses(), 0.903, 2));
    Sov99 sov99_8 = Sov99("Q3", refObserved, predSequence8, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_8.CalculateAllClasses(), 0.944, 2));
}

TEST(Liu18, SovRefineTestTable1) {
    string refObserved   = "CHHHHHHHHHHC";
    string predSequence1 = "CHCHCHCHCHCC";
    string predSequence2 = "CHHHCHHHCHHC";
    string predSequence3 = "CHHCCHHHHHCC";
    string predSequence4 = "CCCHHHHCCCCC";
    string predSequence5 = "CCCHHHHHCCCC";
    string predSequence6 = "CCCHHHHHHCCC";
    string predSequence7 = "CCCHHHHHHHCC";
    string predSequence8 = "CCCHHHHHHHHC";
    SovRefine sovRefine_1 = SovRefine("Q3", refObserved, predSequence1, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_1.CalculateAllClasses(), 0.149, 2));
    SovRefine sovRefine_2 = SovRefine("Q3", refObserved, predSequence2, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_2.CalculateAllClasses(), 0.371, 2));
    SovRefine sovRefine_3 = SovRefine("Q3", refObserved, predSequence3, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_3.CalculateAllClasses(), 0.464, 2));
    SovRefine sovRefine_4 = SovRefine("Q3", refObserved, predSequence4, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_4.CalculateAllClasses(), 0.459, 2));
    SovRefine sovRefine_5 = SovRefine("Q3", refObserved, predSequence5, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_5.CalculateAllClasses(), 0.567, 2));
    SovRefine sovRefine_6 = SovRefine("Q3", refObserved, predSequence6, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_6.CalculateAllClasses(), 0.678, 2));
    SovRefine sovRefine_7 = SovRefine("Q3", refObserved, predSequence7, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_7.CalculateAllClasses(), 0.797, 2));
    SovRefine sovRefine_8 = SovRefine("Q3", refObserved, predSequence8, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_8.CalculateAllClasses(), 0.937, 2));
}

TEST(Liu18, AccuracyTestTable2) {
    string refSequence   = "AABBBBBBCCCCCCDD";
    string predSequence1 = "AAAAABBBCCCDDDDD";
    string predSequence2 = "AAAABBBBCCCCDDDD";
    string predSequence3 = "AAABBBBBCCCCCDDD";
    string predSequence4 = "AABBBBBBCCCCCDDD";
    Accuracy acc_1 = Accuracy("Q4", refSequence, predSequence1, nullptr);
    EXPECT_TRUE(compare(acc_1.CalculateAllClasses(), 0.625, 2));
    Accuracy acc_2 = Accuracy("Q4", refSequence, predSequence2, nullptr);
    EXPECT_TRUE(compare(acc_2.CalculateAllClasses(), 0.75, 2));
    Accuracy acc_3 = Accuracy("Q4", refSequence, predSequence3, nullptr);
    EXPECT_TRUE(compare(acc_3.CalculateAllClasses(), 0.875, 2));
    Accuracy acc_4 = Accuracy("Q4", refSequence, predSequence4, nullptr);
    EXPECT_TRUE(compare(acc_4.CalculateAllClasses(), 0.938, 2));
}

TEST(Liu18, Sov99TestTable2) {
    string refSequence   = "AABBBBBBCCCCCCDD";
    string predSequence1 = "AAAAABBBCCCDDDDD";
    string predSequence2 = "AAAABBBBCCCCDDDD";
    string predSequence3 = "AAABBBBBCCCCCDDD";
    string predSequence4 = "AABBBBBBCCCCCDDD";
    Sov99 sov99_1 = Sov99("Sov99", refSequence, predSequence1, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_1.CalculateAllClasses(), 0.65, 2));
    Sov99 sov99_2 = Sov99("Sov99", refSequence, predSequence2, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_2.CalculateAllClasses(), 0.938, 2));
    Sov99 sov99_3 = Sov99("Sov99", refSequence, predSequence3, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_3.CalculateAllClasses(), 1.0, 2));
    Sov99 sov99_4 = Sov99("Sov99", refSequence, predSequence4, false, nullptr, nullptr);
    EXPECT_TRUE(compare(sov99_4.CalculateAllClasses(), 1.0, 2));
}

TEST(Liu18, SovRefineLambda1TestTable2) {
    string refSequence   = "AABBBBBBCCCCCCDD";
    string predSequence1 = "AAAAABBBCCCDDDDD";
    string predSequence2 = "AAAABBBBCCCCDDDD";
    string predSequence3 = "AAABBBBBCCCCCDDD";
    string predSequence4 = "AABBBBBBCCCCCDDD";
    SovRefine sovRefine_1 = SovRefine("SovRefine", refSequence, predSequence1, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_1.CalculateAllClasses(), 0.807, 2));
    SovRefine sovRefine_2 = SovRefine("SovRefine", refSequence, predSequence2, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_2.CalculateAllClasses(), 0.925, 2));
    SovRefine sovRefine_3 = SovRefine("SovRefine", refSequence, predSequence3, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_3.CalculateAllClasses(), 1.0, 2));
    SovRefine sovRefine_4 = SovRefine("SovRefine", refSequence, predSequence4, false, 1.0, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_4.CalculateAllClasses(), 1.0, 2));
}

TEST(Liu18, SovRefineLambda0_5TestTable2) {
    string refSequence   = "AABBBBBBCCCCCCDD";
    string predSequence1 = "AAAAABBBCCCDDDDD";
    string predSequence2 = "AAAABBBBCCCCDDDD";
    string predSequence3 = "AAABBBBBCCCCCDDD";
    string predSequence4 = "AABBBBBBCCCCCDDD";
    SovRefine sovRefine_1 = SovRefine("SovRefine", refSequence, predSequence1, false, 0.5, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_1.CalculateAllClasses(), 0.641, 2));
    SovRefine sovRefine_2 = SovRefine("SovRefine", refSequence, predSequence2, false, 0.5, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_2.CalculateAllClasses(), 0.85, 2));
    SovRefine sovRefine_3 = SovRefine("SovRefine", refSequence, predSequence3, false, 0.5, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_3.CalculateAllClasses(), 0.961, 2));
    SovRefine sovRefine_4 = SovRefine("SovRefine", refSequence, predSequence4, false, 0.5, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_4.CalculateAllClasses(), 0.981, 2));
}

TEST(Liu18, SovRefineLambda0_1TestTable2) {
    string refSequence   = "AABBBBBBCCCCCCDD";
    string predSequence1 = "AAAAABBBCCCDDDDD";
    string predSequence2 = "AAAABBBBCCCCDDDD";
    string predSequence3 = "AAABBBBBCCCCCDDD";
    string predSequence4 = "AABBBBBBCCCCCDDD";
    SovRefine sovRefine_1 = SovRefine("SovRefine", refSequence, predSequence1, false, 0.1, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_1.CalculateAllClasses(), 0.508, 2));
    SovRefine sovRefine_2 = SovRefine("SovRefine", refSequence, predSequence2, false, 0.1, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_2.CalculateAllClasses(), 0.67, 2));
    SovRefine sovRefine_3 = SovRefine("SovRefine", refSequence, predSequence3, false, 0.1, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_3.CalculateAllClasses(), 0.851, 2));
    SovRefine sovRefine_4 = SovRefine("SovRefine", refSequence, predSequence4, false, 0.1, nullptr, nullptr);
    EXPECT_TRUE(compare(sovRefine_4.CalculateAllClasses(), 0.925, 2));
}