/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_DEFS_HPP
#define TSTEST_CORE_DEFS_HPP

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
 * @brief Operation name type
 *
 */
typedef std::string OperationName;

/**
 * @brief Thread name type
 * 
 */
typedef std::string ThreadName;

} // namespace tstest

#endif /* TSTEST_CORE_DEFS_HPP */
