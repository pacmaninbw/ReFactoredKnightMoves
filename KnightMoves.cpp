/*
 * KnightMoves.cpp
 *
 *  Created on: Mar 17, 2016
 *	  Author: pacmaninbw
 */

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cctype>
#include "KnightMoves.h"
#include "TestData.h"
#include "KnightMovesImplementation.h"
#include "KMBoardDimensionConstants.h"

bool EnableShowPaths(void)
{
    std::cout << "\nDo you want to show all the resulting paths? ('y' or 'n')\n";
    char YesOrNo;
    std::cin >> YesOrNo;
    return (std::tolower(YesOrNo) == 'y');
}

double Average(std::vector<double> TestTimes)
{
    double AverageTestTime = 0.0;
    double SumOfTestTimes = 0.0;
    int CountOfTestTimes = 0;

    std::cout << "\n";
    for (auto TestTimesIter : TestTimes)
    {
        SumOfTestTimes += TestTimesIter;
        CountOfTestTimes++;
        std::cout << TestTimesIter << " ";
    }
    std::cout <<  "SumOfTestTimes = " << SumOfTestTimes << " CountOfTestTimes = " << CountOfTestTimes << "\n";

    if (CountOfTestTimes) { // Prevent division by zero.
        AverageTestTime = SumOfTestTimes / static_cast<double>(CountOfTestTimes);
    }

    return AverageTestTime;
}

void OutputOverAllStatistics(std::vector<double> TestTimes)
{
    if (TestTimes.size() < 1) {
        std::cout << "No test times to run statistics on!" << std::endl;
        return;
    }

    std::sort(TestTimes.begin(), TestTimes.end());
    double average = Average(TestTimes);
    std::cout << "\n" << "Overall Results" << "\n";
    std::cout << "The average execution time is " << average << " seconds" << "\n";
    std::cout << "The median execution time is " << TestTimes[TestTimes.size()/2] << " seconds" << "\n";
    std::cout << "The longest execution time is " << TestTimes[TestTimes.size()-1] << " seconds" << "\n";
    std::cout << "The shortest execution time is " << TestTimes[0] << " seconds" << std::endl;
}

double ExecutionLoop(KMBaseData UserInputData, bool ShowPaths=false)
{
    KnightMovesImplementation KnightPathFinder(UserInputData);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    KMOutputData OutputData = KnightPathFinder.CalculatePaths();
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    double ElapsedTimeForOutPut = elapsed_seconds.count();

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << ElapsedTimeForOutPut << std::endl << std::endl << std:: endl;
    // Don't include output of results in elapsed time calculation
    OutputData.ShowPathData(ShowPaths);
    OutputData.ShowResults();

    return ElapsedTimeForOutPut;
}

int main(int argc, char *argv[])
{
    int status = 0;
    bool ShowPaths = false;
    KMTestData TestData;
    TestCaseList TestCases = TestData.LetUserSelectTestCases();

    if (TestCases.empty())
    {
        return status;
    }

    ShowPaths = EnableShowPaths();

    try {
        std::vector<double> TestTimes;

        for (auto TestCase: TestCases) {
            TestTimes.push_back(ExecutionLoop(TestCase, ShowPaths));
        }
        OutputOverAllStatistics(TestTimes);

        return status;
    }
    catch(std::runtime_error &e) {
        std::cerr << "A fatal error occurred in KnightMoves: ";
        std::cerr << e.what()  << std::endl;
        status = 1;
    }
    catch(std::runtime_error *e) {
        std::cerr << "A fatal error occurred in KnightMoves: ";
        std::cerr << e->what()  << std::endl;
        status = 1;
    }
    catch(...) {
        std::cerr << "An unknown fatal error occurred in KnightMoves." << std::endl;
        status = 1;
    }
    return status;
}
