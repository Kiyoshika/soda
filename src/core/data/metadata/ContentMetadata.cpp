#include "core/data/metadata/ContentMetadata.hpp"
#include "core/data/metadata/Exceptions.hpp"
#include "util/DirectoryFactory.hpp"

using namespace soda::core::data::metadata;
using namespace soda::util;

ContentMetadata::ContentMetadata() noexcept
{
    this->m_rows = 0;
    this->m_next_id = 1;
    this->m_repo_relationships = std::vector<std::string>();
}

void ContentMetadata::from_file(const std::string& path)
{
    std::ifstream content(path);
    if (!content.is_open())
        throw ContentFileNotFoundException(path);
    
    std::string line;
    std::getline(content, line);
    content.close();

    this->parse(line);
}

std::string ContentMetadata::to_string() const noexcept
{
    std::stringstream output_ss;
    output_ss << "rows:" << this->get_rows() << ",";
    output_ss << "nextid:" << this->get_next_id() << ",";
    output_ss << "relationships:";
    const auto& repo_names = this->get_repo_relationships();
    for (std::size_t i = 0; i < this->get_repo_relationships().size(); ++i)
    {
        output_ss << repo_names[i];
        if (i < this->get_repo_relationships().size() - 1)
            output_ss << ",";
    }

    return output_ss.str();
}

std::uint64_t ContentMetadata::get_rows() const noexcept
{
    return this->m_rows;
}

const std::vector<std::string>&
ContentMetadata::get_repo_relationships() const noexcept
{
    return this->m_repo_relationships;
}

void ContentMetadata::increment_rows() noexcept
{
    this->m_rows += 1;
}

void ContentMetadata::decrement_rows() noexcept
{
    if (this->m_rows > 0)
        this->m_rows -= 1;
}

void ContentMetadata::increment_next_id() noexcept
{
    this->m_next_id += 1;
}

void ContentMetadata::set_key_value(
    const std::string& key,
    const std::string& value)
{
    if (key == "rows")
        this->set_rows(std::stoull(value));
    else if (key == "nextid")
        this->set_next_id(std::stoull(value));
    else if (key == "relationships")
        this->parse_relationships(value);
    else
        throw UnknownKeyException(key);
}

void ContentMetadata::parse(const std::string& metadata)
{
    if (metadata.empty())
        throw ContentParseException();

    bool parsing_key = true;
    std::string key;
    std::string value;
    for (const char c : metadata)
    {
        if (c == ',')
        {
            this->set_key_value(key, value);
            parsing_key = true;
            key.clear();
            value.clear();
            continue;
        }

        if (c == ':')
        {
            parsing_key = !parsing_key;
            continue;
        }


        if (parsing_key)
            key.push_back(c);
        else
            value.push_back(c);
    }

    if (!key.empty())
        this->set_key_value(key, value);
}

void ContentMetadata::parse_relationships(const std::string& relationships_str)
{
    if (relationships_str.empty())
        return;

    std::string value{0};
    for (const char c :relationships_str)
    {
        if (c == ',')
        {
            this->m_repo_relationships.push_back(value);
            value.clear();
            continue;
        }

        value += c;
    }

    if (!value.empty())
        this->m_repo_relationships.push_back(value);
}

void ContentMetadata::set_rows(std::uint64_t rows) noexcept
{
    this->m_rows = rows;
}

void ContentMetadata::set_next_id(std::uint64_t next_id) noexcept
{
    this->m_next_id = next_id;
}

std::uint64_t ContentMetadata::get_next_id() const noexcept
{
    return this->m_next_id;
}

void ContentMetadata::add_repo_relationship(const std::string& repo_name) noexcept
{
    this->m_repo_relationships.push_back(repo_name);
}
