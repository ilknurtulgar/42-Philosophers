42 Philosophers
This project is a simulation of the Dining Philosophers problem, designed to test synchronization and concurrency using threads and mutexes.

Objective
Implement a solution to the Dining Philosophers problem, ensuring proper handling of deadlocks, race conditions, and resource sharing through thread synchronization.

Requirements
C compiler (e.g., GCC)
pthread library
Makefile for building the project
Installation
Clone the repository:

bash
  git clone https://github.com/your-username/42-philosophers.git
  cd 42-philosophers

Build the project:
bash
  make

Run the simulation:
bash
  ./philosophers [num_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
