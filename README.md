# Philosophers

This is the implementation of the "Philosophers" project from 42 School's curriculum.

This project is an introduction to concurrent programming and thread synchronization using mutexes to resolve the classic Dining Philosophers problem.

## Table of Contents
- [Introduction](#introduction)
- [Philosophers Problem](#philosophers-problem)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
- [Project Structure](#project-structure)
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project tackles the Dining Philosophers problem using threads and mutexes in C. It is a required part of the 42 School curriculum and focuses on understanding thread management, synchronization, and avoiding potential deadlock scenarios.

## Philosophers Problem

The Dining Philosophers problem is a classical problem involving five philosophers who alternate between thinking and eating. Around a table, 
- **Philosophers think** while not hungry.
- When a philosopher becomes hungry, they pick up their adjacent forks (if available) to eat. 
- A philosopher can only eat if they have both the left and right forks.
- After eating, philosophers think again.

This project implements rules to ensure there are no deadlocks and starvation while using synchronization mechanisms.

## Features

- Philosophers and their behaviors are represented as threads.
- Mutexes are used to synchronize access to shared resources.
- Avoidance of deadlock and resource contention via proper synchronization.

## Getting Started

### Prerequisites
- GCC or another C compiler.
- `make` tool for building.
- Tested on Unix-like operating systems (Linux or macOS).

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/AdnilsonPinheiro/philosophers.git
   cd philosophers
   ```

2. Build the project:
   ```bash
   make
   ```

### Usage
Run the executable with the following parameters:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
Example:
```bash
./philo 5 800 200 200 7
```

#### Arguments:
- **number_of_philosophers**: The number of philosophers and forks.
- **time_to_die**: Time (in ms) before a philosopher dies since their last meal.
- **time_to_eat**: Time (in ms) required for a philosopher to eat a meal.
- **time_to_sleep**: Time (in ms) a philosopher spends sleeping after eating.
- **number_of_times_each_philosopher_must_eat** *(optional)*: The number of meals for each philosopher before simulation ends.

## Project Structure

```
philosophers/
├── src/            # Source code files
├── include/        # Header files
├── Makefile        # Build system
└── README.md       # Project documentation (this file)
```

## Resources

Here are some resources to understand the Philosophers problem and synchronization:
- [Dining Philosophers Problem on Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- 42 School Project Guidelines & Subject PDF
- Recommended reading: "Operating System Concepts" by Silberschatz, Galvin, and Gagne.

## Contributing

Contributions are welcome! If you'd like to contribute, make a pull request or open an issue in the repository.

## License

This project is licensed under the MIT License. See [LICENSE](./LICENSE) for details.