#pragma once
#include "SecondaryDataObject.h"
#include "MyString.h"

class Reply : public SecondaryDataObject
{
	size_t commentId = 0;
	MyString text = "";

public:
	Reply(const MyString& text, size_t id, size_t createrId, size_t commentId);
	Reply() = default;

	const MyString& getText() const;
	size_t getCommentId() const;

	void setText(const MyString& text);
	void setCommentId(size_t postId);

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};