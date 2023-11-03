	.arch armv8-a
	.file	"assignment5.c"
	.text
	.align	2
	.global	f1
	.type	f1, %function
f1:
.LFB1:
	.cfi_startproc
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, 8]
	str	wzr, [sp, 20]
	add	x0, sp, 20
	str	x0, [sp, 24]
	ldr	w0, [sp, 20]
	cmp	w0, 0
	bne	.L2
	mov	w0, 5
	str	w0, [sp, 16]
	add	x0, sp, 16
	str	x0, [sp, 24]
.L2:
	ldr	x0, [sp, 8]
	add	sp, sp, 32
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE1:
	.size	f1, .-f1
	.section	.rodata
	.align	3
.LC0:
	.string	"Value %d is at %p\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB2:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	x19, [sp, 16]
	.cfi_offset 19, -32
	mov	w0, 5
	str	w0, [sp, 44]
	ldr	w19, [sp, 44]
	add	x0, sp, 44
	bl	f1
	mov	x2, x0
	mov	w1, w19
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (FreeBSD Ports Collection) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
