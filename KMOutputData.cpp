/*
 * KMOutputData.cpp
 *
 *  Created on: Mar 19, 2016
 *  Updated June 20, 2016
 *      Author: pacmaninbw
 */

#include <vector>
#include <algorithm>
#include <functional>
#include "KMOutputData.h"

KMOutputData::KMOutputData()
 : m_BoardDimension{0}, m_AttemptedPaths{0}, m_LimitationsOnMoves{DenyByPreviousRowOrColumn}, m_ShowPathData{false}
{
}

void KMOutputData::ShowStats()
{

	std::vector<double> PathLengths;
	for (auto PathsIter : m_PathRecords)
	{
		PathLengths.push_back(static_cast<double>(PathsIter.GetLength()));
	}

	std::cout << "The average path length is " << Average(PathLengths) << std::endl;
	std::nth_element(PathLengths.begin(), PathLengths.begin() + PathLengths.size()/2, PathLengths.end());
	std::cout << "The median path length is " << PathLengths[PathLengths.size()/2] << std::endl;
	std::nth_element(PathLengths.begin(), PathLengths.begin()+1, PathLengths.end(), std::greater<int>());
	std::cout << "The longest path is " << PathLengths[0] << " moves" << std::endl;
	std::nth_element(PathLengths.begin(), PathLengths.begin()+1, PathLengths.end(), std::less<int>());
	std::cout << "The shortest path is " << PathLengths[0] << " moves" << std::endl;
}

double KMOutputData::Average(std::vector<double> PathLengths)
{
	double AverageLength = 0.0;

	for (auto PathLenthsIter : PathLengths)
	{
		AverageLength += PathLenthsIter;
	}

	AverageLength = AverageLength / static_cast<double>(PathLengths.size());

	return AverageLength;
}

void KMOutputData::ShowResults()
{
	std::cout << "The point of origin for all path searches was " << m_Origin << std::endl;
	std::cout << "The destination point for all path searches was " << m_Destination << std::endl;
	std::cout << "The number of squares on each edge of the board is " << m_BoardDimension << std::endl;
	OutputSlicingMethodlogy();
	std::cout << "There are " << m_PathRecords.size() << " Resulting Paths" << std::endl;
	std::cout << "There were " << m_AttemptedPaths << " attempted paths" << std::endl;
	ShowStats();

	if (!m_ShowPathData) {
		for (int i = 0; i < 25; i++) std::cout << "-";
		std::cout << std::endl << std::endl;
		return;
	}
	std::cout << std::endl << std::endl << std::endl << "Here is the listing of the paths" << std::endl << std::endl;


	for (auto CurrentPath : m_PathRecords)
	{
		for (int i = 0; i < 25; i++) std::cout << "-";
		std::cout << std::endl << std::endl;
		std::cout << CurrentPath << std::endl;
	}

}

void KMOutputData::OutputSlicingMethodlogy()
{
	switch (m_LimitationsOnMoves) {
	default :
		throw std::runtime_error("KnightMovesTIO::OutputSlicingMethodlogy : Unknown type of Path Limitation.");
	case DenyByPreviousLocation :
		std::cout << "The slicing methodology used to further limit searches was no repeat visits to squares on the board." << std::endl;
		break;
	case DenyByPreviousRowOrColumn:
		std::cout << "The slicing methodology used to further limit searches was no repeat visits to any rows or columns." << std::endl;
		break;
	}

}

