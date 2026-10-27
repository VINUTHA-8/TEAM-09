# TEAM-09: Smart Emergency Response System

A menu-driven C program for registering and managing emergency requests. It uses
a queue for pending emergencies and a stack for completed-emergency history.

## About

SERS is an educational C project that models a console-based emergency-response
workflow using priority levels, an array-backed queue, and a stack to manage
pending and completed requests. It is a learning/demo program, not a live
emergency service.

## Features

- Register ambulance, fire, and police emergencies
- View pending emergencies and dispatch the highest-priority request
- View completed history, search by ID, and undo the latest completion
- See dashboard statistics
- Save completed history to `history.txt`

## Requirements

- GCC or another C compiler

## Build and run

The source file in this repository is named `CS project.c`.

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic "CS project.c" -o sers
./sers
```

On Windows with MinGW GCC:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic "CS project.c" -o sers.exe
sers.exe
```

Choose **Save History To File** in the program menu to create `history.txt`
in the current directory.
