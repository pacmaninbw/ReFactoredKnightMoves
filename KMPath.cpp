/*
 * KMPath.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: pacmaninbw
 */

#include <stdexcept>
#include "KMPath.h"
#include "KMBoardDimensionConstants.h"

KMMove KMPath::GetLastMove()
{
    KMMove LastMove;
    if (m_RecordOfMoves.size() > 0) {
        LastMove = m_RecordOfMoves.back();
    }
    else
    {
        std::cerr << "In KMPath::GetLastMove() : There was no last move" << std::endl;
    }

    return LastMove;
}
