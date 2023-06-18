#pragma once
#include "DataObject.h"

class SecondaryDataObject : public DataObject
{
	size_t createrId = 0;

public:
	SecondaryDataObject(size_t id, size_t createrId);
	SecondaryDataObject() = default;

	void setCreaterId(size_t id);
	size_t getCreaterId() const;
};
