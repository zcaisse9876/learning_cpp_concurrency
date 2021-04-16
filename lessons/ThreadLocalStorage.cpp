#include <ThreadLocalStorage.hpp>

// Storage duration specifier that will create individual instances in each thread
thread_local std::atomic<int> ThreadLocalStorage::i{0};
std::atomic<int> ThreadLocalStorage::j{0};

// Just increment the static variables of Thread local and print them
void ThreadLocalStorage::foo()
{
  std::cout << "i: " << ++ThreadLocalStorage::i << std::endl;
  std::cout << "j: " << ++ThreadLocalStorage::j << std::endl;
}

// start three threads running function foo,
// in each thread, the behavior will be different for static variables i and j due to the duration storage specifier
void ThreadLocalStorage::run()
{
  std::thread t1(ThreadLocalStorage::foo);
  std::thread t2(ThreadLocalStorage::foo);
  std::thread t3(ThreadLocalStorage::foo);

  t1.join();
  t2.join();
  t3.join();

  std::cout << "Main Thread i: " << ThreadLocalStorage::i << std::endl;
  std::cout << "Main Thread j: " << ThreadLocalStorage::j << std::endl;
}