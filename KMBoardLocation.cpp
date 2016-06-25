/*
 * KMBoardLocation.cpp
 *
 *  Created on: Mar 17, 2016
 *	  Author: pacmaninbw
 */

#include "KnightMoves.h"
#include <stdio.h>
#include <string>
#include <stdexcept>
#include "KMBoardLocation.h"
#include "KMBoardDimensionConstants.h"

const int ExceptionMessageBufferSize = 1024;


KMBoardLocation::KMBoardLocation()
: m_Row{0}, m_Column{0}, m_BoardDimension{DefaultBoardDimensionOnOneSide}
{
	m_Name = "";
}

KMBoardLocation::KMBoardLocation(unsigned int Row, unsigned int Column, unsigned int BoardSingleSideDimension)
 : m_Row{Row}, m_Column{Column}, m_BoardDimension{BoardSingleSideDimension}
{
	if (((m_Row < MinimumBoardLocationValue)|| (m_Row > m_BoardDimension)) ||
		((m_Column < MinimumBoardLocationValue) || (m_Column > m_BoardDimension))) {
		ThrowBoundsException("KMBoardLocation::KMBoardLocation");
	}
	MakeName();
}

/**
 * A common chess notation for location is using A-H for rows and 1-8 for columns.
 * MakeName creates a name for the location using that notation.
 */
void KMBoardLocation::MakeName()
{
	const unsigned int RowCStrSize = 2; // Enough for a null terminated string of 1 character
	const unsigned int RowCharacterPosition = 0;
	const unsigned int RowNullTerminatorPosition = 1;

	if (((m_Row < MinimumBoardLocationValue)|| (m_Row > m_BoardDimension)) ||
		((m_Column < MinimumBoardLocationValue) || (m_Column > m_BoardDimension))) {
		ThrowBoundsException("KMBoardLocation::MakeName()");
	}

	char RowCStr[RowCStrSize];
	RowCStr[RowCharacterPosition] = ('A' + (m_Row - 1));
	RowCStr[RowNullTerminatorPosition] = '\0';

	std::string tempRow(RowCStr);
	std::string tempColumn = std::to_string(m_Column);
	m_Name = tempRow + tempColumn;
}

void KMBoardLocation::ThrowBoundsException(const char *CallingFunction)
{
	char estrbuff[ExceptionMessageBufferSize];
	sprintf(estrbuff, "%s value out of range (%d to %d) : ", CallingFunction, MinimumBoardLocationValue, m_BoardDimension);
	std::string EMessage(estrbuff);
	sprintf(estrbuff, "Row = %d, Column = %d", m_Row, m_Column);
	EMessage.append(estrbuff);
	throw std::runtime_error(EMessage);
}

bool KMBoardLocation::IsValid() const
{
	bool ValidLocation = true;
	if (!IsSet())
	{
		ValidLocation = false;
	}
	else
	{
		if ((m_Row < MinimumBoardLocationValue)|| (m_Row > m_BoardDimension)) {
			ValidLocation = false;
		}
		if ((m_Column < MinimumBoardLocationValue)|| (m_Column > m_BoardDimension)) {
			ValidLocation = false;
		}
	}

	return ValidLocation;
}
