/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief EventLog Class Tests
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

#include <tstest/core/event_log.hpp>

using namespace tstest;

class EventLogTestFixture : public ::testing::Test {
protected:
  std::unique_ptr<EventLog> event_log;
  void SetUp() override { event_log = std::make_unique<EventLog>(); }
  void TearDown() override {}
};

TEST_F(EventLogTestFixture, TestPush) {
  std::thread thread_a([&]() {
    event_log->Push({"test_event-a", Event::Type::BEGIN});
  });
  std::thread thread_b([&]() {
    event_log->Push({"test_event-b", Event::Type::BEGIN});
  });

  thread_a.join();
  thread_b.join();

  ASSERT_TRUE(event_log->Contains({"test_event-a", Event::Type::BEGIN}));
  ASSERT_TRUE(event_log->Contains({"test_event-b", Event::Type::BEGIN}));
}

TEST_F(EventLogTestFixture, TestLatest) {
  event_log->Push({"test_event-first", Event::Type::BEGIN});
  event_log->Push({"test_event-last", Event::Type::BEGIN});

  ASSERT_EQ(event_log->Latest(), Event("test_event-last", Event::Type::BEGIN));
}

TEST_F(EventLogTestFixture, TestFirst) {
  event_log->Push({"test_event-first", Event::Type::BEGIN});
  event_log->Push({"test_event-last", Event::Type::BEGIN});

  ASSERT_EQ(event_log->First(), Event("test_event-first", Event::Type::BEGIN));
}

TEST_F(EventLogTestFixture, TestSize) {
  event_log->Push({"test_event-first", Event::Type::BEGIN});
  event_log->Push({"test_event-last", Event::Type::BEGIN});

  ASSERT_EQ(event_log->Size(), 2);
}

TEST_F(EventLogTestFixture, TestEqualityOperator) {
  event_log->Push({"test_event-first", Event::Type::BEGIN});
  event_log->Push({"test_event-last", Event::Type::BEGIN});

  std::list<Event> events = {{"test_event-first", Event::Type::BEGIN},
                             {"test_event-last", Event::Type::BEGIN}};

  ASSERT_TRUE(*event_log == events);
}
