# Virtual Machine Design

## Parser:
### Parser Parent:

#### Constructor:
- Opens input stream and prepares to parse it.

#### hasMoreCommands:
- Checks if there are more inputs in the .vm file stream opened by Constructor

#### commandType:
- Returns a class that is the currentCommands correct type. (Has factory functions for each command type) Creates The correct object

### Parser C_ARITHMETIC:
#### arg1:
- Returns itself
### Parser C_PUSH:
#### arg1:
- Returns The first argument of the command
#### arg2:
- Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL

### Parser C_POP:
#### arg1:
- Returns The first argument of the command
#### arg2:
- Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL

### Parser C_LABEL:
#### arg1:
- Returns The first argument of the command

### Parser C_GOTO:
#### arg1:
- Returns The first argument of the command

### Parser C_IF:
#### arg1:
- Returns The first argument of the command

### Parser C_FUNCTION:
#### arg1:
- Returns The first argument of the command
#### arg2:
- Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL

### Parser C_RETURN:
#### arg1:
- Returns The first argument of the command

### Parser C_CALL:
#### arg1:
- Returns The first argument of the command
#### arg2:
- Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL


## Code Writter:
### Constructor:
- Opens output file and gets ready to write to it

### writeArithmetic:
- Writes Assembly code for an arithmatic command to the output file

### writePushPop:
- Writes the assembly code that implements a given command to the output file

### Close:
- Closes the output file

## Description of parser:
- The parent parser will have multiple factory functions that pass a command around and if one of these functions relize that the command passed to them is valid, create a certain object for the needed parser. 
