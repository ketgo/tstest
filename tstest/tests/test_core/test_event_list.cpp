/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief Buffer Manager Thread Safety Tests
 *
 */

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <thread>

/**
 * @brief Enable debug mode if not already enabled
 *
 */
#ifndef __TSTEST_DEBUG__
#define __TSTEST_DEBUG__
#endif

#include <tstest/core/event_list.hpp>

using namespace tstest;

class EventListTestFixture : public ::testing::Test {
protected:
  std::unique_ptr<EventList> event_list;
  void SetUp() override { event_list = std::make_unique<EventList>(); }
  void TearDown() override {}
};

TEST_F(EventListTestFixture, TestPush) {
  std::thread thread_a([&]() {
    event_list->Push({"test_event-a", Event::Type::BEGIN});
  });
  std::thread thread_b([&]() {
    event_list->Push({"test_event-b", Event::Type::BEGIN});
  });

  thread_a.join();
  thread_b.join();

  ASSERT_TRUE(event_list->Contains({"test_event-a", Event::Type::BEGIN}));
  ASSERT_TRUE(event_list->Contains({"test_event-b", Event::Type::BEGIN}));
}

TEST_F(EventListTestFixture, TestLatest) {
  event_list->Push({"test_event-first", Event::Type::BEGIN});
  event_list->Push({"test_event-last", Event::Type::BEGIN});

  ASSERT_EQ(event_list->Latest(), Event("test_event-last", Event::Type::BEGIN));
}

TEST_F(EventListTestFixture, TestFirst) {
  event_list->Push({"test_event-first", Event::Type::BEGIN});
  event_list->Push({"test_event-last", Event::Type::BEGIN});

  ASSERT_EQ(event_list->First(), Event("test_event-first", Event::Type::BEGIN));
}

TEST_F(EventListTestFixture, TestSize) {
  event_list->Push({"test_event-first", Event::Type::BEGIN});
  event_list->Push({"test_event-last", Event::Type::BEGIN});

  ASSERT_EQ(event_list->Size(), 2);
}

TEST_F(EventListTestFixture, TestEqualityOperator) {
  event_list->Push({"test_event-first", Event::Type::BEGIN});
  event_list->Push({"test_event-last", Event::Type::BEGIN});

  std::list<Event> events = {{"test_event-first", Event::Type::BEGIN},
                             {"test_event-last", Event::Type::BEGIN}};

  ASSERT_TRUE(*event_list == events);
}
