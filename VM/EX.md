# VM to ASM translations:

## push:
```c
@SP
A=M
M=D
@SP
M=M+1
```

## Pop:
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

## add:
@SP
AM=M-1
D=M
A=A-1
M=D+M

## Subtract:
@SP
AM=M-1
D=M
A=A-1
M=M-D

## Negate:
@SP
A=M-1
M=-M

## And:
@SP
AM=M-1
D=M
A=A-1
M=D&M

## Or:
@SP
AM=M-1
D=M
A=A-1
M=D|M

## Not:
@SP
A=M-1
M=!M

## Return:
???
