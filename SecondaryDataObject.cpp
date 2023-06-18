#include "SecondaryDataObject.h"

SecondaryDataObject::SecondaryDataObject(size_t id, size_t createrId)
	: DataObject(id), createrId(createrId)
{}

void SecondaryDataObject::setCreaterId(size_t id)
{
	this->createrId = id;
}

size_t SecondaryDataObject::getCreaterId() const
{
	return createrId;
}