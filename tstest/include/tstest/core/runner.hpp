/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_RUNNER_HPP
#define TSTEST_CORE_RUNNER_HPP

#include <functional>
#include <thread>
#include <unordered_map>

#include <tstest/core/context.hpp>
#include <tstest/core/event_log.hpp>

namespace tstest {

/**
 * @brief Thread function type
 *
 */
typedef std::function<void(ExecutionContext)> ThreadFunction;

/**
 * @brief Runner Class
 *
 * The runner executes set of operations to be tested for thread safety in one
 * or more threads, as configured by the user.
 */
class Runner {
public:
  /**
   * @brief Access thread function method
   *
   * If a thread function with given name exists in the runner, then a refernce
   * to the function is returned. If no such thread function exists, a new
   * function is inserted and its reference returned.
   *
   * @param thread_name Rvalue reference to thread name
   * @returns Reference to thread function
   */
  ThreadFunction &operator[](ThreadName &&thread_name) {
    return thread_functions[thread_name];
  }

  /**
   * @brief Remove a thread function with given name.
   *
   * @param thread_name Rvalue reference to thread name
   * @returns `1` if an assertion function is removed else `0`
   */
  size_t Remove(ThreadName &&thread_name) {
    return thread_functions.erase(thread_name);
  }

  /**
   * @brief Get the event log object.
   *
   * @returns Constant reference to the event logs
   */
  const EventLog &GetEventLog() const { return event_log; }

  /**
   * @brief Run all registered thread functions.
   *
   */
  void Run() {
    // Using a map of threads. Could also have used a list or vector
    std::unordered_map<ThreadName, std::thread> threads;

    // Create execution context and run all thread functions
    for (auto &element : thread_functions) {
      // Create an execution context
      ExecutionContext context(&event_log, element.first);
      // Spawn thread executing a thread function
      threads[element.first] = std::thread(element.second, context);
    }

    // Wait for threads to finish
    for (auto &element : threads) {
      element.second.join();
    }
  }

  TSTEST_PRIVATE
  /**
   * @brief Chronologically ordered log of events.
   *
   */
  EventLog event_log;
  /**
   * @brief Mapping between thread names and thread functions.
   *
   */
  std::unordered_map<ThreadName, ThreadFunction> thread_functions;
};

} // namespace tstest

#endif /* TSTEST_CORE_RUNNER_HPP */
