#include "core/api/database/Database.hpp"
#include "core/api/database/Exceptions.hpp"
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

    // ATTEMPT TO DROP VALID DATABASE
    try
    {
        teardown();
        Database::create("mydb");
        Database::drop("mydb");
        if (std::filesystem::exists(DirectoryFactory::build_path_from_home({ "soda-test", "mydb" })))
        {
            std::cerr << "mydb did not drop correctly.\n";
            teardown();
            return -1;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        teardown();
        return -1;
    }

    // ATTEMPT TO DROP INVALID DATABASE
    try
    {
        teardown();
        Database::drop("blah");
        std::cerr << "Expected exception when dropping 'blah'.\n";
        teardown();
        return -1;
    }
    catch (const DatabaseNotFoundException& ex) { (void)ex; }
    catch (const std::exception& ex)
    {
        std::cerr << "Unexpected exception:\n" << ex.what();
        teardown();
        return -1;
    }

    teardown();
    return 0;
}