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

    // CREATE NEW VALID DATABASE
    try
    {
        teardown();
        TestDatabase::create("mydb");
        if (!std::filesystem::is_directory(DirectoryFactory::build_path_from_home({ "soda-test", "mydb" })))
        {
            std::cerr << "mydb was not created.\n";
            teardown();
            return -1;
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << "\n";
        teardown();
        return -1;
    }

    // CREATE NEW INVALID DATABASE
    try
    {
        teardown();
        TestDatabase::create("bad..name");
        std::cerr << "Expected exception when creating database 'bad..name'.\n";
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

    // ATTEMPT TO CREATE DUPLICATE DATABASE
    try
    {
        teardown();
        TestDatabase::create("mydb");
        TestDatabase::create("mydb");
        std::cerr << "Missing exception when attempting to create duplicate database.\n";
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

    teardown();
    return 0;
}