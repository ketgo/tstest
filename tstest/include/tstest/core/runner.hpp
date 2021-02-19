/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_RUNNER_HPP
#define TSTEST_CORE_RUNNER_HPP

#include <string>

#include <tstest/core/defs.hpp>
#include <tstest/core/event_log.hpp>

namespace tstest {

/**
 * @brief Runner Class
 *
 * The runner executes set of operations to be tested for thread safety in one
 * or more threads, as configured by the user.
 */
class Runner {
  TSTEST_PRIVATE
  /**
   * @brief Chronologically ordered log of events.
   *
   */
  EventLog event_log;

public:
  void OpBegin(const std::string &name) {}

  void OpBegin(const std::string &&name) {}

  void OpEnd(const std::string &name) {}

  void OpEnd(const std::string &&name) {}

  void Eun();
};

} // namespace tstest

#endif /* TSTEST_CORE_RUNNER_HPP */
