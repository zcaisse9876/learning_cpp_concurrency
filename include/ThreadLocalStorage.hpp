#pragma once

#include "AbstractLesson.hpp"

class ThreadLocalStorage: public AbstractLesson
{
private:
  static void foo();

public:
  static thread_local std::atomic<int> i;
  static std::atomic<int> j;
  virtual void run() override;
};