#include "Reply.h"

Reply::Reply(const MyString& text, size_t id, size_t createrId, size_t postId)
    : text(text), commentId(postId), SecondaryDataObject(id, createrId)
{}

const MyString& Reply::getText() const
{
    return this->text;
}

size_t Reply::getCommentId() const
{
    return this->commentId;
}

void Reply::setText(const MyString& text)
{
    this->text = text;
}

void Reply::setCommentId(size_t postId)
{
    this->commentId = postId;
}

void Reply::serialize(std::ostream& os) const
{
    os << getId() << std::endl
        << getCreaterId() << std::endl
        << getText() << std::endl << std::endl;
}

void Reply::deserialize(std::istream& is)
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

    is >> text;

    //std::cout << "Record with id: " << getId() << ' '
    //    << getCreaterId() << ' ' << getText() << std::endl;
}