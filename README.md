# minishell
The objective of this project is for to create a simple shell that should:
* Show a ***prompt*** when waiting for a new command
* Search and launch the right ***executable*** _(based on the PATH variable or by using
relative or absolute path)_ like in bash
* It must implement the builtins like in bash:
  - ***echo*** with option **’-n’**
  - ***cd*** with only a relative or absolute path
  - ***pwd*** without any options
  - ***export*** without any options
  - ***unset*** without any options
  - ***env*** without any options and any arguments
  - ***exit*** without any options
* ***;*** in the command should separate commands like in bash
* ***’ and "*** should work like in bash except for multiline commands
* ***Redirections < > “>>”*** should work like in bash except for file descriptor aggregation Minishell As beautiful as a shell
* ***Pipes |*** should work like in bash
* Environment variables ($ followed by characters) should work like in bash
* ***$?*** should work like in bash
* ***ctrl-C, ctrl-D and ctrl-\\*** should have the same result as in bash

## Compilling the project
* **make** - compile whole project + lib without unmodified filse
* **make re** - recompile whole project with lib
* **make clean** - clean object files
* **make fclean** - clean object, lib and binary files

## Run project
***./minishell***
