# get_next_line

![42 Logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTXfAZMOWHDQ3DKE63A9jWhIqQaKcKqUIXvzg&s)

`get_next_line` is a C programming project where you develop a function that reads a line from a file descriptor. The project focuses on handling file input/output and memory management in C. The main goal is to create an efficient function to read a line from a file, one at a time, until the end of the file is reached.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)

## Description

The goal of the `get_next_line` project is to create a function that reads a single line from a file descriptor each time it is called. This function should handle any size of input and continue reading from the file until the end of the file is reached, or an error occurs. The function will return the line that was read each time it is called, allowing for efficient line-by-line file reading.

This project helps to practice file handling, memory management, and string manipulation in C.

## Features

- Reads one line at a time from a file descriptor.
- Handles files of any size and is memory efficient.
- Works with both text files and standard input/output.
- Compatible with multiple file descriptors.

## Installation

To compile and use `get_next_line`, follow these steps:

1. Clone the repository to your local machine:

    ```bash
   git clone https://github.com/yourusername/get_next_line.git
   ```
2. Navigate into the project directory:

   ```bash
   cd get_next_line
   ```

## Usage

To use `get_next_line`, include the `get_next_line.h` header in your C program and link it with the compiled object files. Below is a small example of how to read lines from a single file using your implementation of `get_next_line`:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line;
    int fd = open("tests/file1.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);  // Don't forget to free the memory after use!
    }

    close(fd);
    return (0);
}
```

## How It Works
1. get_next_line function reads from the file descriptor until it encounters a newline character or reaches the end of the file.
2. It dynamically allocates memory for the line buffer, handling both short and long lines efficiently.
3. The function handles multiple calls, allowing the program to read the next line from the file each time.
4. The line buffer is returned, and it is the user's responsibility to free the memory after each line is processed.
