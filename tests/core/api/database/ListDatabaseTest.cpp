#include "core/api/database/Database.hpp"
#include "core/api/database/Exceptions.hpp"
#include "util/DirectoryFactory.hpp"

#include "TestUtil.hpp"

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
    // remove test dir if already exists
    teardown();

    ASSERT_NO_EXCEPTION({
        TestDatabase::create("db1");
        TestDatabase::create("db2");
        TestDatabase::create("db3");
        std::vector<std::string> db_list = TestDatabase::list();
        teardown();
        assert(db_list == std::vector<std::string>({ "db1", "db2", "db3" }));
    });

    teardown();
    return 0;
}