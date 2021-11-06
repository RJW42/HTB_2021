#include "gdt.h"

/*Define a GDT index. Use "attribute" (packed)) to prevent the compiler from optimizing alignment*/
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

/*Gdtr pointer*/
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/*Declare GDT and gdtr pointer GP with 3 indexes*/
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/*This is a function in start.asm to load a new segment register*/
extern void gdt_flush();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /*Set descriptor base address*/
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /*Set descriptor boundary*/
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /*Finally, set granularity and access flags*/
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/*Called by main function
 *Set gdtr pointer, set three index barcodes of GDT
 * finally call the gdt_flush in the assembly to tell the location of the new GDT of the processor.
 *And new segment register*/
void gdt_install()
{
    /*Set GDT pointer and boundary*/
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = &gdt;

    /*Null descriptor*/
    gdt_set_gate(0, 0, 0, 0, 0);

    /*The second index is our code snippet
     *Base address is 0, boundary is 4gbyte, granularity is 4kbyte
     *Using a 32 bit operand, is a code segment descriptor
     *Table comparing GDT descriptors in this tutorial
     *Find out what each value means*/
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /*The third index is the data segment
     *Almost the same as the code snippet
     *But access is set to data segment*/
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /*Clear old GDT install new GDT*/
    gdt_flush();
}