; this will create our new segment register
; set CS by long jump
global gdt_flush; allows C source programs to link the function Extern gpdeclares GPAs an external variable
[extern gp]
gdt_flush:
    lgdt [gp]; use_gp to load GDT
    Mov ax, 0x10; 0x10 is the offset address of our data segment in GDT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    JMP 0x08: flush2; 0x08 is the offset address of the code segment, long jump
flush2:
    Ret; return to C program