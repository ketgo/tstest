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
  std::unique_ptr<Event> beginEvent, endEvent;
  void SetUp() override {
    beginEvent = std::make_unique<Event>("test-event", Event::Type::BEGIN);
    endEvent = std::make_unique<Event>("test-event", Event::Type::END);
  }
  void TearDown() override {}
};

TEST_F(EventTestFixture, TestGetType) {
  ASSERT_EQ(beginEvent->getType(), Event::Type::BEGIN);
  ASSERT_EQ(endEvent->getType(), Event::Type::END);
}

TEST_F(EventTestFixture, TestGetName) {
  ASSERT_EQ(beginEvent->getName(), "test-event");
  ASSERT_EQ(endEvent->getName(), "test-event");
}

TEST_F(EventTestFixture, TestEquality) {
  ASSERT_TRUE(*beginEvent == Event("test-event", Event::Type::BEGIN));
  ASSERT_TRUE(*endEvent == Event("test-event", Event::Type::END));
}

TEST_F(EventTestFixture, TestInEquality) {
  ASSERT_TRUE(*beginEvent != Event("test-event-other", Event::Type::BEGIN));
  ASSERT_TRUE(*endEvent != Event("test-event-other", Event::Type::END));
}
