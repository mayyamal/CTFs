begin_file:

ehdr:	.byte 0x7f, "ELF", 1, 1, 1, 0
	.byte 0, 0, 0, 0, 0, 0, 0, 0
	.word 2
	.word 3
	.long 1
	.long _start
	.long phdr - begin_file
	.long 0
	.long 0
	.word      ehdrsize       
        .word      phdrsize
        .word      1     
        .word      0     
        .word      0
        .word      0
end_ehdr:
	.set ehdrsize, end_ehdr - ehdr

phdr:             
               .long      1
               .long      0
               .long      0x08048000
               .long      0x08048000
               .long      filesize   
               .long      filesize   
               .long      5          
               .long      0x1000     
end_phdr: 
	.set phdrsize, end_phdr - phdr


.data
     matrNum: .ascii "01532177"
.text
    .globl _start
    _start:

	mov $4, %al
	mov $1, %bl
        mov $matrNum, %ecx
        mov $8, %dl
        int $0x80

        mov $1, %al
        mov $0, %bl
        int $0x80

end_file:
	.set filesize, end_file - begin_file 

        
