#include "Comment.h"

Comment::Comment(const MyString& text, size_t id, size_t createrId, size_t postId)
    : text(text), postId(postId), SecondaryDataObject(id, createrId)
{}

const MyString& Comment::getText() const
{
    return this->text;
}

size_t Comment::getPostId() const
{
    return this->postId;
}

void Comment::setText(const MyString& text)
{
    this->text = text;
}

void Comment::setPostId(size_t postId)
{
    this->postId = postId;
}

void Comment::addUpvote()
{
    upvotesCount++;
}

void Comment::addDownvote()
{
    downvotesCount++;
}

size_t Comment::getUpvotes() const
{
    return upvotesCount;
}

size_t Comment::getDownvotes() const
{
    return downvotesCount;
}

void Comment::serialize(std::ostream& os) const
{
    os << getId() << std::endl
        << getCreaterId() << std::endl
        << getPostId() << std::endl
        << getText() << std::endl << std::endl;
}

void Comment::deserialize(std::istream& is)
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

    size_t postId;
    is >> postId;
    setPostId(postId);
    emptyLine = is.get();

    is >> text;

    //std::cout << "Record with id: " << getId() << ' '
    //    << getCreaterId() << ' ' << getText() << std::endl;
}