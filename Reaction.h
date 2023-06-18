#pragma once
#include <iostream>
#include "SecondaryDataObject.h"

class Reaction : public SecondaryDataObject
{
	size_t commentId = 0;
	bool isUpvote = false;

public:
	Reaction() = default;
	~Reaction() = default;
	Reaction(size_t id, size_t createrId, size_t commentId, bool isUpvote);

	void setCommentId(size_t commentId);
	size_t getCommentId() const;

	void setReactionType(bool isReactionUpvote);
	bool getIsUpvote() const;

	void deserialize(std::istream& is) override;
	void serialize(std::ostream& os) const override;
};