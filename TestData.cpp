/*
 * TestData.cpp
 *
 *  Created on: Jun 29, 2016
 *      Author: pacmaninbw
 */

#include "KMBoardDimensionConstants.h"
#include "TestData.h"

KMTestData::KMTestData() {
    AllTestCases.push_back({1,3, "A3", 8,4, "H4", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({1,1, "A1", 8,8, "H8", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({1,8, "A8", 8,1, "H1", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({2,3, "B3", 8,4, "H4", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({2,3, "B3", 8,8, "H8", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({3,1, "C1", 8,4, "H4", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({3,1, "A3", 8,8, "H8", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({1,3, "A3", 2,5, "B5", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});    // Minimum should be one move
    AllTestCases.push_back({8,4, "H4", 1,3, "A3", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({4,4, "D4", 1,8, "A8", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({4,4, "D4", 5,6, "E6", DefaultBoardDimensionOnOneSide, DenyByPreviousRowOrColumn});
    AllTestCases.push_back({1,3, "A3", 2,5, "B5", MaximumBoardDimension/2, DenyByPreviousRowOrColumn});	// Minimum should be one move
    AllTestCases.push_back({1,3, "A3", 2,5, "B5", DefaultBoardDimensionOnOneSide, DenyByPreviousLocation});	// Minimum should be one move
    AllTestCases.push_back({1,3, "A3", 2,5, "B5", MaximumBoardDimension, DenyByPreviousRowOrColumn});	// Minimum should be one move
}

std::vector<KMBaseData> KMTestData::LetUserEnterTestCaseNumber()
{
    std::vector<KMBaseData> TestCases;
    int i = 1;
    size_t Choice = -1;

    std::cout << "Select the number of the test case you want to run or -1 to exit.\n";
    std::cout << "Test" << "\tStart" << "\tTarget" << "\tBoard" << "\tSlicing" << "\n";
    std::cout << "Case #" << "\tName" << "\tName" << "\tSize" << "\tMethod" << "\n";
    for (auto TestCase: AllTestCases) {
        std::cout << i << TestCase;
        i++;
    }
    std::cout << i << "\tAll of the above except for Test Cases where the Board Dimension is "
            << MaximumBoardDimension <<  " or Slicing Method is Can't return to previous location" << "\n";
    std::cout << ++i <<"\tAll of the above (Go get lunch)\n";

    std::cin >> Choice;

    if ((Choice > 0) && (Choice <= AllTestCases.size() + 2)) {
        if (Choice <= AllTestCases.size()) {
            TestCases.push_back(AllTestCases[Choice -1]);
        }
        else
        {
            if (Choice == (AllTestCases.size() + 1))
            { // Run all test cases that definitely execute in finite time.
                for (auto TestCase: AllTestCases)
                {
                    if ((TestCase.m_LimitationsOnMoves != DenyByPreviousLocation) &&
                            (TestCase.m_DimensionOneSide != MaximumBoardDimension))
                    {
                        TestCases.push_back(TestCase);
                    }
                }
            }
            else
            {
                TestCases = AllTestCases;
            }
        }
    }

    return TestCases;
}
