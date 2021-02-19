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
    event_log->Push({"test_event-b", Event::Type::BEGIN});

    // Setup assertor
    assertor = std::make_unique<Assertor>();
  }
  void TearDown() override {}
};

TEST_F(AssertorTestFixture, TestInsert) {}
