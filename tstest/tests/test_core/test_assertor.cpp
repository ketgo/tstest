/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief Assertor Class Tests
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

#include <tstest/core/assertor.hpp>

using namespace tstest;

class AssertorTestFixture : public ::testing::Test {
protected:
  std::unique_ptr<EventLog> event_log;
  std::unique_ptr<Assertor> assertor;
  void SetUp() override {
    // Setup event log
    event_log = std::make_unique<EventLog>();
    event_log->Push({"test_event-a", Event::Type::BEGIN});
    event_log->Push({"test_event-a", Event::Type::END});

    // Setup assertor
    assertor = std::make_unique<Assertor>();
  }
  void TearDown() override {}
};

TEST_F(AssertorTestFixture, TestInsert) {
  bool flag = false; // Flag indicating if an assertion function was executed
  EventList event_list = {{"test_event-a", Event::Type::BEGIN},
                          {"test_event-a", Event::Type::END}};
  AssertionFunction assertion_function = [&]() { flag = true; };

  // Inserting assertion function
  assertor->Insert(event_list, assertion_function);
  // Running assertion function
  assertor->Get(event_list)();

  ASSERT_TRUE(flag);
}

TEST_F(AssertorTestFixture, TestRemove) {
  bool flag = false; // Flag indicating if an assertion function was executed
  EventList event_list = {{"test_event-a", Event::Type::BEGIN},
                          {"test_event-a", Event::Type::END}};
  AssertionFunction assertion_function = [&]() { flag = true; };

  // Remove non-existing assertion function
  ASSERT_EQ(assertor->Remove(event_list), 0);

  // Inserting and then removing the assertion function
  assertor->Insert(event_list, assertion_function);
  ASSERT_EQ(assertor->Remove(event_list), 1);
}

TEST_F(AssertorTestFixture, TestAssert) {
  ASSERT_THROW(assertor->Assert(*event_log), NoAssertionFunctionFound);

  bool flag = false; // Flag indicating if an assertion function was executed
  EventList event_list = {{"test_event-a", Event::Type::BEGIN},
                          {"test_event-a", Event::Type::END}};
  AssertionFunction assertion_function = [&]() { flag = true; };
  assertor->Insert(event_list, assertion_function);
  assertor->Assert(*event_log);

  ASSERT_TRUE(flag);
}

TEST_F(AssertorTestFixture, TestAssertDefault) {
  ASSERT_THROW(assertor->Assert(*event_log), NoAssertionFunctionFound);

  bool flag = false; // Flag indicating if an assertion function was executed
  EventList event_list = {{"test_event-a", Event::Type::BEGIN},
                          {"test_event-a", Event::Type::END}};
  AssertionFunction assertion_function = [&]() { flag = true; };
  assertor->Assert(*event_log, assertion_function);

  ASSERT_TRUE(flag);
}
