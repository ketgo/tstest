/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_HPP
#define TSTEST_HPP

#include <tstest/core/assertor.hpp>
#include <tstest/core/runner.hpp>

/**
 * @brief Macro used to define a thread function.
 *
 * @example
 *
 *  Runner runner;
 *
 *  THREAD(runner, "example-thread") {
 *    ...
 *  }
 *
 */
#define THREAD(Runner, Name) Runner[Name] = [&](ExecutionContext context)

/**
 * @brief Macro to define an operation.
 *
 * @example
 *
 *  Runner runner;
 *
 *  THREAD(runner, "example-thread") {
 *    OPERATION("example-operation", int i=1);
 *  }
 *
 */
#define OPERATION(Name, Expression)                                            \
  context.LogOperationBegin(Name);                                             \
  Expression;                                                                  \
  context.LogOperationEnd(Name);

#endif /* TSTEST_HPP */
