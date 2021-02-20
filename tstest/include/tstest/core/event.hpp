/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_EVENT_HPP
#define TSTEST_CORE_EVENT_HPP

#include <list>

#include <tstest/core/defs.hpp>

namespace tstest {
/**
 * @brief Event Class
 *
 * The class represents in event. It consists of a name and the type of event.
 * Currently only the following event types are supported:
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
  enum class Type { BEGIN, END };

  /**
   * @brief Construct a new Event object
   *
   * @param name Constant reference to the name of the event
   * @param type Type of event
   */
  Event(const EventName &name, const Type type) : name(name), type(type) {}

  /**
   * @brief Construct a new Event object
   *
   * @param name Lvalue reference to the name of the event
   * @param type Type of event
   */
  Event(EventName &&name, const Type type) : name(name), type(type) {}

  /**
   * @brief Get the event type
   *
   * @returns Constant reference to the event type
   */
  const Type &GetType() const { return type; }

  /**
   * @brief Get the event name
   *
   * @returns Constant reference to the event name
   */
  const EventName &GetName() const { return name; }

  /**
   * @brief Equality comparision operator
   *
   */
  bool operator==(const Event &other) const {
    return type == other.type && name == other.name;
  }

  /**
   * @brief Inequality comparision operator
   *
   */
  bool operator!=(const Event &other) const {
    return type != other.type || name != other.name;
  }

  TSTEST_PRIVATE
  /**
   * @brief Type of event
   *
   */
  Type type;
  /**
   * @brief Name of the event
   *
   */
  EventName name;
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

    size_t seed = event.GetName().size();
    seed ^= std::hash<int>()((int)event.GetType()) + 0x9e3779b9 + (seed << 6) +
            (seed >> 2);
    for (auto &i : event.GetName()) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return seed;
  }
};

} // namespace tstest

#endif /* TSTEST_CORE_EVENT_HPP */
