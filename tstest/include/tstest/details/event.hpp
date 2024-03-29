/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST__DETAILS__EVENT_HPP
#define TSTEST__DETAILS__EVENT_HPP

#include <list>

#include <tstest/details/defs.hpp>

namespace tstest {
namespace details {

/**
 * @brief Event Class
 *
 * The class represents an operational event. It contaians the name of the
 * operation and the type of event. Currently only the following event types are
 * supported:
 *
 * - BEGIN
 * - END
 *
 */
class Event {
 public:
  /**
   * @brief Enumerated list of event types.
   *
   */
  enum class Type { BEGIN = 0, END };

  /**
   * @brief Construct a new Event object
   *
   * @param thread_name Constant reference to the name of the thread
   * @param operation_name Constant reference to the name of the operation
   * @param event_type Type of event
   */
  Event(const ThreadName &thread_name, const OperationName &operation_name,
        const Type event_type)
      : thread_name(thread_name),
        operation_name(operation_name),
        event_type(event_type) {}

  /**
   * @brief Construct a new Event object
   *
   * @param thread_name Lvalue reference to the name of the thread
   * @param operation_name Lvalue reference to the name of the operation
   * @param event_type Type of event
   */
  Event(ThreadName &&thread_name, OperationName &&operation_name,
        const Type event_type)
      : thread_name(thread_name),
        operation_name(operation_name),
        event_type(event_type) {}

  /**
   * @brief Get the event type
   *
   * @returns Constant reference to the event type
   */
  const Type &GetEventType() const { return event_type; }

  /**
   * @brief Get the operation name
   *
   * @returns Constant reference to the operation name
   */
  const OperationName &GetOperationName() const { return operation_name; }

  /**
   * @brief Get the thread name
   *
   * @returns Constant reference to the thread name
   */
  const OperationName &GetThreadName() const { return thread_name; }

  /**
   * @brief String representation of the event
   *
   * @returns event string
   */
  std::string ToString() const {
    const char *type_str[] = {"BEGIN", "END"};
    return "{\"" + thread_name + "\", \"" + operation_name +
           "\", tstest::Event::Type::" + type_str[(int)event_type] + "}";
  }

  /**
   * @brief Equality comparision operator
   *
   */
  bool operator==(const Event &other) const {
    return event_type == other.event_type &&
           operation_name == other.operation_name &&
           thread_name == other.thread_name;
  }

  /**
   * @brief Inequality comparision operator
   *
   */
  bool operator!=(const Event &other) const {
    return event_type != other.event_type ||
           operation_name != other.operation_name ||
           thread_name != other.thread_name;
  }

  TSTEST_PRIVATE
  /**
   * @brief Type of event
   *
   */
  Type event_type;
  /**
   * @brief Name of the operation
   *
   */
  OperationName operation_name;
  /**
   * @brief Name of thread
   *
   */
  ThreadName thread_name;
};

/**
 * @brief Function object to compute hash value for an event object.
 *
 */
class EventHash {
 public:
  /**
   * @brief Compute hash value for given event object.
   *
   * @param event Constant reference to event object
   * @returns Hash value for the given event object
   */
  size_t operator()(const Event &event) const {
    // Implemented hash function based on comment in
    // https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector

    size_t seed = event.GetOperationName().size();
    seed ^= std::hash<int>()((int)event.GetEventType()) + 0x9e3779b9 +
            (seed << 6) + (seed >> 2);
    for (auto &i : event.GetOperationName()) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    for (auto &i : event.GetThreadName()) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return seed;
  }
};

/**
 * @brief EventList Type
 *
 */
typedef std::list<Event> EventList;

/**
 * @brief Hash function object for event list.
 *
 */
class EventListHash {
 public:
  /**
   * @brief Compute hash value for given event list
   *
   * @param event_list Constant reference to event list
   * @returns Hash value for the given event list
   */
  size_t operator()(const EventList &event_list) const {
    // Implemented hash function based on comment in
    // https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector

    size_t seed = event_list.size();
    EventHash event_hash;
    for (auto &event : event_list) {
      seed ^= event_hash(event) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return seed;
  }
};

}  // namespace details
}  // namespace tstest

#endif /* TSTEST__DETAILS__EVENT_HPP */
