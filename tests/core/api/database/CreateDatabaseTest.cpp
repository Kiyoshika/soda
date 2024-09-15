#include "core/api/database/Database.hpp"
#include "core/api/database/Exceptions.hpp"
#include "util/DirectoryFactory.hpp"

#include "TestUtil.hpp"

#include <cassert>
#include <iostream>

using namespace soda::tests;
using namespace soda::util;
using namespace soda::core::api::database;


int main()
{
    //remove test dir if already exists
    teardown();

    // CREATE NEW VALID DATABASE
    ASSERT_NO_EXCEPTION({
        teardown();
        TestDatabase::create("mydb");
        if (!std::filesystem::is_directory(DirectoryFactory::build_path_from_home({ "soda-test", "mydb" })))
        {
            std::cerr << "mydb was not created.\n";
            teardown();
            return -1;
        }
    });

    // CREATE NEW INVALID DATABASE
    ASSERT_EXCEPTION(InvalidDatabaseNameException, {
        teardown();
        TestDatabase::create("bad..name");
        teardown();
    });

    // ATTEMPT TO CREATE DUPLICATE DATABASE
    ASSERT_EXCEPTION(DatabaseAlreadyExistsException, {
        teardown();
        TestDatabase::create("mydb");
        TestDatabase::create("mydb");
        teardown();
    });

    teardown();
    return 0;
}
