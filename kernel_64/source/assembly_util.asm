[BITS 64]

SECTION .text

global keyboard_read, keyboard_write

keyboard_read:
	push	rdx

	mov	rdx, rdi
	mov	rax, 0

	in	al, dx

	pop	rdx
	ret

keyboard_write:
	push	rdx
	push	rax

	mov	rdx, rdi
	mov	rax, rsi

	out	dx, al

	pop	rax
	pop	rdx
	ret
