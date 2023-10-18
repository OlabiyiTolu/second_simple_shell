# simple_shell

# Simple Shell - 0x16 Project

This is the repository for the Simple Shell project, which is part of ALX School's curriculum. This project is a UNIX command-line interpreter designed to replicate basic shell functionality.

## Project Overview

The project involves creating a simple shell, providing a command-line interface to interact with the operating system. This shell is designed to handle basic commands and features such as executing commands, handling arguments, managing the environment, built-in commands, logical operators, variables, comments, and more.

The project aims to reinforce various programming and system-level concepts, including system calls, processes, environment variables, and working with the UNIX shell.

## Team Members

- Khalil Zhari
- Tolu Olabiyi

## Project Timeline

- Start Date: October 4, 2023
- End Date: October 19, 2023
- Checker Release: October 18, 2023

## Project Concepts

In this project, you will explore and learn about the following key concepts:

- Understanding and building your own shell
- The basics of programming and C
- Problem-solving and engineering mindset
- Collaborative work in a team

## Important Message

Before you begin the project, it's essential to understand the importance of integrity in your work. At ALX School, the emphasis is on learning and understanding the process, not copying solutions or code from others. Here are some important reminders:

- **Do not copy code**: Do not look at or copy solutions from other students or online sources.
- **Write code from understanding**: Ensure you write code from understanding, not memory.
- **Avoid sharing resources**: Sharing tutorials or code solutions with friends can be detrimental to your learning.

## Learning Objectives

By the end of this project, you should be able to:

- Understand the basics of programming and C.
- Explain how a shell works.
- Manipulate the environment of the current process.
- Differentiate between functions and system calls.
- Create processes in a UNIX environment.
- Use the PATH to find programs.
- Execute other programs using the execve system call.
- Suspend process execution until child processes terminate.
- Comprehend EOF (End-of-File).

## Requirements

- The project is meant to be compiled on Ubuntu 20.04 LTS using the GCC compiler with specific options.
- Your code should follow the Betty coding style.
- Your shell should be free of memory leaks.
- The repository should contain a README.md file describing the project.
- An AUTHORS file at the root of the repository is required, listing all contributors.

## Allowed Functions and System Calls

The project specifies the use of several allowed functions and system calls, including but not limited to: `access`, `chdir`, `close`, `execve`, `exit`, `fflush`, `fork`, `free`, `getcwd`, `getline`, `getpid`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `read`, `readdir`, `signal`, and more.

## Compilation

The shell will be compiled with the following command:

```shell
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing

The shell is expected to work in both interactive and non-interactive modes. Examples of how to run the shell interactively and non-interactively are provided in the tasks.

## Available Tasks

This project consists of various tasks, each building upon the previous one. It includes tasks such as:

- Creating a shell that can execute basic commands and display prompts.
- Handling command lines with arguments.
- Implementing the PATH for command execution.
- Adding built-in commands such as `exit` and `env`.
- Writing a custom `getline` function.
- Handling the logical operators `&&` and `||`.
- Implementing variables and comments.
- Allowing input from a file.

The tasks are designed to deepen your understanding of shell functionality and reinforce your programming skills.

## License

This project is licensed under ALX School. All rights are reserved. No content from this project should be published or shared.

*Disclaimer: This is a simplified README.md for the Simple Shell project. In a real project, you should provide detailed information about the functionality and usage of the shell, as well as comprehensive instructions on how to run and test the program.*
