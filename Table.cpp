#include "Table.h"

Table::Table() : fileName(), countRecords(0)
{}

Table::Table(const MyString& fileName) : fileName(fileName), countRecords(0)
{}

size_t Table::getUnusedId()
{
	//std::cout << "Unused Id: " << lastUsedId + 1;
	return ++lastUsedId;
}

void Table::loadMetadata(std::istream& is)
{
	is >> countRecords >> lastUsedId;
}

void Table::writeMetadataToFile(std::ostream& os) const
{
	os << countRecords << ' ' << lastUsedId << std::endl << std::endl;
}