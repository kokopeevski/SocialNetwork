#include "User.h"
#include "helpers.h"
#include "GlobalConstants.h"

using namespace LENGTHS;

User::User(size_t id, const MyString& firstName, const MyString& lastName, const MyString& password, size_t points)
    : DataObject(id), firstName(firstName), lastName(lastName), password(password), points(points) {
}

bool User::comparePassword(const MyString& password) const
{
    return this->password == password;
}

bool User::setFirstName(const MyString& firstName)
{
    if (!isNameValid(firstName))
        return false;

    this->firstName = firstName;
    return true;
}

bool User::setLastName(const MyString& lastName)
{
    if (!isNameValid(lastName))
        return false;

    this->lastName = lastName;
    return true;
}

bool User::setPassword(const MyString& password)
{
    if (!isPasswordValid(password))
        return false;

    this->password = password;
    return true;
}

void User::addPoints(size_t pointsCount)
{
    this->points += pointsCount;
}

const MyString& User::getFirstName() const
{
    return firstName;
}

const MyString& User::getLastName() const
{
    return this->lastName;
}

size_t User::getPoints() const
{
    return this->points;
}

void User::serialize(std::ostream& os) const
{
    os << getId() << std::endl
        << getFirstName() << std::endl
        << getLastName() << std::endl
        << password << std::endl
        << getPoints() << std::endl << std::endl;
}

void User::deserialize(std::istream& is)
{
    char emptyLine = is.get();
    //std::cout << emptyLine;

    size_t id;
    is >> id;
    setId(id);
    emptyLine = is.get();

    is >> firstName;

    is >> lastName;

    is >> password;

    is >> points;
    emptyLine = is.get();

    //std::cout << id << firstName << lastName << password << points;
}

bool User::isNameValid(const MyString& name) const
{
    return !contains(name, [](char symbol) {return symbol == ' '; });
}

bool User::isPasswordValid(const MyString& password) const
{
    if (password.length() < MIN_LEN_PASS || password.length() > MAX_LEN_PASS)
        return false;

    if (!contains(password, isCharDigit))
        return false;

    if (!contains(password, isUpperLetter))
        return false;

    if (!contains(password, isLowerLetter))
        return false;

    return true;
}