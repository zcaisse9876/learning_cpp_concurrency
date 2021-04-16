#pragma once

#include "AbstractLesson.hpp"

/**
* The purpose of this is to learn how to pass variables by reference to theads
*/
class ByReference: public AbstractLesson
{
private:
  static void foo(int& x);

public:
  virtual void run() override;
};