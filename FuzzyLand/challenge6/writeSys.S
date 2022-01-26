BITS 32

mov $4, %al	
mov $1, %bl
push dword 0x37313032
push dword 0x44534153
mov %esp, %ecx
mov $8, %dl
int $0x80

	      
 	   