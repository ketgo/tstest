/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_EVENT_LOG_HPP
#define TSTEST_CORE_EVENT_LOG_HPP

#include <tstest/core/defs.hpp>
#include <tstest/core/event.hpp>
#include <tstest/utility/annotations.hpp>
#include <tstest/utility/mutex.hpp>

namespace tstest {

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

/**
 * @brief Event Log Class
 *
 * The event log contains chronologically ordered sequence of operational
 * events pushed by one or more threads during testing.
 */
class EventLog {
  // Allows private access to `Assertor` class
  friend class Assertor; // forward declaration

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
  EventList events GUARDED_BY(lock);

public:
  /**
   * @brief Push an event into the log.
   *
   * @thread_safe
   *
   * @param event Constant reference to the event to push
   */
  void Push(const Event &event) {
    LockGuard guard(lock);

    events.push_back(event);
  }

  /**
   * @brief Push an event into the log.
   *
   * @thread_safe
   *
   * @param event Lvalue reference to the event to push
   */
  void Push(Event &&event) {
    LockGuard guard(lock);

    events.push_back(event);
  }

  /**
   * @brief Get the latest event in the log.
   *
   * @thread_safe
   *
   */
  Event Latest() const {
    LockGuard guard(lock);

    return events.back();
  }

  /**
   * @brief Get the first event in the log.
   *
   * @thread_safe
   *
   */
  Event First() const {
    LockGuard guard(lock);

    return events.front();
  }

  /**
   * @brief Check if the log contains the given event.
   *
   * @thread_safe
   *
   * @param event Constant reference to the event to check
   * @returns `true` if the list contains the event else `false`
   */
  bool Contains(const Event &event) const {
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
   * @brief Check if the log contains the given event.
   *
   * @thread_safe
   *
   * @param event Lvalue reference to the event to check
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
   * @brief Get size of the log.
   *
   * @thread_safe
   *
   * @returns Number of events in the log
   */
  size_t Size() const {
    LockGuard guard(lock);

    return events.size();
  }

  /**
   * @brief Equality comparision operator.
   *
   * @thread_safe
   *
   */
  bool operator==(const std::list<Event> &other) const {
    LockGuard guard(lock);

    return events == other;
  }
};

} // namespace tstest

#endif /* TSTEST_CORE_EVENT_LOG_HPP */
