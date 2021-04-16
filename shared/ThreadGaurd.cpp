#include "ThreadGaurd.hpp"

/**
* ThreadGuard constructor, keeps reference to thread in member variable t_
*/
ThreadGaurd::ThreadGaurd(std::thread &t) : t_(t)
{
  std::cout << "ThreadGaurd constructed for thread " << t_.get_id() << std::endl;
}

/**
* ThreadGaurd destructor, checks if thread is joinable. join if joinable.
*/
ThreadGaurd::~ThreadGaurd()
{
  std::cout << "ThreadGuard destructed for thread " << t_.get_id() << " - " << (t_.joinable() ? "joined" : "already joined") << std::endl;
  if (t_.joinable())
    t_.join();
}