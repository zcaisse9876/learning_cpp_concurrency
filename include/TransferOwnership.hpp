#pragma once

#include "AbstractLesson.hpp"

/**
* The purpose of this is to learn how to pass variables by reference to theads
*/
class TransferOwnership: public AbstractLesson
{
private:
  static void foo();
  static void bar();

public:
  virtual void run() override;
};