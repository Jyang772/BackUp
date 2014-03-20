[BITS 32]

global read_cpuid, switch_kernel_64

SECTION .text

read_cpuid:
	push	ebp
	mov		ebp, esp
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi

	mov		eax, dword[ebp + 8]
	cpuid

	mov		esi, dword[ebp + 12]
	mov		dword[esi], eax

	mov		esi, dword[ebp + 16]
	mov		dword[esi], ebx

	mov		esi, dword[ebp + 20]
	mov		dword[esi], ecx

	mov		esi, dword[ebp + 24]
	mov		dword[esi], edx

	pop		esi
	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
	pop		ebp
	ret

switch_kernel_64:
	mov	eax, cr4
	or	eax, 0x20		; set PAE bit of CR4 to 1
	mov	cr4, eax

	mov	eax, 0x100000	; set the value of CR3 register to the base address of PML4 table
	mov	cr3, eax
		
	mov	ecx, 0xc0000080	; read MSR register
	rdmsr				

	or	eax, 0x0100		; write MSR register
	wrmsr

	mov	eax, cr0
	or	eax, 0xe0000000
	xor	eax, 0x60000000
	mov	cr0, eax

	jmp	0x08:0x200000

	jmp $
