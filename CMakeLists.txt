cmake_minimum_required(VERSION 3.0.0)
project(LEARNING_CPP_CONCURRENCY VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

include_directories(include)
add_executable(
  LEARNING_CPP_CONCURRENCY
  main.cpp
  lessons/ByReference.cpp
  lessons/TransferOwnership.cpp
  lessons/UsefulFunctions.cpp
  lessons/ThreadLocalStorage.cpp
  exercises/SailingShip.cpp
  exercises/ParallelAccumulate.cpp
  shared/ThreadGaurd.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
