/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief Algorithm Tests
 *
 */

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

/**
 * @brief Enable debug mode if not already enabled
 *
 */
#ifndef __TSTEST_DEBUG__
#define __TSTEST_DEBUG__
#endif

#include <tstest/core/algorithm.hpp>

using namespace tstest;

TEST(TestAlgorithm, TestGetAllPermutations) {
  EventList event_list = {
      {"1", "a", Event::Type::BEGIN}, {"1", "b", Event::Type::BEGIN},
      {"2", "a", Event::Type::BEGIN}, {"2", "b", Event::Type::BEGIN},
      //{"2", "b", Event::Type::BEGIN}, {"2", "b", Event::Type::END},
  };
  std::vector<EventList> permutations;

  GetAllPermutations(event_list, permutations);

  int count = 0;
  for (auto &event_list_ : permutations) {
    std::cout << "SEQUENCE: " << count << "\n";
    for (auto &event : event_list_) {
      std::cout << "\t" << event.ToString() << "\n";
    }
    count++;
  }
}
