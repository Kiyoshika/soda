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

    // ATTEMPT TO RENAME VALID DATABASE
    ASSERT_NO_EXCEPTION({
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
    });

    // ATTEMPT TO RENAME EXISTING DATABASE
    ASSERT_EXCEPTION(DatabaseAlreadyExistsException, {
        teardown();
        TestDatabase::create("db1");
        TestDatabase::create("db2");
        TestDatabase::rename("db1", "db2");
        teardown();
    });

    // ATTEMPT TO RENAME BAD DATABASE
    ASSERT_EXCEPTION(InvalidDatabaseNameException, {
        teardown();
        TestDatabase::create("db1");
        TestDatabase::rename("db1", "bad..name");
        teardown();
    });

    teardown();
    return 0;
}
