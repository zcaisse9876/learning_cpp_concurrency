#pragma once

#include "AbstractLesson.hpp"
#include <queue>

/**
* Exercise for managing multiple threads concurrently
*/
class SailingShip: public AbstractLesson
{
private:

  // Executes lambda and waits for the returned amount of seconds before executing again
  template <typename T>
  static void executeTasks(T lambda);

  // Simply prints the instructions for how to use the program
  void printInstructions();

  // Handles input from the user and executes actiona accordingly
  void handleInput(std::queue<int>& cc, std::queue<int>& ec, bool& sailing, int command);

public:
  // Runs the sailing ship exercise
  virtual void run() override;
};