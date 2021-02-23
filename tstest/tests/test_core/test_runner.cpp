/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief Runner Class Tests
 *
 */

#include <gtest/gtest.h>

#include <memory>
#include <string>

/**
 * @brief Enable debug mode if not already enabled
 *
 */
#ifndef __TSTEST_DEBUG__
#define __TSTEST_DEBUG__
#endif

#include <tstest/core/runner.hpp>

using namespace tstest;

class RunnerTestFixture : public ::testing::Test {
protected:
  std::unique_ptr<EventLog> event_log;
  std::unique_ptr<Runner> runner;
  void SetUp() override {
    // Setup event log
    event_log = std::make_unique<EventLog>();

    // Setup runner
    runner = std::make_unique<Runner>();
  }
  void TearDown() override {}
};

TEST_F(RunnerTestFixture, TestInsert) {
  // Inserting thread function
  (*runner)["test"] = [&](ExecutionContext context) {
    context.LogOperationBegin("test_operation");
  };
  // Running assertion function
  ExecutionContext context(event_log.get(), "test");
  (*runner)["test"](context);

  ASSERT_TRUE(
      event_log->Contains({"test", "test_operation", Event::Type::BEGIN}));
}

TEST_F(RunnerTestFixture, TestRemove) {
  // Remove non-existing thread function
  ASSERT_EQ(runner->Remove("test"), 0);

  // Inserting and then removing a thread function
  (*runner)["test"] = [&](ExecutionContext context) {
    context.LogOperationBegin("test_operation");
  };
  ASSERT_EQ(runner->Remove("test"), 1);
}

TEST_F(RunnerTestFixture, TestRun) {
  // Inserting thread function a
  (*runner)["test-thread-a"] = [&](ExecutionContext context) {
    context.LogOperationBegin("test_operation-a");
  };

  // Inserting thread function b
  (*runner)["test-thread-b"] = [&](ExecutionContext context) {
    context.LogOperationBegin("test_operation-b");
  };

  // Running thread functions
  runner->Run();

  // Assert operational event logs for the two threads
  const EventLog &event_log_ = runner->GetEventLog();
  ASSERT_TRUE(event_log_.Contains(
      {"test-thread-a", "test_operation-a", Event::Type::BEGIN}));
  ASSERT_TRUE(event_log_.Contains(
      {"test-thread-b", "test_operation-b", Event::Type::BEGIN}));
}
