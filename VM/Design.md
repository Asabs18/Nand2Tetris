# Virtual Machine Design

## Parser:
### Parser Parent:

#### Constructor:
- Opens input stream and prepares to parse it.

#### hasMoreCommands:
- Checks if there are more inputs in the .vm file stream opened by Constructor

#### advance:
- Makes the Current Command the next command in the stream, only called if hasMoreCommands is True. Initally there is no current Command

#### commandType:
- Returns which class the currentCommand is

#### arg1:
- Returns the first argument of the current command. In the case of C_ARITHMETIC, the command itself is returned, This function is not called if the command is C_RETURN

### Parser C_ARITHMETIC:

### Parser C_PUSH:
#### arg2:
- Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL

### Parser C_POP:
#### arg2:
- Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL

### Parser C_LABEL:

### Parser C_GOTO:

### Parser C_IF:

### Parser C_FUNCTION:
#### arg2:
- Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL

### Parser C_RETURN:

### Parser C_CALL:
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
