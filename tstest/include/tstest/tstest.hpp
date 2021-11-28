/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef TSTEST_HPP
#define TSTEST_HPP

#include <tstest/details/assertor.hpp>
#include <tstest/details/runner.hpp>

namespace tstest {

/**
 * @brief The class represents an operational event. It contaians the name of
 * the operation and the type of event. Currently only the following event types
 * are supported:
 *
 * - BEGIN
 * - END
 *
 */
typedef tstest::details::Event Event;

/**
 * @brief An execution context contains contextual information required when
 * executing a thread function by the `Runner`.
 *
 */
typedef tstest::details::ExecutionContext ExecutionContext;

/**
 * @brief The runner executes set of operations to be tested for thread safety
 * in one or more threads, as configured by the user.
 *
 */
typedef tstest::details::Runner Runner;

/**
 * @brief An assertor maps one or more sequence of events to user provided
 * assertion functions via dispatch table. The assertion function asserts the
 * expected behavior for an observed mapped event sequence.
 *
 * @note The class is not thread safe.
 *
 */
typedef tstest::details::Assertor Assertor;

}  // namespace tstest

/**
 * @brief Macro used to define a thread function.
 *
 * @example
 *
 *  Runner runner;
 *
 *  THREAD(runner, "example-thread") {
 *    ...
 *  };
 *
 */
#define THREAD(Runner, Name) \
  Runner[Name] = [&](tstest::ExecutionContext context)

/**
 * @brief Macro to define an operation.
 *
 * @example
 *
 *  Runner runner;
 *
 *  THREAD(runner, "example-thread") {
 *    OPERATION("example-operation", int i=1);
 *  };
 *
 */
#define OPERATION(Name, Expression) \
  context.LogOperationBegin(Name);  \
  Expression;                       \
  context.LogOperationEnd(Name);

#endif /* TSTEST_HPP */
