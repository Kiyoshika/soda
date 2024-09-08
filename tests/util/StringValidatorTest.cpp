#include "util/StringValidator.hpp"
#include <cassert>

using namespace soda::util;

int main()
{
	assert(StringValidator::validate_alpha("") == false);
	assert(StringValidator::validate_alpha("abc") == true);
	assert(StringValidator::validate_alpha("123") == false);
	assert(StringValidator::validate_alpha("abc123") == false);
	assert(StringValidator::validate_alpha("abc-_", {'-', '_'}) == true);
	assert(StringValidator::validate_alpha("abc-_", {'-'}) == false);

	assert(StringValidator::validate_numeric("") == false);
	assert(StringValidator::validate_numeric("abc") == false);
	assert(StringValidator::validate_numeric("123") == true);
	assert(StringValidator::validate_numeric("abc123") == false);
	assert(StringValidator::validate_numeric("123-_", { '-', '_' }) == true);
	assert(StringValidator::validate_numeric("123-_", { '-' }) == false);

	assert(StringValidator::validate_alphanumeric("") == false);
	assert(StringValidator::validate_alphanumeric("abc") == true);
	assert(StringValidator::validate_alphanumeric("123") == true);
	assert(StringValidator::validate_alphanumeric("abc123") == true);
	assert(StringValidator::validate_alphanumeric("abc-_", { '-', '_' }) == true);
	assert(StringValidator::validate_alphanumeric("abc-_", { '-' }) == false);
	assert(StringValidator::validate_alphanumeric("123-_", { '-', '_' }) == true);
	assert(StringValidator::validate_alphanumeric("123-_", { '-' }) == false);
	assert(StringValidator::validate_alphanumeric("abc123-_", { '-', '_' }) == true);
	assert(StringValidator::validate_alphanumeric("abc123-_", { '-' }) == false);

	return 0;
}