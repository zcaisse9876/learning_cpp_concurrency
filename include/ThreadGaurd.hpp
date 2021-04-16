#pragma once

#include <thread>
#include <iostream>

/**
* ThreadGaurd class, utilizes RAII to ensure thread is joined when object exits scope
*/
class ThreadGaurd
{
private:
  std::thread& t_;

public:
  explicit ThreadGaurd(std::thread& t);
  ~ThreadGaurd();

  ThreadGaurd(const ThreadGaurd&) = delete;
  ThreadGaurd& operator=(const ThreadGaurd&) = delete;
};