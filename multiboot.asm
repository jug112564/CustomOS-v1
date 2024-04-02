[BITS 32]

section .text
    ALIGN 4
    DD 0x1BADB002
    DD 0x00000000
    DD -(0x1BADB002 + 0x00000000)
    
global start
extern kmain

start:
    CLI
    MOV esp, stack_space

    ; push information contained by GRUB onto the stack
    push ebx                       ; multiboot structure pointer
    push eax                       ; magic number
    CALL kmain
    HLT
HaltKernel:
    CLI
    HLT
    JMP HaltKernel

section .bss
RESB 8192
stack_space: