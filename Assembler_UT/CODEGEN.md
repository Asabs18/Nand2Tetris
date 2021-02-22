# Code Generator:

### Functions:

##### Wrapper Functions:
- Generate code: `GenerateCode(Instruction_t instruct)` - takes a Instruction_t that has a C and A command in it. Finds the Command in the ADT that has a value(not NULL) and calls a function based on which command has a value.

##### Normal Functions:
- Generate C Command: `generateC_Command(cInstruct_t command)` - Takes a C Instruction and creates a starter `uint16_t` value of `1110 0000 0000 0000`. the instruction has three fields(hex values after parser), theses fields are converted to binary format and stored in uint16_t's then the OR operator(|) is used to combine each field with the original uint16_t
- Generate A Command: `generateA_Command(int command)` - Takes the Hex value returned from the parser and directly converts that to its binary format.
- Produce output: `produceOutput(uint16_t(???) binVal)` - takes a int value and uses a helper function to convert to ASCII Binary then outputs produced binary to the output.hack file

##### Helper Functions:
- Convert Hex to Binary: `hexToBin(int hexIn)` - takes a hex value and returns the value converted to binary format (maybe uint16_t???_)
- Convert to ASCII: `intToAscii(int intIn)` - takes a int value and inserts a '0' character in front of the Int to convert the value to binary: [How to Convert Int to Ascii](https://www.tutorialspoint.com/convert-an-int-to-ascii-character-in-c-cplusplus#:~:text=In%20C%20or%20C%2B%2B%20the,'0'%20with%20the%20integer)


### Questions:
- *Can I do these conversions in hex or do they have to be binary i.e (does | work for hex numbers)?*

- *If they have to be binary, what data type is needed for each instance i.e (`1110 0000 0000 000` needs to be uint16_t)?*

- *How does uint16_t work? How is it declared?*