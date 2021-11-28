/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief Event Class Tests
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

#include <tstest/details/event.hpp>

using namespace tstest::details;

class EventTestFixture : public ::testing::Test {
protected:
  const std::string thread_name = "test";
  std::unique_ptr<Event> begin_event, end_event;
  void SetUp() override {
    begin_event =
        std::make_unique<Event>(thread_name, "test-event", Event::Type::BEGIN);
    end_event =
        std::make_unique<Event>(thread_name, "test-event", Event::Type::END);
  }
  void TearDown() override {}
};

TEST_F(EventTestFixture, TestGetType) {
  ASSERT_EQ(begin_event->GetEventType(), Event::Type::BEGIN);
  ASSERT_EQ(end_event->GetEventType(), Event::Type::END);
}

TEST_F(EventTestFixture, TestGetOperationName) {
  ASSERT_EQ(begin_event->GetOperationName(), "test-event");
  ASSERT_EQ(end_event->GetOperationName(), "test-event");
}

TEST_F(EventTestFixture, TestGetThreadName) {
  ASSERT_EQ(begin_event->GetThreadName(), thread_name);
  ASSERT_EQ(end_event->GetThreadName(), thread_name);
}

TEST_F(EventTestFixture, TestToString) {
  ASSERT_EQ(begin_event->ToString(), "{\"test\", \"test-event\", tstest::Event::Type::BEGIN}");
  ASSERT_EQ(end_event->ToString(), "{\"test\", \"test-event\", tstest::Event::Type::END}");
}

TEST_F(EventTestFixture, TestEquality) {
  ASSERT_TRUE(*begin_event ==
              Event(thread_name, "test-event", Event::Type::BEGIN));
  ASSERT_TRUE(*end_event == Event(thread_name, "test-event", Event::Type::END));
}

TEST_F(EventTestFixture, TestInEquality) {
  ASSERT_TRUE(*begin_event !=
              Event(thread_name, "test-event-other", Event::Type::BEGIN));
  ASSERT_TRUE(*end_event !=
              Event(thread_name, "test-event-other", Event::Type::END));
}

/**
 * @brief EventHash Class Tests
 *
 */

TEST(EventHashTestFixture, TestHashValue) {
  EventHash event_hash;
  Event begin_event("test", "test-event", Event::Type::BEGIN);
  Event end_event("test", "test-event", Event::Type::END);

  size_t begin_event_hash = event_hash(begin_event);
  size_t begin_event_hash_expected = 20698882074881470U;
  size_t end_event_hash = event_hash(end_event);
  size_t end_event_hash_expected = 14982950806565649480U;

  ASSERT_EQ(begin_event_hash, begin_event_hash_expected);
  ASSERT_EQ(end_event_hash, end_event_hash_expected);
}

/**
 * @brief EventListHash Class Tests
 *
 */

TEST(EventListHashTestFixture, TestHashValue) {
  EventListHash event_list_hash;
  EventList event_list = {{"test", "test-event", Event::Type::BEGIN},
                          {"test", "test-event", Event::Type::END}};

  size_t hash = event_list_hash(event_list);
  size_t hash_expected = 16297242731351833291U;

  ASSERT_EQ(hash, hash_expected);
}
