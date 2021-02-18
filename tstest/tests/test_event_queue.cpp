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

#include <tstest/core/event_queue.hpp>

using namespace tstest;

class EventQueueTestFixture : public ::testing::Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(EventQueueTestFixture, Test) {}