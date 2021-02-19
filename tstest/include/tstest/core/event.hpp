/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_EVENT_HPP
#define TSTEST_CORE_EVENT_HPP

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
   * @param name const reference to the name of the event
   * @param type type of event
   */
  Event(const EventName &name, const Type type) : name(name), type(type) {}

  /**
   * @brief Construct a new Event object
   *
   * @param name lvalue reference to the name of the event
   * @param type type of event
   */
  Event(EventName &&name, const Type type) : name(name), type(type) {}

  /**
   * @brief Get the event type
   *
   * @returns constant reference to the event type
   */
  const Type &getType() const { return type; }

  /**
   * @brief Get the event name
   *
   * @returns constant reference to the event name
   */
  const EventName &getName() const { return name; }

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

} // namespace tstest

#endif /* TSTEST_CORE_EVENT_HPP */
