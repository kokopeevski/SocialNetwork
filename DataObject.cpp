#include "DataObject.h"

void DataObject::setId(size_t id)
{
	this->id = id;
}

size_t DataObject::getId() const
{
	return this->id;
}

DataObject::DataObject(size_t id) : id(id) { }