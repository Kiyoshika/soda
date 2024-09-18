#pragma once

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <sstream>
#include <cstddef>

namespace soda
{
namespace core
{
namespace data
{
namespace metadata
{
class ContentMetadata
{
public:
    ContentMetadata() noexcept;

    void from_file(const std::string& path);
    std::string to_string() const noexcept;

    std::uint64_t get_rows() const noexcept;
    std::uint64_t get_next_id() const noexcept;

    const std::vector<std::string>&
    get_repo_relationships() const noexcept;

    void add_repo_relationship(const std::string& repo) noexcept;
    void set_rows(std::uint64_t rows) noexcept;
    void set_next_id(std::uint64_t next_id) noexcept;

    void increment_rows() noexcept;
    void decrement_rows() noexcept;
    void increment_next_id() noexcept;
private:
    std::uint64_t m_rows;
    std::uint64_t m_next_id;
    std::vector<std::string> m_repo_relationships;
private:
    void parse(const std::string& metadata);
    void parse_relationships(const std::string& relationships_str);
    void set_key_value(const std::string& key, const std::string& value);
};
}
}
}
}
