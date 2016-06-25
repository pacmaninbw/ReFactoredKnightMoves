/*
 * KMMove.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: pacmaninbw
 */

#include <stdexcept>
#include "KMMove.h"
#include "KMBoardDimensionConstants.h"

KMMove::KMMove()
 : m_RowTransition{0},
   m_ColumnTransition{0},
   m_BoardDimension{DefaultBoardDimensionOnOneSide}
{
}

/**
 * BoardDimension is converted to int for type safe comparisions.
 */
KMMove::KMMove(int RowTransition, int ColumnTransition, unsigned int BoardDimension)
: m_RowTransition{RowTransition},
  m_ColumnTransition{ColumnTransition},
  m_BoardDimension{static_cast<int>(BoardDimension)}
{
}

void KMMove::CalculateDestination()
{
	if (m_Origin.IsSet()) {
		m_Destination.SetRow(m_RowTransition + m_Origin.GetRow());
		m_Destination.SetColumn(m_ColumnTransition + m_Origin.GetColumn());
		m_Destination.SetBoardDimension(m_Origin.GetBoardDimension());
	}
	else
	{
		throw std::runtime_error("KMMove::CalculateDestination : Point of Origin has not been set;\n");
	}
}

void KMMove::SetOriginCalculateDestination(KMBoardLocation Origin)
{
	if (Origin.IsValid()) {
		m_Origin = Origin;
		CalculateDestination();
	}
	else
	{
		throw std::runtime_error("KMMove::CalculateDestination : Parameter Origin has not been set;\n");
	}
}

void KMMove::MakeNamesForOutPut()
{
	if (m_Origin.IsValid()) {
		m_Origin.MakeName();
	}
	if (m_Destination.IsValid()) {
		m_Destination.MakeName();
	}
}
