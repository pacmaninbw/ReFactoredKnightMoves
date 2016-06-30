/*
 * TestData.h
 *
 *  Created on: Jun 30, 2016
 *      Author: pacman
 */

#ifndef TESTDATA_H_
#define TESTDATA_H_

#include <vector>
#include "KMMethodLimitations.h"
#include "KMBaseData.h"

typedef std::vector<KMBaseData> TestCaseList;

class KMTestData {
private:
    TestCaseList AllTestCases;

public:
    KMTestData();
    virtual ~KMTestData() = default;
    TestCaseList LetUserSelectTestCases();
    void PrintAllTestCases();
    void PrintTestCases(TestCaseList TestCases);
};

#endif /* TESTDATA_H_ */
