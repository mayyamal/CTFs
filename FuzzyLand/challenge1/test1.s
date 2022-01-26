 BITS 32
  
                org     0x00200000
  
  elfhdr:                                                 ; Elf32_Ehdr
                db      0x7F, "ELF"                       ;   e_ident
				db		1, 1, 1, 0  
        	
 _end:  mov al, 0x1
		mov bl, 0x0
		int 0x80
				db      0, 0	
                dw      2                               ;   e_type
                dw      3                               ;   e_machine
                dd      1                               ;   e_version
                dd      _start                          ;   e_entry
                dd      proghdr - $$                    ;   e_phoff
     proghdr:   dd      1                               ;   e_shoff        ;   p_type
                dd      0                               ;   e_flags        ;   p_offset 
                dd      $$                              ;   e_ehsize       ;   p_vaddr
                                                        ;   e_phentsize
   			    dw      1                               ;   e_phnum        ;   p_paddr    
              	dw      0			                    ;   e_shentsize    
                		                                
                                                            
													
                              
                dd      filesize                        ;   e_shnum        ;   p_filesz
														;   e_shstrndx
                dd      filesize                        ;   p_memsz
                dd      5                               ;   p_flags
                dd      0x1000                          ;   p_align
  
    
  _start:
		
		mov al, 0x4
		mov bl, 0x1
		mov ecx, matrNum
		mov dl, 0x8
		int 0x80
		
		jmp _end  
    	

  matrNum:  db "01532177"
  
  filesize      equ     $ - $$
