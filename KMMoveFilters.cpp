/*
 * KMMoveFilters.cpp
 *
 *  Created on: Jun 20, 2016
 *      Author: pacmaninbw
 */

#include <stdexcept>
#include <algorithm>
#include "KMBoardDimensionConstants.h"
#include "KMMoveFilters.h"

KMMoveFilters::KMMoveFilters()
 : m_SingleSideBoardDimension{DefaultBoardDimensionOnOneSide},
   m_PathLimitations{DenyByPreviousRowOrColumn}
{

}

const int Left1 = -1;
const int Left2 = -2;
const int Down1 = -1;
const int Down2 = -2;
const int Right1 = 1;
const int Right2 = 2;
const int Up1 = 1;
const int Up2 = 2;

KMMove KMMoveFilters::Left1Up2(Left1, Up2, DefaultBoardDimensionOnOneSide);
KMMove KMMoveFilters::Left2Up1(Left2, Up1, DefaultBoardDimensionOnOneSide);
KMMove KMMoveFilters::Left2Down1(Left2, Down1, DefaultBoardDimensionOnOneSide);
KMMove KMMoveFilters::Left1Down2(Left1, Down2, DefaultBoardDimensionOnOneSide);
KMMove KMMoveFilters::Right1Up2(Right1, Up2, DefaultBoardDimensionOnOneSide);
KMMove KMMoveFilters::Right2Up1(Right2, Up1, DefaultBoardDimensionOnOneSide);
KMMove KMMoveFilters::Right2Down1(Right2, Down1, DefaultBoardDimensionOnOneSide);
KMMove KMMoveFilters::Right1Down2(Right1, Down2, DefaultBoardDimensionOnOneSide);

const KMRandomAccessMoveCollection KMMoveFilters::AllPossibleMoves{
    Left1Up2,
    Left2Up1,
    Left2Down1,
    Left1Down2,
    Right1Up2,
    Right2Up1,
    Right2Down1,
    Right1Down2,
};

void KMMoveFilters::ResetFilters(KMBoardLocation Origin ,unsigned int BoardDimension, KnightMovesMethodLimitations SlicingMethod)
{
    m_SingleSideBoardDimension = BoardDimension;
    m_PathLimitations = SlicingMethod;
    // Prevent returning to the point of origin.
    m_VisitedLocations.push_back(Origin);
}

KMRandomAccessMoveCollection KMMoveFilters::GetPossibleMoves(const KMBoardLocation CurrentLocation) const
{
    KMRandomAccessMoveCollection PossibleMoves;
    for (auto PossibeMove : AllPossibleMoves) {
        PossibeMove.SetBoardDimension(m_SingleSideBoardDimension);
        PossibeMove.SetOriginCalculateDestination(CurrentLocation);
        if ((PossibeMove.IsValid()) && (IsNotPreviouslyVisited(PossibeMove))) {
            PossibleMoves.push_back(PossibeMove);
        }
    }
    return PossibleMoves;
}

bool KMMoveFilters::IsNotPreviouslyVisited(KMBoardLocation PossibleDestination) const
{
    bool NotPrevioslyVisited = true;

    if (!m_VisitedLocations.empty()) {    // This is always a test, we can't move backwards
        if (std::find(m_VisitedLocations.begin(), m_VisitedLocations.end(), PossibleDestination)
            != m_VisitedLocations.end()) {
            NotPrevioslyVisited = false;
        }
    }

    switch (m_PathLimitations) {
    default :
        throw std::runtime_error("KMPath::CheckMoveAgainstPreviousLocations : Unknown type of Path Limitation.");
    case DenyByPreviousLocation :
        // Always tested above.
        break;
    case DenyByPreviousRowOrColumn:
        if ((!m_VisitedRows.empty()) && (!m_VisitedColumns.empty())) {
            unsigned int PossibleRow = PossibleDestination.GetRow();
            if (std::find(m_VisitedRows.begin(), m_VisitedRows.end(), PossibleRow) != m_VisitedRows.end()) {
                NotPrevioslyVisited = false;
                break;
            }
            unsigned int PossibleColum = PossibleDestination.GetColumn();
            if (std::find(m_VisitedColumns.begin(), m_VisitedColumns.end(), PossibleColum) != m_VisitedColumns.end()) {
                NotPrevioslyVisited = false;
            }
        }
        break;
    }

    return NotPrevioslyVisited;
}

void KMMoveFilters::PushVisited(KMBoardLocation Location)
{
    m_VisitedRows.push_back(Location.GetRow());
    m_VisitedColumns.push_back(Location.GetColumn());
    m_VisitedLocations.push_back(Location);
}

void KMMoveFilters::PopVisited()
{
    m_VisitedRows.pop_back();
    m_VisitedColumns.pop_back();
    m_VisitedLocations.pop_back();
}
