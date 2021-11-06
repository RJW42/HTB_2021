global start                    ; the entry symbol for ELF

;MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
;FLAGS        equ 0x0            ; multiboot flags
;CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
;                                ; (magic number + checksum + flags should equal 0)

;align 4                         ; the code must be 4 byte aligned
;    dd MAGIC_NUMBER             ; write the magic number to the machine code,
;    dd FLAGS                    ; the flags,
;    dd CHECKSUM                 ; and the checksum

section .text:                  ; start of the text (code) section
start:                          ; the loader label (defined as entry point in linker script)
	[extern main]
	call main

.loop:
    jmp .loop                   ; loop forever
