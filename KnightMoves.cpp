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
#include "KnightMoves.h"
#include "KnightMovesImplementation.h"
#include "KMBoardDimensionConstants.h"

double Average(std::vector<double> TestTimes)
{
	double AverageTestTime = 0.0;
	double SumOfTestTimes = 0.0;
	int CountOfTestTimes = 0;

	for (auto TestTimesIter : TestTimes)
	{
		SumOfTestTimes += TestTimesIter;
		CountOfTestTimes++;
	}

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

	std::cout << std::endl << "Overall Results" << std::endl;
	std::cout << "The average execution time is " << Average(TestTimes) << " seconds" << std::endl;
	std::nth_element(TestTimes.begin(), TestTimes.begin() + TestTimes.size()/2, TestTimes.end());
	std::cout << "The median execution time is " << TestTimes[TestTimes.size()/2] << " seconds" << std::endl;
	std::nth_element(TestTimes.begin(), TestTimes.begin()+1, TestTimes.end(), std::greater<int>());
	std::cout << "The longest execution time is " << TestTimes[0] << " seconds" << std::endl;
	std::nth_element(TestTimes.begin(), TestTimes.begin()+1, TestTimes.end(), std::less<int>());
	std::cout << "The shortest execution time is " << TestTimes[0] << " seconds" << std::endl;
}

double ExecutionLoop(KMBaseData UserInputData)
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
    OutputData.DontShowPathData();
    // OutputData.ShowPathData();
    OutputData.ShowResults();

    return ElapsedTimeForOutPut;
}

void InitTestData(std::vector<KMBaseData> &TestData)
{

	TestData.push_back({1,3,"A3",8,4,"H4",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({1,1,"A1",8,8,"H8",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({1,8,"A8",8,1,"H1",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({2,3,"B3",8,4,"H4",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({2,3,"B3",8,8,"H8",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({3,1,"C1",8,4,"H4",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({3,1,"A3",8,8,"H8",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({1,3,"A3",2,5,"B5",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});	// Minimum should be one move
	TestData.push_back({1,3,"A3",2,5,"B5",12,DenyByPreviousRowOrColumn});							// Minimum should be one move
//	TestData.push_back({1,3,"A3",2,5,"B5",MaximumBoardDimension,DenyByPreviousRowOrColumn});		// Minimum should be one move
//	TestData.push_back({1,3,"A3",2,5,"B5",MaximumBoardDimension,DenyByPreviousLocation});			// Minimum should be one move
	TestData.push_back({8,4,"H4",1,3,"A3",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({4,4,"D4",1,8,"A8",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
	TestData.push_back({4,4,"D4",5,6,"E6",DefaultBoardDimensionOnOneSide,DenyByPreviousRowOrColumn});
}

int main(int argc, char *argv[])
{
	int status = 0;

	std::vector<KMBaseData> TestData;
	std::vector<double> TestTimes;

	try {

		InitTestData(TestData);

		for (auto TestDataIter: TestData) {
			TestTimes.push_back(ExecutionLoop(TestDataIter));
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

