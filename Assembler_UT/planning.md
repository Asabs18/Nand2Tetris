# Parser Design

### Requirements:
- The parse function will take a command and figure out its type then parse it and return its int value
- the parse a command will be called from the parse function if currCommand is an A command and it will return a int representing the command
- the parse L command will be called from the parse function if currCommand is an L command and it will return a int representing the command
- the parse c command will be called from the parse function if currCommand is an C command and it will return a int representing the command
- the comp, dest and jump functions will each parse a certain part of the c-command if needed

### Current state of parser:

- function parse A command takes tokenized A command and gets the command without the @ then its checks if the command is valid and adds it to the symbol table ------ there is incorrect logic when checking and adding the command
- The parse L command gets the command without the parenthesis on each side, still needs to be converted to an int value
- the parse C command takes a command and passes it into helper function comp dest and jump as needed, then based on the output of these helper functions the c command updates the instructon variable with the new values, still need to convert these values to usable int

### TODO:
- Fix A-command by not adding to the symbol table in the function but instead returning the correct int value
- Fix L-command by returning the correct int value based on instruction
- Fix C-command by converting the instruction var to a valid int output, may be fine as it is