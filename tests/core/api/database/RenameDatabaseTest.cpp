#include "core/api/database/Database.hpp"
#include "core/api/database/DatabaseExceptions.hpp"
#include "util/DirectoryFactory.hpp"
#include <cassert>
#include <iostream>

using namespace soda::util;
using namespace soda::core::api::database;

static void teardown()
{
    std::filesystem::remove_all(TestDirectoryFactory::get_soda_dir());
}

int main()
{
    //remove test dir if already exists
    teardown();

    // ATTEMPT TO RENAME VALID DATABASE
    try
    {
        teardown();
        TestDatabase::create("db1");
        TestDatabase::rename("db1", "db2");
        if (std::filesystem::exists(DirectoryFactory::build_path_from_home({ "soda-test", "db1" })))
        {
            std::cerr << "'db1' still exists after rename.\n";
            teardown();
            return -1;
        }

        if (!std::filesystem::exists(DirectoryFactory::build_path_from_home({ "soda-test", "db2" })))
        {
            std::cerr << "Expected 'db2' to exist after rename.\n";
            teardown();
            return -1;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what();
        teardown();
        return -1;
    }

    // ATTEMPT TO RENAME EXISTING DATABASE
    try
    {
        teardown();
        TestDatabase::create("db1");
        TestDatabase::create("db2");
        TestDatabase::rename("db1", "db2");
        std::cerr << "Expected exception when renaming 'db1' to existing database 'db2'.\n";
        teardown();
        return -1;
    }
    catch (const DatabaseAlreadyExistsException& ex) { (void)ex; }
    catch (const std::exception& ex)
    {
        std::cerr << "Unexpected exception:\n" << ex.what();
        teardown();
        return -1;
    }

    // ATTEMPT TO RENAME BAD DATABASE
    try
    {
        teardown();
        TestDatabase::create("db1");
        TestDatabase::rename("db1", "bad..name");
        std::cerr << "Expected exception when renaming 'db1' to 'bad..name'.\n";
        teardown();
        return -1;
    }
    catch (const InvalidDatabaseNameException& ex) { (void)ex; }
    catch (const std::exception& ex)
    {
        std::cerr << "Unexpected exception:\n" << ex.what();
        teardown();
        return -1;
    }

    teardown();
    return 0;
}