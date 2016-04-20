bits	32
section		.text
	align	4
	dd	0X1BADB002
	dd	0x00
	dd	- (0x1BADB002+0X00)
	
global start		;entry point of the kernel
extern kmain		;this function is in the C code
start:
	cli		;clear interrupts, provided by BIOS
	call kmain	;send processor to continue execution from kmain()
	hlt		;halt the CPU(no more execution from this point)

