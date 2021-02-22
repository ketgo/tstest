/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief Tstest Interface Tests
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

#include <tstest/tstest.hpp>

using namespace tstest;

class TSTestTestFixture : public ::testing::Test {
protected:
  std::unique_ptr<Assertor> assertor;
  std::unique_ptr<Runner> runner;
  void SetUp() override {
    // Setup assertor
    assertor = std::make_unique<Assertor>();

    // Setup runner
    runner = std::make_unique<Runner>();
  }
  void TearDown() override {}
};

TEST_F(TSTestTestFixture, TestInterface) {
  // Inserting thread function a
  THREAD((*runner), "test-thread-a") {
    int i;
    OPERATION("test_operation-a", i = 1);
  };

  // Inserting thread function b
  THREAD((*runner), "test-thread-b") {
    OPERATION("test_operation-b", int j = 1);
  };

  // Running thread functions
  runner->Run();

  // Assert operational event logs for the two threads
  const EventLog &event_log_ = runner->GetEventLog();
  ASSERT_TRUE(event_log_.Contains({"test_operation-a", Event::Type::BEGIN}));
  ASSERT_TRUE(event_log_.Contains({"test_operation-a", Event::Type::END}));
  ASSERT_TRUE(event_log_.Contains({"test_operation-b", Event::Type::BEGIN}));
  ASSERT_TRUE(event_log_.Contains({"test_operation-b", Event::Type::END}));
}
