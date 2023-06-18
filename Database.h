#pragma once
#include <iostream>

class Database
{
public:
	static Database& getInstance();

	~Database() = default;

private:

	Database() {
		std::cout << "Created\n";
	};
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	static Database* instancePtr;
};