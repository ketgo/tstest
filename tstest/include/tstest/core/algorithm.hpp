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
#include <vector>

#include <tstest/core/event.hpp>

namespace tstest {

/**
 * @brief Get the list of all possible schedules of event sequences for given
 * sequence of events.
 *
 * @param event_list Constant reference to the list of events for which
 * permutations are computed
 * @param output Reference to vector of type EventList where computed
 * permutations are stored
 */
class GetAllSchedules {
  typedef std::vector<unsigned int> IndexVector;
  typedef std::vector<Event> EventVector;

private:
  // Vector of events
  EventVector events;
  // Event topological ranks
  std::unordered_map<Event, unsigned int, EventHash> event_rank;
  // Number of events per thread
  std::unordered_map<ThreadName, unsigned int> events_count;

  /**
   * @brief Initialize variables needed for the algorithm.
   *
   */
  void Initialize(const EventList &event_list) {
    for (const auto &event : event_list) {
      const ThreadName &thread_name = event.GetThreadName();
      const OperationName &operation_name = event.GetOperationName();
      // Check if thread present in events_count map
      if (events_count.find(thread_name) == events_count.end()) {
        events_count.insert({thread_name, 0});
      }
      // Fill event rank
      event_rank[event] = events_count[thread_name];
      events_count[thread_name] += 1;
      // Fill event vector
      events.push_back(event);
    }
  }

  /**
   * @brief Helper method to get all permutations of index vector
   *
   */
  void GetIndexPermutations(unsigned int size,
                            std::vector<IndexVector> &output) {
    // Create ordered list of indexes
    IndexVector idx_list(size);
    for (unsigned int i = 0; i < size; ++i) {
      idx_list[i] = i;
    }
    // Compute permutations
    do {
      output.push_back(idx_list);
    } while (std::next_permutation(idx_list.begin(), idx_list.end()));
  }

  /**
   * @brief Insert permutation to output vector only if chronological order is
   * maintained.
   *
   */
  bool Insert(std::vector<EventList>::iterator &it,
              const IndexVector &idx_vector) {
    // Map containing thread name and previous index as key value pairs
    std::unordered_map<ThreadName, unsigned int> prev_idx;
    // Insert permutation
    for (const auto &idx : idx_vector) {
      const Event &event = events[idx];
      const ThreadName &thread_name = event.GetThreadName();
      // Check for previous index
      if (prev_idx.find(thread_name) == prev_idx.end()) {
        it->push_back(event);
        prev_idx[thread_name] = idx;
      } else {
        Event &prev_event = events[prev_idx[thread_name]];
        if (event_rank[event] < event_rank[prev_event]) {
          return false;
        }
        it->push_back(event);
      }
    }
    return true;
  }

public:
  void operator()(const EventList &event_list, std::vector<EventList> &output) {
    // Initialize
    Initialize(event_list);

    // Compute all permutations of events
    std::vector<IndexVector> idx_list_permutations;
    GetIndexPermutations(event_list.size(), idx_list_permutations);

    // Write all permutations
    for (const auto &idx_vector : idx_list_permutations) {
      output.push_back({});
      auto it = std::prev(output.end());
      if (!Insert(it, idx_vector)) {
        output.erase(it);
      }
    }
  }
};

} // namespace tstest

#endif /* TSTEST_CORE_ALGORITHM_HPP */
