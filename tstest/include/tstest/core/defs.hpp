/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_DEFS_HPP
#define TSTEST_CORE_DEFS_HPP

#include <functional>
#include <string>

/**
 * Used for intrusive testing
 *
 */
#ifdef TSTEST_INTRUSIVE_TESTING
#define TSTEST_PRIVATE public:
#define TSTEST_PROTECTED public:
#else
#define TSTEST_PRIVATE private:
#define TSTEST_PROTECTED protected:
#endif

namespace tstest {

/**
 * @brief Event name type
 *
 */
typedef std::string EventName;

/**
 * @brief Assertion function type
 *
 */
typedef std::function<void()> AssertionFunction;

} // namespace tstest

#endif /* TSTEST_CORE_DEFS_HPP */
