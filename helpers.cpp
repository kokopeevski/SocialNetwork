#include "helpers.h"

bool isUpperLetter(char letter)
{
	return letter >= 'A' && letter <= 'Z';
}

bool isLowerLetter(char letter)
{
	return letter >= 'a' && letter <= 'z';
}

bool isCharDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

bool contains(const MyString& str, bool(*criteria)(char))
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (criteria(str[i]))
			return true;
	}

	return false;
}

bool isInputValidIndex(const MyString& string)
{
	if (string.isEmpty()) { return false; }
	for (size_t i = 0; i < string.length(); i++)
	{
		if (!isCharDigit(string[i])) { return false; }
	}

	return true;
}

MyVector<MyString> splitInputInCommandAndValue(const MyString& input)
{
	MyVector<MyString> result;

	if (input.length() <= 2)
	{
		result.push_back(MyString("Invalid!"));
		return result;
	}

	int endInput = input.find(' ');

	if (endInput == -1)
	{
		result.push_back(input);
		return result;
	}

	MyString command = input.substr(0, endInput);
	result.push_back(command);

	size_t lengthOfValue = input.length() - command.length() - 1;
	MyString value = input.substr((endInput + 1), lengthOfValue);

	result.push_back(value);

	return result;
}

void print(const char* str)
{
	std::cout << str;
}

void print(const MyString& str)
{
	std::cout << str;
}