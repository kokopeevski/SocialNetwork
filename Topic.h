#pragma once
#include "SecondaryDataObject.h"
#include "MyString.h"

class Topic : public SecondaryDataObject
{
	MyString title = "";
	MyString description = "";

public:
	Topic(const MyString& title, const MyString& description, size_t createrId, size_t id);
	Topic(const Topic& other) = default;
	Topic() = default;

	const MyString& getTitle() const;
	const MyString& getDescription() const;
	void setTitle(const MyString& title);
	void setDescription(const MyString& description);

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};
