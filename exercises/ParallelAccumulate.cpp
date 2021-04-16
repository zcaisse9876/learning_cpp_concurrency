#include "ParallelAccumulate.hpp"

template <typename InputIt, typename T, typename BinaryOp>
T ParallelAccumulate::accumulate(InputIt first, InputIt last, T init, BinaryOp op)
{
  // Minimum number of values being operated on to actually justify the overhead of spawning threads
  const int minValues = 100;

  // The maximum number of threads supported by the current hardware. if we spawn more than this then we will not have any performance gain
  int maxThreads = std::thread::hardware_concurrency();

  // The number of elements to be operated on
  int sz = std::distance(first, last);

  // The number of threads to use, including the main thread
  int nThreads = sz < minValues ? 1 : maxThreads;

  // To keep handles to threads that are spawned. main thread at index 0
  std::vector<std::thread> threadPool(nThreads);

  // To keep the results from each thread spawned. main thread at index 0
  std::vector<T> results(nThreads);

  // The blockSize to be operated on by each thread
  int blockSize = sz / nThreads;

  // The single threaded accumulate function to be used by each thread, takes start and end iterator, and reference to where the value should be stored
  auto accum = [&op](InputIt first, InputIt last, T& i) {
    // If first == last, just return. nothing to operate on
    if (first == last)
      return;

    // get starting value
    T result = i;

    // iterate until first reaches end, adding value to result;
    while(first++ != last)
      result = op(result, *first);
    
    // set reference to i to the value result;
    i = result;
  };

  InputIt mainLast = last;
  if (blockSize != sz)
  {
    mainLast = first;
    std::advance(mainLast, blockSize);
  }

  InputIt tFirst = mainLast;
  InputIt tLast = tFirst;

  // initialize our threads, pass accumulate function, iterator to first item in block, iterator to last item in block, reference to where to store value
  // Start at index 1, because if using a single thread the operation will be done on main thread. index 0 is reserved
  for (int i = 1; i < threadPool.size(); ++i)
  {
    std::advance(tLast, blockSize);
    threadPool[i] = std::thread(accum, tFirst, i == threadPool.size() - 1 ? last : tLast, std::ref(results[i]));
    tFirst = tLast;
  }

  // Main thread accumulate function
  accum(first, mainLast, std::ref(results[0]));

  // Wait for all maintained threads to finish before continuing
  for (int i = 1; i < threadPool.size(); ++i)
    threadPool[i].join();

  // result
  T result;

  // final single thread accum function, this runs in constant time, does not affect single threaded occurences of this function
  // There can be memory overhead / initialization overhead with this implementation tho.
  accum(results.begin(), results.end(), result);

  // Print the final results array just to see what each thread calculated
  Useful::printCont(results);

  // return init + result
  return op(init, result);
}

template <typename InputIt, typename T>
T ParallelAccumulate::accumulate(InputIt first, InputIt last, T init)
{
  // Minimum number of values being operated on to actually justify the overhead of spawning threads
  const int minValues = 100;

  // The maximum number of threads supported by the current hardware. if we spawn more than this then we will not have any performance gain
  int maxThreads = std::thread::hardware_concurrency();

  // The number of elements to be operated on
  int sz = std::distance(first, last);

  // The number of threads to use, including the main thread
  int nThreads = sz < minValues ? 1 : maxThreads;

  // To keep handles to threads that are spawned. main thread at index 0
  std::vector<std::thread> threadPool(nThreads);

  // To keep the results from each thread spawned. main thread at index 0
  std::vector<T> results(nThreads);

  // The blockSize to be operated on by each thread
  int blockSize = sz / nThreads;

  // The single threaded accumulate function to be used by each thread, takes start and end iterator, and reference to where the value should be stored
  auto accum = [](InputIt first, InputIt last, T& i) {
    // If first == last, just return. nothing to operate on
    if (first == last)
      return;

    // get starting value
    T result = *first;

    // iterate until first reaches end, adding value to result;
    while(++first != last)
      result = std::plus<T>()(result, *first);
    
    // set reference to i to the value result;
    i = result;
  };

  InputIt mainLast = last;
  if (blockSize != sz)
  {
    mainLast = first;
    std::advance(mainLast, blockSize);
  }

  InputIt tFirst = mainLast;
  InputIt tLast = tFirst;

  // initialize our threads, pass accumulate function, iterator to first item in block, iterator to last item in block, reference to where to store value
  // Start at index 1, because if using a single thread the operation will be done on main thread. index 0 is reserved
  for (int i = 1; i < threadPool.size(); ++i)
  {
    std::advance(tLast, blockSize);
    threadPool[i] = std::thread(accum, tFirst, i == threadPool.size() - 1 ? last : tLast, std::ref(results[i]));
    tFirst = tLast;
  }

  // Main thread accumulate function
  accum(first, mainLast, std::ref(results[0]));

  // Wait for all maintained threads to finish before continuing
  for (int i = 1; i < threadPool.size(); ++i)
    threadPool[i].join();

  // result
  T result;

  // final single thread accum function, this runs in constant time, does not affect single threaded occurences of this function
  // There can be memory overhead / initialization overhead with this implementation tho.
  accum(results.begin(), results.end(), result);

  // Print the final results array just to see what each thread calculated
  Useful::printCont(results);

  // return init + result
  return std::plus<T>()(init, result);
}

void ParallelAccumulate::run()
{
  std::cout << "Parralel Accumulate" << std::endl;
  std::cout << "std::vector - ";
  std::vector<int> toAccumulate;
  int sz = 1000;
  while (sz--) toAccumulate.push_back(sz);
  Useful::printCont(toAccumulate);


  std::cout << "\nUsing std::accumulate" << std::endl;

  int sum = std::accumulate(toAccumulate.begin(), toAccumulate.end(), 0);
  std::cout << "Sum - " << sum << std::endl;

  int product = std::accumulate(toAccumulate.begin(), toAccumulate.end(), 1, std::multiplies<int>());
  std::cout << "Product - " << product << std::endl;

  std::string concatenated = std::accumulate(std::next(toAccumulate.begin()), toAccumulate.end(), std::to_string(toAccumulate.front()),
    [](const auto& a, const auto& b) {
      return a + "-" + std::to_string(b);
    }
  );
  std::cout << "Concatenated - " << concatenated << std::endl;


  std::cout << "\nUsing ParallelAccumulate::accumulate" << std::endl;

  sum = ParallelAccumulate::accumulate(toAccumulate.begin(), toAccumulate.end(), 0);
  std::cout << "Sum - " << sum << std::endl;

  product = ParallelAccumulate::accumulate(toAccumulate.begin(), toAccumulate.end(), 1, std::multiplies<int>());
  std::cout << "Product - " << product << std::endl;

  // This will not be possible for parallel_accumulate due to type deduction of the lambda expression
  // I can go into detail, but in order to provide a binary operation it must only accept two arguments of the same type
  // concatenated = ParallelAccumulate::accumulate(std::next(toAccumulate.begin()), toAccumulate.end(), std::to_string(toAccumulate.front()),
  //   [](const auto& a, const auto& b) {
  //     return std::move(a) + "-" + std::to_string(b);
  //   }
  // );
  // std::cout << "Concatenated - " << concatenated << std::endl;
}