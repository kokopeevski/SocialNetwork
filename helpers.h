#pragma once
#include <fstream>
#include "MyString.h"
#include "DataObject.h"

bool isUpperLetter(char letter);

bool isLowerLetter(char letter);

bool isCharDigit(char symbol);

bool contains(const MyString& str, bool (*criteria)(char));

bool isInputValidIndex(const MyString& string);

MyVector<MyString> splitInputInCommandAndValue(const MyString& input);

void print(const char* str);
void print(const MyString& str);

template <typename T>
const DataObject* searchInCollectionById(const MyVector<T> collection, size_t id);

template<typename T>
inline const DataObject* searchInCollectionById(const MyVector<T> collection, size_t id)
{
	for (size_t i = 0; i < collection.getSize(); i++)
	{
		if (id == collection[i].getId())
			return &collection[i];
	}

	return nullptr;
}