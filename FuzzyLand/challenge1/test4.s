.data
     matrNum: .ascii "01532177"
.text
    .globl _start
    _start:

        mov $4, %al	#write syscall
        mov $1, %bl
        mov $matrNum, %ecx
        mov $8, %dl
        int $0x80

	      
 	mov $1, %al     #exit syscall
        mov $0, %bl	#return 0
        int $0x80

