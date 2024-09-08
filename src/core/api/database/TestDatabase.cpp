#include "core/api/database/Database.hpp"

using namespace soda::core::api::database;

void TestDatabase::create(const std::string& name)
{
    Database::create(name, true);
}

void TestDatabase::drop(const std::string& name)
{
    Database::drop(name, true);
}

void TestDatabase::rename(const std::string& old_name, const std::string& new_name)
{
    Database::rename(old_name, new_name, true);
}

std::vector<std::string> TestDatabase::list()
{
    return Database::list(true);
}