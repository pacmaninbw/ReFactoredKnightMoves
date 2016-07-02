/*
 * KMMoveFilters.h
 *
 *  Created on: Jun 20, 2016
 *      Author: pacmaninbw
 *
 *      This class provides all the possible Knight moves for a specified location
 *      on the chess board. In the center of the chess board there are 8 possible
 *      moves. In the middle of the edge on the chess board there are 4 possible
 *      moves. In a corner of the chess board there are 2 possible moves. The
 *      location on the board provides the first filter.
 *      Slicing is used to allow the program to complete in a reasonable finite
 *      amount of time. The slicing method can be varied, the default slicing
 *      method is the knight can't return to any row or column it has previously
 *      visited. The slicing is the second filter.
 */

#ifndef KMMOVEFILTERS_H_
#define KMMOVEFILTERS_H_

#include <vector>
#include "KMMethodLimitations.h"
#include "KMMove.h"

class KMMoveFilters {
private:
    std::vector<KMBoardLocation> m_VisitedLocations;
    std::vector<unsigned int> m_VisitedRows;
    std::vector<unsigned int> m_VisitedColumns;
    unsigned int m_SingleSideBoardDimension;
    KnightMovesMethodLimitations m_PathLimitations;
    static const KMRandomAccessMoveCollection AllPossibleMoves;
    // The 8 possible moves the knight can make.
    static KMMove Left1Up2;
    static KMMove Left2Up1;
    static KMMove Left2Down1;
    static KMMove Left1Down2;
    static KMMove Right1Up2;
    static KMMove Right2Up1;
    static KMMove Right2Down1;
    static KMMove Right1Down2;

protected:
    bool IsNotPreviouslyVisited(KMMove Move) const { return IsNotPreviouslyVisited(Move.GetNextLocation()); };
    bool IsNotPreviouslyVisited(KMBoardLocation Destination) const;

public:
    KMMoveFilters();
    void ResetFilters(KMBoardLocation Origin, unsigned int BoardDimension, KnightMovesMethodLimitations SlicingMethod);
    virtual ~KMMoveFilters() = default;
    void PushVisited(KMBoardLocation Location);
    void PopVisited();
    KMRandomAccessMoveCollection GetPossibleMoves(const KMBoardLocation CurrentLocation) const;
};

#endif /* KMMOVEFILTERS_H_ */
