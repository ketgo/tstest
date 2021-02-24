/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_CORE_ALGORITHM_HPP
#define TSTEST_CORE_ALGORITHM_HPP

#include <algorithm>
#include <unordered_map>

#include <tstest/core/event.hpp>

namespace tstest {

/**
 * @brief Get the list of all possible permutations of event sequences for given
 * sequence of events.
 *
 * @param event_list Constant reference to the list of events for which
 * permutations are computed
 * @param output Reference to vector of type EventList where computed
 * permutations are stored
 */
static void GetAllPermutations(const EventList &event_list,
                               std::vector<EventList> &output) {
  // Copy event list
  EventList event_list_ = event_list;
  // Create thread ranking
  std::unordered_map<ThreadName, uint64_t> thread_ranks;
  for (auto &event : event_list_) {
    if (thread_ranks.find(event.GetThreadName()) == thread_ranks.end()) {
      thread_ranks.insert({event.GetThreadName(), thread_ranks.size()});
    }
  }
  // Compare lambda function
  auto compare = [&](const Event &a, const Event &b) -> bool {
    if (thread_ranks[a.GetThreadName()] < thread_ranks[b.GetThreadName()]) {
      return true;
    }
    return false;
  };
  // Compute permutations
  do {
    output.push_back(event_list_);
  } while (
      std::next_permutation(event_list_.begin(), event_list_.end(), compare));
}

} // namespace tstest

#endif /* TSTEST_CORE_ALGORITHM_HPP */
