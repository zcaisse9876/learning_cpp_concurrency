#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// just introducing an abstract base class that has a virtual run method that needs to be implemented
// exposes all common concurrency headers I might need
// gives some organization to the repository
class AbstractLesson
{
public:
  virtual void run() = 0;
};