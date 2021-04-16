#include "ByReference.hpp"

/**
* This function runs an infinite loop that prints the value of the reference to x, then sleeps for 1 second
*/
void ByReference::foo(int& x)
{
  while (true)
  {
    std::cout << "Thread " << std::this_thread::get_id() << " value of x - " << x << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void ByReference::run()
{
  int x = 9;
  std::cout << "Main Thread " << std::this_thread::get_id() << " value of x - " << x << std::endl;

  std::thread thread1(ByReference::foo, std::ref(x));
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  x = 15;
  std::cout << "Main Thread " << std::this_thread::get_id() << " value of x has been changed to - " << x << std::endl;
  thread1.join();
}