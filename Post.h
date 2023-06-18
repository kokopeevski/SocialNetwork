#pragma once
#include "SecondaryDataObject.h"
#include "MyString.h"

class Post : public SecondaryDataObject
{
	MyString title = "";
	size_t topicId = 0;

public:

	Post(const MyString& title, size_t id, size_t createrId, size_t topicId);
	Post() = default;

	const MyString& getTitle() const;
	void setTitle(const MyString& title);

	void setTopicId(size_t id);
	size_t getTopicId() const;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};