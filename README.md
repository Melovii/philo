# Dining Philosophers

A multithreaded C implementation of the classic Dining Philosophers problem using POSIX threads (pthread) and mutexes.

## Overview

Simulates philosophers sitting around a table, alternating between thinking, eating, and sleeping while sharing forks. Uses threads for concurrency and mutexes to prevent race conditions and deadlocks.

## Compilation

```bash
make
```

Compiles with pthread library (`-pthread` flag).

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters
- **number_of_philosophers**: Number of philosophers and forks
- **time_to_die**: Max time (ms) without eating before death
- **time_to_eat**: Time (ms) spent eating  
- **time_to_sleep**: Time (ms) spent sleeping
- **number_of_times_each_philosopher_must_eat** (optional): Stop when all have eaten this many times

### Examples

```bash
./philo 5 800 200 200        # 5 philosophers, basic simulation
./philo 4 410 200 200 10     # 4 philosophers, each must eat 10 times
```

## Implementation

- **Each philosopher**: Separate thread with eat/sleep/think cycle
- **Forks**: Mutexes preventing simultaneous access
- **Monitor thread**: Detects death and simulation completion
- **Synchronization**: Print, death, and meal mutexes prevent race conditions
- **Deadlock prevention**: Asymmetric fork acquisition (even/odd philosopher ordering)

## Output

State changes logged with timestamps:
```
[timestamp_ms] [philosopher_id] [state]
```

Example:
```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
```
