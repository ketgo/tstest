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

TEST(TestAlgorithm, TestGetAllSchedules) {
  EventList event_list = {
      {"1", "a", Event::Type::BEGIN},
      {"1", "a", Event::Type::END},
      {"2", "a", Event::Type::BEGIN},
      {"2", "a", Event::Type::END},
  };
  std::vector<EventList> permutations;

  GetAllSchedules()(event_list, permutations);

  std::vector<EventList> expected = {{{"1", "a", tstest::Event::Type::BEGIN},
                                      {"1", "a", tstest::Event::Type::END},
                                      {"2", "a", tstest::Event::Type::BEGIN},
                                      {"2", "a", tstest::Event::Type::END}},
                                     {{"1", "a", tstest::Event::Type::BEGIN},
                                      {"2", "a", tstest::Event::Type::BEGIN},
                                      {"1", "a", tstest::Event::Type::END},
                                      {"2", "a", tstest::Event::Type::END}},
                                     {{"1", "a", tstest::Event::Type::BEGIN},
                                      {"2", "a", tstest::Event::Type::BEGIN},
                                      {"2", "a", tstest::Event::Type::END},
                                      {"1", "a", tstest::Event::Type::END}},
                                     {{"2", "a", tstest::Event::Type::BEGIN},
                                      {"1", "a", tstest::Event::Type::BEGIN},
                                      {"1", "a", tstest::Event::Type::END},
                                      {"2", "a", tstest::Event::Type::END}},
                                     {{"2", "a", tstest::Event::Type::BEGIN},
                                      {"1", "a", tstest::Event::Type::BEGIN},
                                      {"2", "a", tstest::Event::Type::END},
                                      {"1", "a", tstest::Event::Type::END}},
                                     {{"2", "a", tstest::Event::Type::BEGIN},
                                      {"2", "a", tstest::Event::Type::END},
                                      {"1", "a", tstest::Event::Type::BEGIN},
                                      {"1", "a", tstest::Event::Type::END}}};

  ASSERT_EQ(permutations, expected);
}
