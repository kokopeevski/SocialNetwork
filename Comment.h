#pragma once
#include "SecondaryDataObject.h"
#include "MyString.h"

class Comment : public SecondaryDataObject
{
	MyString text = "";
	size_t postId = 0;
	size_t upvotesCount = 0;
	size_t downvotesCount = 0;

public:
	Comment(const MyString& text, size_t id, size_t createrId, size_t postId);
	Comment() = default;

	const MyString& getText() const;
	size_t getPostId() const;

	void setText(const MyString& text);
	void setPostId(size_t postId);
	void addUpvote();
	void addDownvote();

	size_t getUpvotes() const;
	size_t getDownvotes() const;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};
