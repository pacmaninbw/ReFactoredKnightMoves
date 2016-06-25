/*
 * KnightMovesImplementation.h
 *
 *  Created on: Mar 18, 2016
 *  Modified on: June 20, 2016
 *      Author: pacmaninbw
 *
 *      This class provides the search for all the paths a Knight on a chess
 *      board can take from the point of origin to the destination. It
 *      implements a modified Knights Tour. The classic knights tour problem
 *      is to visit every location on the chess board without returning to a
 *      previous location. That is a single path for the knight. This
 *      implementation returns all possible paths from point a to point b.
 *      The actual implementation is documented in the CPP file because it
 *      can be changed. This head file provides the public interface which
 *      should not be changed. The public interface may be moved to a
 *      super class in the future.
 */

#ifndef KNIGHTMOVESIMPLEMENTATION_H_
#define KNIGHTMOVESIMPLEMENTATION_H_

#include "KMPath.h"
#include "KMOutputData.h"
#include "KMMoveFilters.h"

class KnightMovesImplementation {
private:
	KMBoardLocation m_PointOfOrigin;
	KMBoardLocation m_Destination;
	unsigned int m_SingleSideBoardDimension;
	KnightMovesMethodLimitations m_PathLimitations;
	KMOutputData m_Results;
	KMMoveFilters m_MoveFilters;
	KMPath m_Path;

protected:
	bool CalculatePath(KMMove CurrentMove);		// Recursive function
	void InitPointOfOrigin(KMBaseData UserData);
	void InitDestination(KMBaseData UserData);

public:
	KnightMovesImplementation(KMBaseData UserData);
	virtual ~KnightMovesImplementation() = default;
	KMOutputData CalculatePaths();
};

#endif /* KNIGHTMOVESIMPLEMENTATION_H_ */
