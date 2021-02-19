/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_EXCEPTION_HPP
#define TSTEST_CORE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace tstest {

/**
 * No Assertion Function Found Error
 *
 * This error is thrown if no assertion function is found in the dispatch table
 * of the assertor.
 */
class NoAssertionFunctionFound : public std::exception {
private:
  std::string msg;

public:
  NoAssertionFunctionFound() : msg("No assertion function found.") {}
  NoAssertionFunctionFound(const char *msg) : msg(msg) {}
  NoAssertionFunctionFound(std::string &msg) : msg(msg) {}

  const char *what() const throw() { return msg.c_str(); }
};

} // namespace tstest

#endif /* TSTEST_CORE_EXCEPTION_HPP */
