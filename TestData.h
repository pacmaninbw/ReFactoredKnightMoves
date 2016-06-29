/*
 * TestData.h
 *
 *  Created on: Jun 29, 2016
 *      Author: pacmaninbw
 */

#ifndef TESTDATA_H_
#define TESTDATA_H_

#include <vector>
#include "KMMethodLimitations.h"
#include "KMBaseData.h"

class KMTestData {
private:
    std::vector<KMBaseData> AllTestCases;

public:
    KMTestData();
    virtual ~KMTestData() = default;
    std::vector<KMBaseData> LetUserEnterTestCaseNumber();
};

#endif /* TESTDATA_H_ */
