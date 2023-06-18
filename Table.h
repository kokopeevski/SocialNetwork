#pragma once
#include <fstream>
#include "MyString.h"
#include "DataObject.h"

class Table
{
private:
	MyString fileName = "";

protected:
	void loadMetadata(std::istream& ifs);

	void writeMetadataToFile(std::ostream& ifs) const;
	size_t lastUsedId = 0;
	size_t countRecords = 0;

public:

	size_t getUnusedId();
	virtual ~Table() = default;
	Table(const MyString& fileName);
	Table();

	virtual void load(const MyString& file) = 0;
	virtual void overwrite(const MyString& file) const = 0;
};