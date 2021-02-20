/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_ASSERTOR_HPP
#define TSTEST_CORE_ASSERTOR_HPP

#include <unordered_map>

#include <tstest/core/defs.hpp>
#include <tstest/core/event_log.hpp>
#include <tstest/core/exception.hpp>

namespace tstest {

/**
 * @brief Assertor Class
 *
 * An assertor maps one or more sequence of events to user provided assertion
 * functions via dispatch table. The assertion function asserts the expected
 * behavior for an observed mapped event sequence.
 *
 * @note The class is not thread safe.
 *
 */
class Assertor {
public:
  /**
   * @brief Dispatch Table Type
   *
   * The table maps list of events to an assertion function.
   *
   */
  typedef std::unordered_map<EventList, AssertionFunction, EventListHash>
      DispatchTable;

  /**
   * @brief Construct a new Assertor object
   *
   */
  Assertor() {}

  /**
   * @brief Construct a new Assertor object
   *
   * @param dispatch_table Constant reference to an initial dispatch table
   */
  Assertor(DispatchTable &dispatch_table) : dispatch_table(dispatch_table) {}

  /**
   * @brief Construct a new Assertor object
   *
   * @param dispatch_table Rvalue reference to an initial dispatch table
   */
  Assertor(DispatchTable &&dispatch_table) : dispatch_table(dispatch_table) {}

  /**
   * @brief Get assertion function for given event list.
   *
   * @param event_list Constant reference to the event list
   * @returns Constant reference to assertion function
   */
  const AssertionFunction &Get(const EventList &event_list) const {
    return dispatch_table.at(event_list);
  }

  /**
   * @brief Get assertion function for given event list.
   *
   * @param event_list Rvalue reference to the event list
   * @returns Constant reference to assertion function
   */
  const AssertionFunction &Get(EventList &&event_list) const {
    return dispatch_table.at(event_list);
  }

  /**
   * @brief Insert assertion function into dispatch table for given event_list.
   *
   * @param event_list Constant reference to event list
   * @param assertion_function Constant reference to assertion function
   */
  void Insert(const EventList &event_list,
              const AssertionFunction &assertion_function) {
    dispatch_table[event_list] = assertion_function;
  }

  /**
   * @brief Insert assertion function into dispatch table for given event list.
   *
   * @param event_list Rvalue reference to event list
   * @param assertion_function Rvalue reference to assertion function
   */
  void Insert(EventList &&event_list, AssertionFunction &&assertion_function) {
    dispatch_table[event_list] = assertion_function;
  }

  /**
   * @brief Remove assertion function from dispatch table for given event list.
   *
   * @param event_list Constant reference to event list
   */
  void Remove(const EventList &event_list) { dispatch_table.erase(event_list); }

  /**
   * @brief Remove assertion function from dispatch table for given event list.
   *
   * @param event_list Rvalue reference to event list
   */
  void Remove(const EventList &&event_list) {
    dispatch_table.erase(event_list);
  }

  /**
   * @brief Run assertion using the dispatch table. In case no assertion found
   * for the observed event logs, the `NoAssertionFunctionFound` exception is
   * raised. This exception can be disabled if the `raise` argument is set to
   * `false`.
   *
   * @param event_log Constant reference to the event log.
   * @param raise Flag to indicate if `NoAssertionFunctionFound` exception
   * should be raised. Default set to `true`.
   */
  void Assert(const EventLog &event_log,
              bool raise = true) NO_THREAD_SAFETY_ANALYSIS {
    AssertionFunction assertion_function;

    // Find assertion function for given event log
    auto it = dispatch_table.find(event_log.events);

    // Check if assertion function found
    if (it == dispatch_table.end()) {
      // Assertion function not found so raise `NoAssertionFunctionFound` id the
      // `raise` flag is set
      if (raise) {
        assertion_function = [&]() {
          // TODO: Detailed exception message
          throw NoAssertionFunctionFound();
        };
      } else {
        // NOP assertion function set
        assertion_function = [&]() {};
      }
    } else {
      assertion_function = it->second;
    }

    // Calling assertion function
    assertion_function();
  }

  TSTEST_PRIVATE
  /**
   * @brief Dispatch table mapping list of events to assertion functions.
   *
   */
  DispatchTable dispatch_table;
};

} // namespace tstest

#endif /* TSTEST_CORE_ASSERTOR_HPP */
