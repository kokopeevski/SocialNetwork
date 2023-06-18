#pragma once
#include <fstream>

class DataObject
{
	size_t id = 0;

public:
	DataObject() = default;
	DataObject(size_t id);

	void setId(size_t id);
	size_t getId() const;
	virtual void deserialize(std::istream& is) = 0;
	virtual void serialize(std::ostream& os) const = 0;
};
