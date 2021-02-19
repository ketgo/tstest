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
  // Allows private access to `EventHash` class
  friend class EventHash; // forward declaration

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
  size_t operator()(const Event &event) const { return 0; }
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
  size_t operator()(const EventList &event_list) const { return 0; }
};

} // namespace tstest

#endif /* TSTEST_CORE_EVENT_HPP */
