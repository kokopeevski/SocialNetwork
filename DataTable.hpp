#pragma once
#include "Post.h"
#include "Table.h"
#include "Comment.h"
#include "Reaction.h"
#include "Topic.h";

template <typename T>
class DataTable : public Table
{
	MyVector<T> records;

public:
	void addRecord(const T& newRecord);
	DataTable() = default;
	DataTable(const MyString& fileName);
	T* getById(size_t id);
	T* getByTitle(const MyString& title);

	Post* getByTitleAndTopicId(const MyString& title, size_t topicId);

	MyVector<Post> getPostsByTopicId(size_t topicId);
	MyVector<Comment> getCommentsByPostId(size_t postId);
	Reaction* getReactionByUserIdAndCommentId(size_t userId, size_t commentId);

	void removeReactionById(size_t id);

	T* getByFirstName(const MyString& firstName);
	void test(const MyString& fileName, const MyString& testName);
	MyVector<Topic> searchTopicsByPartOfTitle(const MyString& partOfTitle) const;

	void load(const MyString& file) override;
	void overwrite(const MyString& file) const override;
};

template<typename T>
void DataTable<T>::addRecord(const T& newRecord)
{
	records.push_back(newRecord);
	countRecords++;
}

template<typename T>
DataTable<T>::DataTable(const MyString& fileName) : Table(fileName) { }

template<typename T>
T* DataTable<T>::getById(size_t id)
{
	for (size_t i = 0; i < countRecords; i++)
	{
		if (id == records[i].getId())
			return &records[i];
	}

	return nullptr;
}

template<typename T>
T* DataTable<T>::getByTitle(const MyString& title)
{
	for (size_t i = 0; i < countRecords; i++)
	{
		if (title == records[i].getTitle())
			return &records[i];
	}

	return nullptr;
}

template<typename T>
Post* DataTable<T>::getByTitleAndTopicId(const MyString& title, size_t topicId)
{
	for (size_t i = 0; i < countRecords; i++)
	{
		if (title == records[i].getTitle() && topicId == records[i].getTopicId())
			return &records[i];
	}

	return nullptr;
}

template<typename T>
MyVector<Post> DataTable<T>::getPostsByTopicId(size_t topicId)
{
	MyVector<Post> result;
	for (size_t i = 0; i < countRecords; i++)
	{
		if (topicId == records[i].getTopicId())
			result.push_back(records[i]);
	}

	return result;
}

template<typename T>
MyVector<Comment> DataTable<T>::getCommentsByPostId(size_t postId)
{
	MyVector<Comment> result;

	for (size_t i = 0; i < countRecords; i++)
	{
		if (postId == records[i].getPostId())
			result.push_back(records[i]);
	}

	return result;
}

template<typename T>
Reaction* DataTable<T>::getReactionByUserIdAndCommentId(size_t userId, size_t commentId)
{
	for (size_t i = 0; i < countRecords; i++)
	{
		if (userId == records[i].getCreaterId() && commentId == records[i].getCommentId())
			return &records[i];
	}

	return nullptr;
}

template<typename T>
void DataTable<T>::removeReactionById(size_t id)
{
	try
	{
		for (size_t i = 0; i < countRecords; i++)
		{
			size_t idd = records[i].getId();
			if (idd == id)
			{
				countRecords--;
				records.remove(i);
				return;
			}
		}
	}
	catch (const std::exception& exc)
	{
		countRecords++;
		std::cout << "Invalid index!\n";
	}
}

template<typename T>
T* DataTable<T>::getByFirstName(const MyString& firstName)
{
	for (size_t i = 0; i < countRecords; i++)
	{
		if (firstName == records[i].getFirstName())
			return &records[i];
	}

	return nullptr;
}

template<typename T>
void DataTable<T>::test(const MyString& fileName, const MyString& testName)
{
	std::cout << testName << std::endl;
	load(fileName);

	overwrite(fileName);
	std::cout << std::endl;
}

template<typename T>
MyVector<Topic> DataTable<T>::searchTopicsByPartOfTitle(const MyString& partOfTitle) const
{
	MyVector<Topic> result;

	for (size_t i = 0; i < countRecords; i++)
	{
		const MyString& title = records[i].getTitle();
		if (title.isSubstring(partOfTitle))
			result.push_back(records[i]);
	}

	return result;
}

template<typename T>
void DataTable<T>::load(const MyString& file)
{
	std::ifstream ifs(file.c_str());

	if (!ifs.is_open())
	{
		std::cout << "Not open";
		return;
	}

	loadMetadata(ifs);
	for (size_t i = 0; i < countRecords; i++)
	{
		records.push_back();
		records[i].deserialize(ifs);
	}

	ifs.close();
}

template<typename T>
void DataTable<T>::overwrite(const MyString& file) const
{
	std::ofstream ofs(file.c_str());

	if (!ofs.is_open())
	{
		std::cout << "Not open";
		return;
	}

	writeMetadataToFile(ofs);
	for (size_t i = 0; i < countRecords; i++)
	{
		records[i].serialize(ofs);
	}

	ofs.close();
}