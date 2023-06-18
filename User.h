#pragma once
#include "MyString.h"
#include "DataObject.h"

class User : public DataObject
{
	MyString firstName = "";
	MyString lastName = "";
	MyString password = "";
	size_t points = 0;

	bool isNameValid(const MyString& name) const;
	bool isPasswordValid(const MyString& password) const;
public:
	User() = default;
	User(size_t id, const MyString& firstName, const MyString& lastName, const MyString& password, size_t points);

	bool comparePassword(const MyString& password) const;
	bool setFirstName(const MyString& firstName);
	bool setLastName(const MyString& lastName);
	bool setPassword(const MyString& password);
	void addPoints(size_t pointsCount);

	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	size_t getPoints() const;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	~User() = default;
};