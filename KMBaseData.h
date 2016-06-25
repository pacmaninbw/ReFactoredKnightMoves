/*
 * KMBaseData.h
 *
 *  Created on: Mar 20, 2016
 *      Author: pacmaninbw
 */

#ifndef KMBASEDATA_H_
#define KMBASEDATA_H_

struct KMBaseData {
	unsigned int m_StartRow;
	unsigned int m_StartColumn;
	std::string m_StartName;
	unsigned int m_TargetRow;
	unsigned int m_TargetColumn;
	std::string m_TargetName;
	unsigned int m_DimensionOneSide;
	KnightMovesMethodLimitations m_LimitationsOnMoves;
};

#endif /* KMBASEDATA_H_ */
