#pragma once

#include <string>
#include <vector>
#include <cctype>

namespace soda
{
namespace util
{
class StringValidator
{

public:
	static bool validate_alpha(const std::string& str);
	static bool validate_alpha(
		const std::string& str,
		const std::vector<char>& allowed_chars);

	static bool validate_numeric(const std::string& str);
	static bool validate_numeric(
		const std::string& str,
		const std::vector<char>& allowed_chars);

	static bool validate_alphanumeric(const std::string& str);
	static bool validate_alphanumeric(
		const std::string& str,
		const std::vector<char>& allowed_chars);

private:
	static bool validate_base(
		const std::string& str,
		const std::vector<char>& allowed_chars,
		bool (*validate_char)(const char));

	static bool is_alpha(const char c);
	static bool is_numeric(const char c);
	static bool is_alphanumeric(const char c);
};
};
};