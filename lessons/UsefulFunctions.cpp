#include "UsefulFunctions.hpp"

void UsefulFunctions::getThreadID()
{
  std::cout << "This thread id - " << std::this_thread::get_id() << std::endl;
}

void UsefulFunctions::bar()
{
  auto sleepTime = ms(5000);
  auto before = clock::now();
  std::cout << "Thread " << std::this_thread::get_id() << " is going to sleep for " << std::dec << sleepTime.count() << "ms" << std::endl;

  // This thread does not sleep for exactly 5000ms, it is gauranteed to sleep for AT LEAST 5000 ms but can take more depending on task scheduler implementation and resource contention
  std::this_thread::sleep_for(sleepTime);
  auto duration = clock::now() - before;
  std::cout << "Thread " << std::this_thread::get_id() << " woke up after " << std::dec << duration.count() / 1000000 << "ms" << std::endl;
}

void UsefulFunctions::getIDTest()
{
  std::thread thread1(UsefulFunctions::getThreadID);
  std::thread thread2(UsefulFunctions::getThreadID);
  std::thread thread3(UsefulFunctions::getThreadID);

  // Can get the id from an instance of std::thread
  std::cout << "thread1 - " << thread1.get_id() << std::endl;
  std::cout << "thread2 - " << thread2.get_id() << std::endl;
  std::cout << "thread3 - " << thread3.get_id() << std::endl;

  thread1.join();
  thread2.join();
  thread3.join();
}

// exploring sleep_for, yield, hardware_concurrency
void UsefulFunctions::sleepTest()
{
  int nThreads = std::thread::hardware_concurrency();
  std::cout << "Maximum concurrent threads allowed by this device: " << nThreads << std::endl;

  std::thread thread1(UsefulFunctions::bar);
  thread1.join();
}

void UsefulFunctions::run()
{
  this->getIDTest();
  this->sleepTest();
}