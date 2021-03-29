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
```c
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
```

## add:
```c
@SP
AM=M-1
D=M
A=A-1
M=D+M
```

## Subtract:
```c
@SP
AM=M-1
D=M
A=A-1
M=M-D
```

## Negate:
```c
@SP
A=M-1
M=-M
```

## And:
```c
@SP
AM=M-1
D=M
A=A-1
M=D&M
```

## Or:
```c
@SP
AM=M-1
D=M
A=A-1
M=D|M
```

## Not:
```c
@SP
A=M-1
M=!M
```

## Return:
```c
???
```
