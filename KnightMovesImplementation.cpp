/*
 * KnightMovesImplementation.cpp
 *
 *  Created on: Mar 18, 2016
 *  Modified on: June 21, 2016
 *  Commented on: June 24, 2016
 *      Author: pacmaninbw
 *
 *      This class implements the search for all possible paths for a Knight
 *      on a chess board from one particular square on the board to another
 *      particular square on the board.
 *
 *      The current implementation is a Recursive Breadth First Search. Conceptually
 *      the algorithm implements a B+ tree with a maximum of 8 possible branches
 *      at each level. The root of the tree is the point of origin. A particular
 *      path terminates in a leaf. A leaf is the result of either reaching the
 *      destination, or reaching a point where there are no more branches to
 *      traverse.
 *
 *      The m_Path variable is used as a stack within the search.
 *
 *      The public interface CalculatePaths establishes the root and creates
 *      the first level of branching. The protected interface CalculatePath
 *      performs the recursive depth first search, however, the
 *      m_MoveFilters.GetPossibleMoves() function it calls performs a breadth
 *      first search of the current level.
 *
 */

#include "KnightMoves.h"
#include "KnightMovesImplementation.h"
#include "KMBoardDimensionConstants.h"

KnightMovesImplementation::KnightMovesImplementation(KMBaseData UserInputData)
 : m_SingleSideBoardDimension{UserInputData.m_DimensionOneSide},
   m_PathLimitations{UserInputData.m_LimitationsOnMoves}
{
	InitPointOfOrigin(UserInputData);
	InitDestination(UserInputData);
	m_MoveFilters.ResetFilters(static_cast<unsigned int>(UserInputData.m_DimensionOneSide), UserInputData.m_LimitationsOnMoves);
	m_Results.SetPointOfOrigin(m_PointOfOrigin);
	m_Results.SetDestination(m_Destination);
	m_Results.SetBoardDimension(m_SingleSideBoardDimension);
	m_Results.SetSlicingMethod(m_PathLimitations);
}

void KnightMovesImplementation::InitPointOfOrigin(KMBaseData UserInputData)
{
	m_PointOfOrigin.SetRow(UserInputData.m_StartRow);
	m_PointOfOrigin.SetColumn(UserInputData.m_StartColumn);
	m_PointOfOrigin.SetName(UserInputData.m_StartName);
	m_PointOfOrigin.SetBoardDimension(m_SingleSideBoardDimension);
}

void KnightMovesImplementation::InitDestination(KMBaseData UserInputData)
{
	m_Destination.SetRow(UserInputData.m_TargetRow);
	m_Destination.SetColumn(UserInputData.m_TargetColumn);
	m_Destination.SetName(UserInputData.m_TargetName);
	m_Destination.SetBoardDimension(m_SingleSideBoardDimension);
}

KMOutputData KnightMovesImplementation::CalculatePaths()
{
	KMRandomAccessMoveCollection PossibleFirstMoves = m_MoveFilters.GetPossibleMoves(m_PointOfOrigin);

	if (PossibleFirstMoves.empty())
	{
		std::cerr << "No Possible Moves in KnightMovesImplementation::CalculatePaths" << std::endl;
	}
	else
	{
		for (auto CurrentMoveIter : PossibleFirstMoves)
		{
			KMMove CurrentMove = CurrentMoveIter;
			CurrentMove.SetOriginCalculateDestination(m_PointOfOrigin);
			if (CurrentMove.IsValid()) {
				/**
				 * This might be a good place to improve performance by
				 * using multiple threads.
				 */
				CalculatePath(CurrentMove);
			}
		}
	}
	return m_Results;
}

bool KnightMovesImplementation::CalculatePath(KMMove CurrentMove)
{
	bool CompletedSearch = false;
	KMBoardLocation CurrentLocation = CurrentMove.GetNextLocation();
	m_Path.AddMoveToPath(CurrentMove);
	m_MoveFilters.PushVisited(CurrentLocation);

	if (CurrentLocation == m_Destination)
	{
		m_Results.AddPath(m_Path);
		CompletedSearch =  true;
		m_Results.IncrementAttemptedPaths();
	}
	else
	{
		if (CurrentMove.IsValid())
		{
			KMRandomAccessMoveCollection PossibleMoves = m_MoveFilters.GetPossibleMoves(CurrentLocation);
			if (!PossibleMoves.empty())
			{
				for (auto NextMove : PossibleMoves)
				{
					CalculatePath(NextMove);
				}
			}
			else
			{
				// No more moves to test, record the attempted path
				m_Results.IncrementAttemptedPaths();
			}
		}
		else
		{
			// There is a logic error if we get here.
			std::cerr << "In KnightMovesImplementation::CalculatePath CurrentMove Not Valid" << std::endl;
		}
	}

	m_Path.RemoveLastMove();
	m_MoveFilters.PopVisited();
	return CompletedSearch;
}
