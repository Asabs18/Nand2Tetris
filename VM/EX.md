# VM to ASM translations:

## push x y:
``` c
@y
D = A
@SP
A=M
M=D
@SP
M=M+1
```

## add:
``` c
...
```
