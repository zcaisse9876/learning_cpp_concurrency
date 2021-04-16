#include <functional>
#include "SailingShip.hpp"
#include "ThreadGaurd.hpp"

/**
* A simple Program to represent a ship that has a captain and two crews, engine and cleaning
* Main thread is the captain
* Engine and Cleaning crews are represented by different threads
*
* Requirements:
*
* Engine and Cleaning crew are represented by seperate threads
* Must maintain two queues that represent job queues for each crew (thread)
* The captain listens for a command from the user once every second
* The captain adds the instruction to a job queue, 1 is for cleaning, 2 is for engine full speed, 3 is for engine stop, 100 is to stop the ship and end program
* the cleaning queue should check the cleaning task queue, while the engine queue should check the engine task queue
* if there are no tasks, the respective crew waits 2 seconds to check again
* if there are tasks, the respective crew executes the task and waits 1 second to check again
* all crew and captain check a flag to determine if they are done for the day and the program ends.
* The crews run asynchronously from the captain, the captain does not need to wait for them to finish a task before issuing another task to their task queue.
*/

// Simple function to execute a lambda that returns the number of seconds to wait before executing the lambda again
template <typename T>
void SailingShip::executeTasks(T lambda)
{
  // This represents how long the crew should wait before executing the next task
  int seconds = 1;
  while (seconds > 0)
  {
    // Take a break
    std::this_thread::sleep_for(std::chrono::milliseconds(seconds * 1000));
    // execute next task
    seconds = lambda();
  }
}

// Prints the instruction
void SailingShip::printInstructions()
{
  std::cout << "The ship has sailed!\n"
            << "type 1 to clean.\n"
            << "type 2 to go full speed ahead.\n"
            << "type 3 to stop.\n"
            << "type 100 to stop the program.\n";
}

void SailingShip::handleInput(std::queue<int> &cc, std::queue<int> &ec, bool& sailing, int command)
{
  // If command is 1, push job for cleaning crew
  if (command == 1)
    cc.push(command);
  // if command is 2 or 3, insert job for engine crew
  else if (command == 2 || command == 3)
    ec.push(command);
  // if command is 100, set sailing flag to false
  else if (command == 100)
    sailing = false;
  // otherwise print invalid command and do nothing
  else
    std::cout << "Captain received an invalid command" << std::endl;
}

void SailingShip::run()
{
  // Ship would continue sailing when this is not zero
  bool sailing = true;
  // Tasks queues for each crew
  std::queue<int> engineTasks, cleaningTasks;

  // This is code is clearly ugly :/ This is is an expirement of whether i "could" and not whether i "should"
  // template functions that accept lambdas to the constructor of std::thread. kinda cool but the implementation looks nasty
  std::thread cleaningCrew(SailingShip::executeTasks<std::function<int()>>,
    [&cleaningTasks, &sailing]() -> int {
      if (!sailing)
        return 0;

      if (!cleaningTasks.size())
        return 2;

      std::cout << "Cleaning crew (tid -- " << std::this_thread::get_id() << ") is cleaning the ship!" << std::endl;

      cleaningTasks.pop();
      return 1;
    }
  );

  std::thread engineCrew(SailingShip::executeTasks<std::function<int()>>,
    [&engineTasks, &sailing]() -> int {
      if (!sailing)
        return 0;
      
      if (!engineTasks.size())
        return 2;

      if (engineTasks.front() == 2)
        std::cout << "Engine crew (tid -- " << std::this_thread::get_id() << ") going full speed ahead!" << std::endl;
      else
        std::cout << "Engine crew (tid -- " << std::this_thread::get_id() << ") stopping the ship!" << std::endl;

      engineTasks.pop();
      return 1;
    }
  );

  // Use threadguard to join threads via RAII
  ThreadGaurd ccGaurd(cleaningCrew), ecGaurd(engineCrew); 

  // send instructions to user on console
  this->printInstructions();

  // start sailing the ship
  while (sailing)
  {
    // captain can only take a command every 1 second
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Captain (tid -- " << std::this_thread::get_id() << ") is ready for a command!" << std::endl;
    
    // read command from user
    int command;
    std::cin >> command;

    // handle the input
    this->handleInput(cleaningTasks, engineTasks, sailing, command);
  }

  std::cout << "Ship crews are going home for the day!" << std::endl;
}