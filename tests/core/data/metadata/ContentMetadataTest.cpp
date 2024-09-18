#include "core/data/metadata/ContentMetadata.hpp"
#include "core/data/metadata/Exceptions.hpp"

#include "TestUtil.hpp"

#include <cassert>

using namespace soda::tests;
using namespace soda::core::data::metadata;

int main()
{
    ContentMetadata metadata;

    metadata.set_rows(12);
    assert(metadata.get_rows() == 12);

    metadata.increment_rows();
    assert(metadata.get_rows() == 13);

    metadata.decrement_rows();
    assert(metadata.get_rows() == 12);

    metadata.set_next_id(42);
    assert(metadata.get_next_id() == 42);

    metadata.add_repo_relationship("one");
    metadata.add_repo_relationship("two");
    const auto& relationships = metadata.get_repo_relationships();
    assert(relationships[0] == "one");
    assert(relationships[1] == "two");

    assert(metadata.to_string() == "rows:12,nextid:42,relationships:one,two");

    ASSERT_EXCEPTION(ContentFileNotFoundException, {
        ContentMetadata new_metadata;
        new_metadata.from_file("noexist");
    });
    
    return 0;
}
