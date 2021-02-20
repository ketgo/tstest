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

#include <tstest/core/event.hpp>

using namespace tstest;

class EventTestFixture : public ::testing::Test {
protected:
  std::unique_ptr<Event> begin_event, end_event;
  void SetUp() override {
    begin_event = std::make_unique<Event>("test-event", Event::Type::BEGIN);
    end_event = std::make_unique<Event>("test-event", Event::Type::END);
  }
  void TearDown() override {}
};

TEST_F(EventTestFixture, TestGetType) {
  ASSERT_EQ(begin_event->GetType(), Event::Type::BEGIN);
  ASSERT_EQ(end_event->GetType(), Event::Type::END);
}

TEST_F(EventTestFixture, TestGetName) {
  ASSERT_EQ(begin_event->GetName(), "test-event");
  ASSERT_EQ(end_event->GetName(), "test-event");
}

TEST_F(EventTestFixture, TestEquality) {
  ASSERT_TRUE(*begin_event == Event("test-event", Event::Type::BEGIN));
  ASSERT_TRUE(*end_event == Event("test-event", Event::Type::END));
}

TEST_F(EventTestFixture, TestInEquality) {
  ASSERT_TRUE(*begin_event != Event("test-event-other", Event::Type::BEGIN));
  ASSERT_TRUE(*end_event != Event("test-event-other", Event::Type::END));
}

/**
 * @brief EventHash Class Tests
 *
 */

TEST(EventHashTestFixture, TestHashValue) {
  EventHash event_hash;
  Event begin_event("test-event", Event::Type::BEGIN);
  Event end_event("test-event", Event::Type::END);

  size_t begin_event_hash = event_hash(begin_event);
  size_t begin_event_hash_expected = 2925993893350407644U;
  size_t end_event_hash = event_hash(end_event);
  size_t end_event_hash_expected = 15990077341322827889U;

  ASSERT_EQ(begin_event_hash, begin_event_hash_expected);
  ASSERT_EQ(end_event_hash, end_event_hash_expected);
}
