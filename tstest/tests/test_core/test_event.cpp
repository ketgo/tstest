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
