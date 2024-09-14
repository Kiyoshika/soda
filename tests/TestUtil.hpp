#pragma once

#include <exception>
#include <stdexcept>
#include <functional>
#include <iostream>

#define ASSERT_EXCEPTION(expected_exception, test_body){ \
    try { \
        test_body \
        std::cerr << "No exception caught. Expected '" << #expected_exception << "' to be thrown.\n"; \
        return -1; \
    } \
    catch (const expected_exception& ex) {} \
    catch (const std::exception& ex) { \
        std::cerr << "Incorrect exception caught. Expected '" << #expected_exception << "' to be thrown.\nException message: " << ex.what(); \
        return -1; \
    } \
}

#define ASSERT_NO_EXCEPTION(test_body){ \
    try { \
        test_body \
    } \
    catch (const std::exception& ex) { \
        std::cerr << "Was not expecting exception to be thrown.\nException message: " << ex.what(); \
        return -1; \
    } \
}