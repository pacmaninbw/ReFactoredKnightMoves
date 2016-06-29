/*
 * KMPath.h
 *
 *  Created on: Mar 18, 2016
 *  Extensively refactored: June 20, 2016
 *  Comments added: June 24, 2016
 *      Author: pacmaninbw
 *
 *      This class maintains a history of the current path for reporting purposes
 *      as well as for the search algorithm. Within the algorithm it is used as a
 *      stack, for reporting purposes it is used as a linear list.
 *
 */

#ifndef KMPATH_H_
#define KMPATH_H_

#include "KMBoardLocation.h"
#include "KMMove.h"
#include "KMMethodLimitations.h"

class KMPath {
private:
    KMFastAccessMoveCollection m_RecordOfMoves;

public:
    KMPath() = default;
    KMPath(const KMPath &Original) = default;
    virtual ~KMPath() = default;
    void AddMoveToPath(KMMove Move) { m_RecordOfMoves.push_back(Move); }
    void RemoveLastMove() { m_RecordOfMoves.pop_back(); }
    unsigned int GetLength() const { return m_RecordOfMoves.size(); }
    KMFastAccessMoveCollection GetRecordOfMoves() const { return m_RecordOfMoves; }
    KMMove GetLastMove();
    friend std::ostream &operator<<( std::ostream &output, KMPath &Path)
    {
        output << "This path contains " << Path.GetLength() << " moves." << std::endl;
        KMFastAccessMoveCollection RecordOfMoves = Path.GetRecordOfMoves();
        for (auto CurrentMove: RecordOfMoves) {
            CurrentMove.MakeNamesForOutPut();
            output << CurrentMove << std::endl;
        }
        return output;
    }
};

#endif /* KMPATH_H_ */
