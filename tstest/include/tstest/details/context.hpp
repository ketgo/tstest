/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST__DETAILS__CONTEXT_HPP
#define TSTEST__DETAILS__CONTEXT_HPP

#include <tstest/details/defs.hpp>
#include <tstest/details/event_log.hpp>

namespace tstest {
namespace details {

/**
 * @brief Execution Context Class
 *
 * An execution context contains contextual information required when executing
 * a thread function by the `Runner`.
 *
 */
class ExecutionContext {
 public:
  /**
   * @brief Construct a new Execution Context object
   *
   * @param event_log Pointer to the event log used for logging operation events
   * @param thread_name Constant reference to thread name
   */
  ExecutionContext(EventLog *event_log, const ThreadName &thread_name)
      : event_log(event_log), thread_name(thread_name) {}

  /**
   * @brief Log BEGIN operational event.
   *
   * @param operation_name Rvalue reference to operation name
   */
  void LogOperationBegin(OperationName &&operation_name) {
    event_log->Push({thread_name, operation_name, Event::Type::BEGIN});
  }

  /**
   * @brief Log END operational event.
   *
   * @param operation_name Rvalue reference to operation name
   */
  void LogOperationEnd(OperationName &&operation_name) {
    event_log->Push({thread_name, operation_name, Event::Type::END});
  }

  TSTEST_PRIVATE
  /**
   * @brief Pointer to the event log used for logging operational events.
   *
   */
  EventLog *event_log;

  /**
   * @brief Name of the thread which utilizes the execution context
   *
   */
  ThreadName thread_name;
};

}  // namespace details
}  // namespace tstest

#endif /* TSTEST__DETAILS__CONTEXT_HPP */
