#include "TransferOwnership.hpp"

void TransferOwnership::foo()
{
  std::cout << "Method foo from thread -- " << std::this_thread::get_id() << std::endl;
}

void TransferOwnership::bar()
{
  std::cout << "Method bar from thread -- " << std::this_thread::get_id() << std::endl;
}

void TransferOwnership::run()
{
  std::thread t1(TransferOwnership::foo);

  // Below throws error at compile time. No copy constructor for std::thread
  // std::thread t2 = t1;

  std::thread t2 = std::move(t1);

  // The below compiles but will cause an error at runtime, we have to manage the life cycle of the thread with join or detach. Can't just dump existing t1
  // std::thread t3(TransferOwnership::bar);
  // t1 = std::move(t3);

  std::cout << "t1 after moved joinable status: " << t1.joinable() << std::endl;

  // Implicit std::move on temporary r-value
  t1 = std::thread(bar);
  t1.join();
  t2.join();
}