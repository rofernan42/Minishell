# MiniShell
## Summary
The objective of this project is to create our own shell.
This is a 2 persons group project.
## Instructions
The minishell should:
* show a prompt when waiting for a new command
* search and launch the right executable (based on the PATH variable or using a relative or absolute path)
* the following builtins have to be implemented:
** ```echo``` with option ```-n```
** ```cd```
** ```pwd``` without any option
** ```export``` without any option
** ```unset``` without any option
** ```env``` without any option
** ```exit``` without any option
* ```;``` in the command should separate commands like in bash
* ```'``` and ```"``` should work like in bash (but multiligne commands are not handled)
* redirections ```< > >>``` should work like in bash except for fil descriptor aggregation
* pipes ```|``` should work like in bash
* environment variables ```$VAR``` should work like in bash
* return value ```$?``` should work like in bash
* ctrl-C, ctrl-D, ctrl-\ should have the same result as in bash
## Compilation
Use the ```make``` command to compile using the Makefile.
## Execution
```./minishell```
## Usage
Type commands like in a real shell terminal!
