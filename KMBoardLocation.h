/*
 * KMBoardLocation.h
 *
 *  Created on: Mar 17, 2016
 *	  Author: pacmaninbw
 */

#ifndef KMBOARDLOCATION_H_
#define KMBOARDLOCATION_H_

#include <iostream>
#include <string>

class KMBoardLocation {
private:
	std::string m_Name;
	unsigned int m_Row;
	unsigned int m_Column;
	unsigned int m_BoardDimension;
	void ThrowBoundsException(const char* FormatString);

public:
	KMBoardLocation();
	KMBoardLocation(unsigned int Row, unsigned int Column, unsigned int BoardSingleSideDimension);
	virtual ~KMBoardLocation() = default;
	std::string GetName() const { return m_Name; }
	void SetName(std::string Name) { m_Name = Name; }
	void MakeName();
	void SetRow(const unsigned int Row) { m_Row = Row; }
	unsigned int GetRow() const { return m_Row; }
	void SetColumn(const unsigned int Column) { m_Column = Column; }
	unsigned int GetColumn() const { return m_Column; }
	bool IsSet() const { return (m_Row && m_Column); }
	bool IsValid() const;
	void SetBoardDimension(unsigned int Dimension) { m_BoardDimension = Dimension; }
	int GetBoardDimension() const { return m_BoardDimension; }
	bool operator ==(const KMBoardLocation &OtherLocation) const {
		if ((m_Row == OtherLocation.m_Row) && (m_Column == OtherLocation.m_Column)) {
			return true;
		}
		return false;
	}
	friend std::ostream &operator<<( std::ostream &output, KMBoardLocation &KMLoc)
	{
		output << " " << KMLoc.GetName();
		return output;
	}
};

#endif /* KMBOARDLOCATION_H_ */


