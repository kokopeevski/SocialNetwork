#include "Database.h"

Database* Database::instancePtr = nullptr;

Database& Database::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Database();
    }

    return *instancePtr;
}