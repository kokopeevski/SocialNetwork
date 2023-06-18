#include "Post.h"

Post::Post(const MyString& title, size_t id, size_t createrId, size_t topicId)
    : title(title), SecondaryDataObject(id, createrId), topicId(topicId)
{
}

const MyString& Post::getTitle() const
{
    return this->title;
}

void Post::setTitle(const MyString& title)
{
    this->title = title;
}

void Post::setTopicId(size_t id)
{
    topicId = id;
}

size_t Post::getTopicId() const
{
    return topicId;
}

void Post::serialize(std::ostream& os) const
{
    os << getId() << std::endl
        << getTopicId() << std::endl
        << getCreaterId() << std::endl
        << getTitle() << std::endl << std::endl;
}

void Post::deserialize(std::istream& is)
{
    char emptyLine = is.get();
    //std::cout << emptyLine;

    size_t id;
    is >> id;
    setId(id);
    emptyLine = is.get();

    size_t topicId;
    is >> topicId;
    setTopicId(topicId);
    emptyLine = is.get();

    size_t createrId;
    is >> createrId;
    setCreaterId(createrId);
    emptyLine = is.get();

    is >> title;

    //std::cout << "Record with id: " << getId() << ' '
    //   << getCreaterId() << ' ' << getTitle() << std::endl;
}