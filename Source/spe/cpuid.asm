; i386/cpuid.asm
; Copyrights (c) 2005 Mohamed Abdelsalam Aslan <maslan@users.berlios.de>
;
; This library is free software; you can redistribute it and/or
; modify it under the terms of the GNU Lesser General Public
; License as published by the Free Software Foundation; either
; version 2.1 of the License, or (at your option) any later version.
;
; This library is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; Lesser General Public License for more details.
;
; You should have received a copy of the GNU Lesser General Public
; License along with this library; if not, write to the Free Software
; Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

;GenuineIntel		Intel processor
;UMC UMC UMC		UMC processor
;AuthenticAMD		AMD processor
;CyrixInstead		Cyrix processor
;NexGenDriven		NexGen processor
;CentaurHauls		Centaur processor
;RiseRiseRise		Rise Technology processor
;SiS SiS SiS		SiS processor
;GenuineTMx86	Transmeta processor
;Geode by NSC		National Semiconductor processor

bits 32

global osdk_get_cpuid

vendor	dd	0h
		dd	0h
		dd	0h
std_eax	dd	0h
std_ebx	dd	0h
std_ecx	dd	0h
std_edx	dd	0h
ser_ecx	dd	0h
ser_edx	dd	0h

check_cpuid:
	pushf
	pop	eax
	mov	ebx, eax
	or	eax, 1000000000000000000000b
	push eax
	popf
	pushf
	pop	eax
	cmp	eax, ebx
	je	cpuid_not_supported
cpuid_supported:
	mov	eax, 01h
	ret
cpuid_not_supported:
	xor	eax, eax
	ret

check_rdtsc:
	mov	eax, [std_edx]
	and	eax, 10000b
	jz	rdtsc_not_supported
rdtsc_supported:
	mov	eax, 01h
	ret
rdtsc_not_supported:
	xor	eax, eax
	ret
	

init_cpuid:
	push eax
	push ebx
	push ecx
	push edx
	push esi
	call	check_cpuid
	or	eax, eax
	jz	no_cpuid
	call	check_rdtsc
	or	eax, eax
	jz	no_rdtsc
	mov	esi, vendor
	xor	eax, eax
	cpuid
	mov	[esi], dword ebx
	mov	[esi+4], dword edx
	mov	[esi+8], dword ecx
	mov	eax, 01h
	cpuid
	mov	[std_eax], dword eax
	mov	[std_ebx], dword ebx
	mov	[std_ecx], dword ecx
	mov	[std_edx], dword edx
	mov	eax, 03h
	cpuid
	mov	[ser_ecx], dword ecx
	mov	[ser_edx], dword edx
init_cpuid_end:
	pop esi	
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret
no_cpuid:
	jmp	init_cpuid_end
no_rdtsc:
	jmp	init_cpuid_end


get_cpu_speed:
	ret

osdk_get_cpuid:
	push ebp
	mov	ebp, esp
	pushf
	push ecx
	push esi
	push edi
	cld
	mov esi, vendor
	mov edi, dword [ebp+8]
	mov	ecx, 03h
	rep	movsd
	mov [edi], byte 0h
	mov	ecx, [std_eax]
	mov	[edi+1], dword ecx
	mov	ecx, [std_ebx]
	mov	[edi+5], dword ecx
	mov	ecx, [std_ecx]
	mov	[edi+9], dword ecx
	mov	ecx, [std_edx]
	mov	[edi+13], dword ecx
	mov	ecx, [ser_ecx]
	mov	[edi+25], dword ecx
	mov	ecx, [ser_edx]
	mov	[edi+29], dword ecx
	pop	edi
	pop	esi
	pop	ecx
	popf
	mov	esp, ebp
	pop	ebp
	ret


