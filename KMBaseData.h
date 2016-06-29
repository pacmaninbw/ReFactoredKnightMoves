/*
 * KMBaseData.h
 *
 *  Created on: Mar 20, 2016
 *      Author: pacmaninbw
 */

#ifndef KMBASEDATA_H_
#define KMBASEDATA_H_

#include <iostream>
#include <string>
#include <stdexcept>

struct KMBaseData {
    unsigned int m_StartRow;
    unsigned int m_StartColumn;
    std::string m_StartName;
    unsigned int m_TargetRow;
    unsigned int m_TargetColumn;
    std::string m_TargetName;
    unsigned int m_DimensionOneSide;
    KnightMovesMethodLimitations m_LimitationsOnMoves;
    friend std::ostream &operator<<( std::ostream &output, KMBaseData &TestCase)
    {
        output << "\t" << TestCase.m_StartName
                << "\t" << TestCase.m_TargetName
                << "\t" << TestCase.m_DimensionOneSide
                << "\t";
        switch (TestCase.m_LimitationsOnMoves)
        {
            default :
                throw std::runtime_error("LetUserEnterTestCaseNumber : Unknown type of Path Limitation.");
            case DenyByPreviousLocation :
                output << "Can't return to previous location";
                break;
            case DenyByPreviousRowOrColumn:
                output << "Can't return to previous row or column";
                break;
        }
        output << "\n";

        return output;
    }
};

#endif /* KMBASEDATA_H_ */
