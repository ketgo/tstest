/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_EVENT_LIST_HPP
#define TSTEST_CORE_EVENT_LIST_HPP

#include <list>

#include <tstest/core/defs.hpp>
#include <tstest/core/event.hpp>
#include <tstest/utility/annotations.hpp>
#include <tstest/utility/mutex.hpp>

namespace tstest {

/**
 * @brief Event List Class
 *
 * The event list contains chronologically ordered sequence of operation events
 * pushed by one or more threads during testing.
 */
class EventList {
  TSTEST_PRIVATE
  /**
   * @brief Re-enterent Lock for mutual exclusion
   *
   */
  typedef typename tstest::Mutex<std::recursive_mutex> Mutex;
  mutable Mutex lock; //<- lock for achieving thread safety via mutual exclusion
  typedef typename tstest::LockGuard<Mutex> LockGuard;

  /**
   * @brief Chronologically ordered list of events
   *
   */
  std::list<Event> events GUARDED_BY(lock);

public:
  /**
   * @brief Push an event into the event list.
   *
   * @param event constant reference to the event to push
   */
  void Push(const Event &event) {
    LockGuard guard(lock);

    events.push_back(event);
  }

  /**
   * @brief Push an event into the event list.
   *
   * @param event lvalue reference to the event to push
   */
  void Push(Event &&event) {
    LockGuard guard(lock);

    events.push_back(event);
  }

  /**
   * @brief Get the latest event in the list
   *
   */
  Event Latest() const {
    LockGuard guard(lock);

    return events.back();
  }

  /**
   * @brief Get the first event in the list
   *
   */
  Event First() const {
    LockGuard guard(lock);

    return events.front();
  }

  /**
   * @brief Check if the event list contains the given event.
   *
   * @param event lvalue reference to the event to check
   * @returns `true` if the list contains the event else `false`
   */
  bool Contains(Event &&event) const {
    LockGuard guard(lock);

    auto it = events.begin();

    while (it != events.end()) {
      if (*it == event) {
        return true;
      }
      ++it;
    }
    return false;
  }

  /**
   * @brief Get size of the event list.
   *
   * @returns number of events in the list
   */
  size_t Size() const {
    LockGuard guard(lock);

    return events.size();
  }

  /**
   * @brief Equality comparision operator
   *
   */
  bool operator==(const std::list<Event> &other) const {
    LockGuard guard(lock);

    // Check if size are equal
    if (Size() != other.size()) {
      return false;
    }

    auto it = events.begin();
    auto other_it = other.begin();

    while (it != events.end() && other_it != other.end()) {
      if (*it != *other_it) {
        return false;
      }
      ++it;
      ++other_it;
    }

    return true;
  }

  /**
   * @brief Check if event is in list.
   *
   * @param event const reference to the event to check for
   * @returns `true` if is in list else `false`
   */
  bool isIn(const Event &event) const {
    LockGuard guard(lock);

    auto it = events.begin();

    while (it != events.end()) {
      if (*it == event) {
        return true;
      }
    }
    return false;
  }
};

} // namespace tstest

#endif /* TSTEST_CORE_EVENT_LIST_HPP */
