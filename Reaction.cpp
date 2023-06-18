#include "Reaction.h"

Reaction::Reaction(size_t id, size_t createrId, size_t commentId, bool isUpvote)
    : SecondaryDataObject(id, createrId), commentId(commentId), isUpvote(isUpvote)
{}

void Reaction::setCommentId(size_t commentId)
{
    this->commentId = commentId;
}

size_t Reaction::getCommentId() const
{
    return commentId;
}

void Reaction::setReactionType(bool isReactionUpvote)
{
    this->isUpvote = isReactionUpvote;
}

bool Reaction::getIsUpvote() const
{
    return isUpvote;
}

void Reaction::deserialize(std::istream& is)
{
    char emptyLine = is.get();
    //std::cout << emptyLine;

    size_t id;
    is >> id;
    setId(id);

    size_t commentId;
    is >> commentId;
    setCommentId(commentId);

    size_t createrId;
    is >> createrId;
    setCreaterId(createrId);

    bool isUpvote;
    is >> isUpvote;
    setReactionType(isUpvote);

    /* std::cout << "Record with id: " << getId() << ' '
        << getCommentId() << ' ' << getCreaterId() << ' '
        << "Is upvote: " << getIsUpvote() << std::endl; */

}

void Reaction::serialize(std::ostream& os) const
{
    os << getId() << ' '
        << getCommentId() << ' '
        << getCreaterId() << ' '
        << getIsUpvote() << std::endl;
}