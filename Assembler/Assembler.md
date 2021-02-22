# Assembler

#### Details:

##### first:
-Add all preexisting symbols to the symbol table(there are 23)

##### First Pass:
- Reads through each line of Assembly language code and take all the labels (Surrounded in "()" ) and adds them to the symbol table along with the address if the next machine language command
- This requires maintaining this running address 

###### Restart reading


##### Second Pass:
- Get the assembly language command and parse it 
- If you encounter a var then check if it exists on the symbol table, if so translate this var to its binary address, if not add it to the symbol table(position does not matter)
- if curr instruction is an A-instruction then add the vars name and the next free address to the symbol table
- You will need to parse each C-instruction. This can be broken down to the parts:
    - Advance(reads the next command and makes it the curr command, handles whitespace if needed, Should only be called if hasMoreCommands() is true, starts with no curr command)
    - CommandType(Returns type of curr command A, C or L commands)
    - Symbol (Returns the symbol or decimal of the curr command, should be called when command type is equal to A or L)
    - Dest (Returns the dest mnemonic in the curr C-command(8 possibilities), Only called during C-Commands)
    - Comp (Returns the comp mnemonic for C-commands(28  possibilities), Only used for C Commands)
    - Jump (Returns the jump mnemonic for C-commands(8 possibilities), Only used for C-commands)
- loop through this loop until all vars are added to the symbol table and translated to their binary addresses
- Output the resulting machine language command



##### OutLine:

 - Assembler():
    - Over arching function that runs 2 passes on a piece of Assembly code and translates it into hack binary
    - The first pass adds all of the labels to the symbol table
    - the second pass adds vars to the symbol table and parses c-instructions to get values for the vars. This pass goes through each line of coded ignoring whitespace and labels

 - SymbolTable():
    - This function creates a empty symbol table
    - It adds all predefined hack values to the symbol table, there are 23
    - The symbol table does not need to be sorted for this program. It only needs to hold a name(key) and a value(the key is attached to)
 - Advance():
    - Read the next command and makes it the curr command
    - Handles whitespace if needed(treat labels as whitespace in the second pass)
    - Should only be called if has more commands = True
    - At the start of the program this function will have no curr command
 - CommandType():
    - Returns the type of the curr command
    - This can be an A-Command a C-Command or L-command(label)
 - Symbol():
    - Returns the Symbol or decimal of curr command
    - Should be only called when command type is A or L
 - Dest():
    - Returns the dest mnemonic in the curr C-command(8 possibilities)
    - Only Used for C-Commands
 - Comp():
    -  Returns the comp mnemonic for C-commands(28  possibilities)
    -  Only used for C-commands
 - Jump():
    - Returns the jump mnemonic for C-commands(8 possibilities)
    - Only Used For C-Commands
 - areThereMoreCommands():
    - Checks if the file is over or if more commands exist
    - If more commands exist return true
    - otherwise return false


##### White Space:

 - White space is extremely straightforward.
 - All but one file handles whitespace in its own line all in the very beginning of the file before any commands
 - One file requires you to handle comments on the same line as a command exclusively after the command.
 - Whitespace is only represented by a "//"
 - White space can be handled by checking for the "//" and if found ignoring the rest of the line


##### SymbolTable Functions:
 - create(int startSize)
 - destroy(symbolTable_p table)
 - add(symbolTable_p table, symbol_p symbol)
 - isInTable(symbolTable_p table, symbol_p symbol)
 - isStringValidSymbol(char* string)
 - getSymbol(symbolTable_p table, char* key)
 - printTable(symbolTable_p table)

#### References:
-  [Symbol Table Details](https://www.tutorialspoint.com/compiler_design/compiler_design_symbol_table.htm)
-  [Hashmaps](http://www.kaushikbaruah.com/posts/data-structure-in-c-hashmap/)
-  [Dynamic Array](https://stackoverflow.com/questions/3536153/c-dynamically-growing-array)
-  [Dynamic Array pt.2](https://troydhanson.github.io/uthash/utarray.html)
-  [Dynamic Array pt. 3](https://medium.com/@imjacobclark/working-with-dynamic-arrays-in-c-c7d40a3cea01)