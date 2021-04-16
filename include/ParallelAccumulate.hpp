#pragma once

#include "AbstractLesson.hpp"
#include "Useful.hpp"
#include <vector>
#include <numeric>
#include <functional>

/**
* The purpose of this is to learn how to use std::thread to implement a parralel version of std::accumulate
*/
class ParallelAccumulate: public AbstractLesson
{
private:
  // Probably bad practice to declare templated function in header file but im going for it anyway
  // no binary operation
  template <typename InputIt, typename T, typename BinaryOp>
  static T accumulate(InputIt, InputIt, T, BinaryOp);

  // mimics std::accumulate default binary operation std::plus<T>()
  template <typename InputIt, typename T>
  static T accumulate(InputIt, InputIt, T);

public:
  virtual void run() override;
};