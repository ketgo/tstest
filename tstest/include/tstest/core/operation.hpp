/**
 * Copyright (c) 2021 Ketan Goyal
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OPERATION_HPP
#define OPERATION_HPP

#include <string>

namespace tstest {

/**
 * @brief Operation Class
 *
 */
class Operation {
private:
  /**
   * @brief name of the operation
   *
   */
  std::string name;

public:
  /**
   * @brief
   *
   */
  void run();
};

} // namespace tstest

#endif /* OPERATION_HPP */
