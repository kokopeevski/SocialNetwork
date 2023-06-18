#include "Topic.h"

Topic::Topic(const MyString& title, const MyString& description, size_t createrId, size_t id)
    : title(title), description(description), SecondaryDataObject(id, createrId)
{}

const MyString& Topic::getTitle() const
{
    return this->title;
}

const MyString& Topic::getDescription() const
{
    return this->description;
}

void Topic::setTitle(const MyString& title)
{
    this->title = title;
}

void Topic::setDescription(const MyString& description)
{
    this->description = description;
}

void Topic::serialize(std::ostream& os) const
{
    os << getId() << std::endl
        << getCreaterId() << std::endl
        << getTitle() << std::endl
        << getDescription() << std::endl << std::endl;
}

void Topic::deserialize(std::istream& is)
{
    char emptyLine = is.get();
    //std::cout << emptyLine;

    size_t id;
    is >> id;
    setId(id);
    emptyLine = is.get();

    size_t createrId;
    is >> createrId;
    setCreaterId(createrId);
    emptyLine = is.get();

    is >> title;

    is >> description;

    //std::cout << "Record with id: " << getId() << ' '
    //   << getCreaterId() << ' ' << getTitle() << ' ' << getDescription() << std::endl;
}