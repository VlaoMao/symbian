.text
.align 4
.data
str:
	.ascii "hello"
dir:
	.ascii "test"
string:
	.ascii "Hello!"

.globl _Z7E32Mainv

    _Z7E32Mainv:
    mov r0,#dir
    mov r1,#dir
    mov r2,#1
    mov r3,#string
    ;bl _ZN11RFileLogger11WriteFormatERK7TDesC16S2_16TFileLoggingMode11TRefByValueIS1_Ez
    
    ;mov pc, lr
    mov r0,#0
    bl _ZN4User4ExitEi
.end
