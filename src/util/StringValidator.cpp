#include "util/StringValidator.hpp"

using namespace soda::util;

bool StringValidator::validate_alpha(const std::string& str)
{
	return StringValidator::validate_base(str, {}, StringValidator::is_alpha);
}

bool StringValidator::validate_alpha(
	const std::string& str,
	const std::vector<char>& allowed_chars)
{
	return StringValidator::validate_base(str, allowed_chars, StringValidator::is_alpha);
}

bool StringValidator::validate_numeric(const std::string& str)
{
	return StringValidator::validate_base(str, {}, StringValidator::is_numeric);
}

bool StringValidator::validate_numeric(
	const std::string& str,
	const std::vector<char>& allowed_chars)
{
	return StringValidator::validate_base(str, allowed_chars, StringValidator::is_numeric);
}

bool StringValidator::validate_alphanumeric(const std::string& str)
{
	return StringValidator::validate_base(str, {}, StringValidator::is_alphanumeric);
}

bool StringValidator::validate_alphanumeric(
	const std::string& str,
	const std::vector<char>& allowed_chars)
{
	return StringValidator::validate_base(str, allowed_chars, StringValidator::is_alphanumeric);
}

bool StringValidator::validate_base(
	const std::string& str,
	const std::vector<char>& allowed_chars,
	bool (*validate_char)(const char))
{
	if (str.empty())
		return false;

	for (const char c : str)
	{
		bool is_valid = false;
		is_valid |= validate_char(c);

		if (!allowed_chars.empty())
			for (const char allowed_char : allowed_chars)
				is_valid |= c == allowed_char;

		if (!is_valid)
			return false;
	}

	return true;
}

bool StringValidator::is_alpha(const char c) { return std::isalpha(c) != 0; }
bool StringValidator::is_numeric(const char c) { return std::isdigit(c) != 0; }
bool StringValidator::is_alphanumeric(const char c) { return std::isalnum(c) != 0; }