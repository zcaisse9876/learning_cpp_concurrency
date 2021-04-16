#pragma once

#include <iostream>

namespace Useful {
  template <typename T>
  void printCont(const T& c)
  {
    for (const auto& n: c)
      std::cout << n << " ";

    std::cout << std::endl;
  }
} // namespace Useful