/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

/**
 * @brief EvaluationContex Class Tests
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

#include <tstest/details/context.hpp>

using namespace tstest::details;

class ExecutionContextTestFixture : public ::testing::Test {
protected:
  const std::string thread_name = "test";
  std::unique_ptr<EventLog> event_log;
  std::unique_ptr<ExecutionContext> context;
  void SetUp() override {
    // Setup event log
    event_log = std::make_unique<EventLog>();

    // Setup assertor
    context = std::make_unique<ExecutionContext>(event_log.get(), thread_name);
  }
  void TearDown() override {}
};

TEST_F(ExecutionContextTestFixture, TestLogOperationBegin) {
  context->LogOperationBegin("test_operation");
  ASSERT_TRUE(
      event_log->Contains({thread_name, "test_operation", Event::Type::BEGIN}));
}

TEST_F(ExecutionContextTestFixture, TestLogOperationEnd) {
  context->LogOperationEnd("test_operation");
  ASSERT_TRUE(
      event_log->Contains({thread_name, "test_operation", Event::Type::END}));
}
