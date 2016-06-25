/*
 * KMOutputData.h
 *
 *  Created on: Mar 19, 2016
 *  Modified on: June 21, 2016
 *      Author: pacmaninbw
 *
 *      This class reports the data after the test is complete. Each successful
 *      path is stored for output. Statistics on all the successful paths are
 *      always provided, printing all the moves in the successful paths is
 *      optional. A count of all attempted paths is maintained and reported.
 *      The current configuration is a command line program with text output,
 *      this class could be converted to providing graphic output.
 */

#ifndef KMOUTPUTDATA_H_
#define KMOUTPUTDATA_H_

#include <vector>
#include "KMPath.h"

class KMOutputData {
private:
	KMBoardLocation m_Origin;
	KMBoardLocation m_Destination;
	unsigned int m_BoardDimension;
	std::vector<KMPath> m_PathRecords;
	unsigned int m_AttemptedPaths;
	KnightMovesMethodLimitations m_LimitationsOnMoves;
	bool m_ShowPathData;
protected:
	void OutputSlicingMethodlogy();

public:
	KMOutputData();
	virtual ~KMOutputData() = default;
	void IncrementAttemptedPaths() { m_AttemptedPaths++; }
	void AddPath(const KMPath PathData) { m_PathRecords.push_back(PathData); }
	int GetPathCount() const { return m_PathRecords.size(); }
	std::vector<KMPath> GetAllPaths() const { return m_PathRecords; }
	unsigned int GetAttempts() const { return m_AttemptedPaths; }
	void SetPointOfOrigin(KMBoardLocation Origin) { m_Origin = Origin; }
	KMBoardLocation GetPointOfOrigin() { return m_Origin; }
	void SetDestination(KMBoardLocation Destination) { m_Destination = Destination; }
	KMBoardLocation GetDestination() { return m_Destination; }
	void SetBoardDimension(unsigned int BoardDimension) { m_BoardDimension = BoardDimension; }
	unsigned int GetBoardDimension() const { return m_BoardDimension; }
	// Statistics on the returned paths.
	void ShowStats();
	double Average(std::vector<double> PathLengths);
	void SetSlicingMethod(KnightMovesMethodLimitations Limitations) { m_LimitationsOnMoves = Limitations; }
	KnightMovesMethodLimitations GetSlicingMethod() { return m_LimitationsOnMoves; }
	void DontShowPathData() { m_ShowPathData = false; }
	void ShowPathData() { m_ShowPathData = true; }
	bool GetShowPathData() const { return m_ShowPathData; }
	void ShowResults();
};

#endif /* KMOUTPUTDATA_H_ */
