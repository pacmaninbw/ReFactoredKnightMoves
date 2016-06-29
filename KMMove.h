/*
 * KMMove.h
 *
 *  Created on: Mar 18, 2016
 *      Author: pacmaninbw
 */

#ifndef KMMOVE_H_
#define KMMOVE_H_

#include <vector>
#include <list>
#include "KMBoardLocation.h"

class KMMove {
private:
    int m_RowTransition;
    int m_ColumnTransition;
    int m_BoardDimension;
    KMBoardLocation m_Origin;
    KMBoardLocation m_Destination;

public:
    KMMove();
    KMMove(int RowTransition, int ColumnTransition, unsigned int BoardDimension);
    virtual ~KMMove() = default;
    bool IsValid() const { return ((((!m_RowTransition) || (!m_ColumnTransition)) || (!m_Destination.IsValid())) ? false : true); };
    void CalculateDestination();
    void SetOriginCalculateDestination(const KMBoardLocation Origin);
    KMBoardLocation GetNextLocation() const { return m_Destination; }
    void SetOrigin(KMBoardLocation Origin) { m_Origin = Origin; }
    KMBoardLocation GetOrigin() const { return m_Origin; }
    void SetRowTransition(int RowTransition){ m_RowTransition = RowTransition; }
    int GetRowTransition() const { return m_RowTransition; }
    void SetColumnTransition(int ColumnTransition){ m_ColumnTransition = ColumnTransition; }
    int GetColumnTransition() const { return m_ColumnTransition; }
    void SetBoardDimension(unsigned int BoardDimension) { m_BoardDimension = static_cast<int>(BoardDimension); }
    int GetBoardDimension() const { return m_BoardDimension; }
    void SetTransitionsAndDimension(const int RowTransition, const int ColumnTransition, const unsigned int BoardDimension) {
        m_RowTransition = RowTransition;
        m_ColumnTransition = ColumnTransition;
        m_BoardDimension = static_cast<int>(BoardDimension);
    }
    void MakeNamesForOutPut();
    friend std::ostream &operator<<( std::ostream &output, KMMove &Move)
    {
        output << "Move from " << Move.GetOrigin().GetName();
        output << " To " << Move.GetNextLocation().GetName();
        return output;
    }
};

typedef std::vector<KMMove> KMRandomAccessMoveCollection;
typedef std::list<KMMove> KMFastAccessMoveCollection;

#endif /* KMMOVE_H_ */
