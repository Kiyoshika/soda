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

    // ATTEMPT TO DROP VALID DATABASE
    ASSERT_NO_EXCEPTION({
        teardown();
        Database::create("mydb");
        Database::drop("mydb");
        if (std::filesystem::exists(DirectoryFactory::build_path_from_home({ "soda-test", "mydb" })))
        {
            std::cerr << "mydb did not drop correctly.\n";
            teardown();
            return -1;
        }
    });

    // ATTEMPT TO DROP INVALID DATABASE
    ASSERT_EXCEPTION(DatabaseNotFoundException, {
        teardown();
        Database::drop("blah");
        teardown();
    });

    teardown();
    return 0;
}
