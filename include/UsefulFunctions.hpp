#pragma once

#include "AbstractLesson.hpp"

/**
* The purpose of this is to learn how to pass variables by reference to theads
*/
class UsefulFunctions: public AbstractLesson
{
private:
  using clock = std::chrono::system_clock;
  using ms = std::chrono::milliseconds;
  
  static void getThreadID();
  static void bar();

  void getIDTest();
  void sleepTest();

public:
  virtual void run() override;
};