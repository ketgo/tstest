/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST__DETAILS__ASSERTOR_HPP
#define TSTEST__DETAILS__ASSERTOR_HPP

#include <functional>
#include <unordered_map>
#include <vector>

#include <tstest/details/defs.hpp>
#include <tstest/details/event_log.hpp>
#include <tstest/details/exception.hpp>

namespace tstest {
namespace details {

/**
 * @brief Assertion function type
 *
 */
typedef std::function<void()> AssertionFunction;

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
   * @thread_unsafe
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
   * @thread_unsafe
   *
   * @param event_list Rvalue reference to the event list
   * @returns Constant reference to assertion function
   */
  const AssertionFunction &Get(EventList &&event_list) const {
    return dispatch_table.at(event_list);
  }

  /**
   * @brief Insert assertion function into dispatch table for given event list.
   *
   * @thread_unsafe
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
   * @thread_unsafe
   *
   * @param event_list Rvalue reference to event list
   * @param assertion_function Rvalue reference to assertion function
   */
  void Insert(EventList &&event_list, AssertionFunction &&assertion_function) {
    dispatch_table[event_list] = assertion_function;
  }

  /**
   * @brief The method inserts a single assertion function into dispatch table
   * for mutiple event lists.
   *
   * @thread_unsafe
   *
   * @param event_list Constant reference to a vector of event lists
   * @param assertion_function Rvalue reference to assertion function
   */
  void InsertMany(const std::vector<EventList> &event_lists,
                  const AssertionFunction &assertion_function) {
    for (auto &event_list : event_lists) {
      dispatch_table[event_list] = assertion_function;
    }
  }

  /**
   * @brief The method inserts a single assertion function into dispatch table
   * for mutiple event lists.
   *
   * @thread_unsafe
   *
   * @param event_list Rvalue reference to a vector of event lists
   * @param assertion_function Rvalue reference to assertion function
   */
  void InsertMany(std::vector<EventList> &&event_lists,
                  AssertionFunction &&assertion_function) {
    for (auto &event_list : event_lists) {
      dispatch_table[event_list] = assertion_function;
    }
  }

  /**
   * @brief Remove assertion function from dispatch table for given event list.
   *
   * @thread_unsafe
   *
   * @param event_list Constant reference to event list
   * @returns `1` if an assertion function is removed else `0`
   */
  size_t Remove(const EventList &event_list) {
    return dispatch_table.erase(event_list);
  }

  /**
   * @brief Remove assertion function from dispatch table for given event list.
   *
   * @thread_unsafe
   *
   * @param event_list Rvalue reference to event list
   * @returns `1` if an assertion function is removed else `0`
   */
  size_t Remove(const EventList &&event_list) {
    return dispatch_table.erase(event_list);
  }

  /**
   * @brief Run assertion using the configured dispatch table. An exception is
   * thrown in case no assertion function is found for the observed event logs.
   *
   * @thread_unsafe
   *
   * @param event_log Constant reference to the event log.
   *
   */
  void Assert(const EventLog &event_log) const {
    EventList event_list = event_log.GetEvents();

    AssertionFunction assertion_function = [&]() {
      // TODO: Detailed exception message
      throw NoAssertionFunctionFound(event_list);
    };

    // Find assertion function for given event log
    auto it = dispatch_table.find(event_list);
    // Check if assertion function found
    if (it != dispatch_table.end()) {
      assertion_function = it->second;
    }

    // Calling assertion function
    assertion_function();
  }

  /**
   * @brief Run assertion using the configured dispatch table. In case no
   * assertion function is found then the provided default is executed.
   *
   * @thread_unsafe
   *
   * @param event_log Constant reference to the event log.
   * @param default_function Default assertion function
   *
   */
  void Assert(const EventLog &event_log,
              const AssertionFunction &default_function) const {
    AssertionFunction assertion_function = default_function;

    // Find assertion function for given event log
    auto it = dispatch_table.find(event_log.GetEvents());
    // Check if assertion function found
    if (it != dispatch_table.end()) {
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

}  // namespace details
}  // namespace tstest

#endif /* TSTEST__DETAILS__ASSERTOR_HPP */
