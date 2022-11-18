	.file	"7.c"
	.text
	.p2align 4
	.globl	hamming_weight
	.type	hamming_weight, @function
hamming_weight:
.LFB39:
	.cfi_startproc
	endbr64
	movl	%edi, %edx
	shrl	%edi
	andl	$1431655765, %edx
	andl	$1431655765, %edi
	leal	(%rdx,%rdi), %eax
	movl	%eax, %edx
	shrl	$2, %eax
	andl	$858993459, %edx
	andl	$858993459, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$4, %eax
	andl	$252645135, %edx
	andl	$252645135, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$8, %eax
	andl	$16711935, %edx
	andl	$16711935, %eax
	addl	%edx, %eax
	movzwl	%ax, %edx
	shrl	$16, %eax
	addl	%edx, %eax
	ret
	.cfi_endproc
.LFE39:
	.size	hamming_weight, .-hamming_weight
	.p2align 4
	.globl	hamming_weight_bis
	.type	hamming_weight_bis, @function
hamming_weight_bis:
.LFB40:
	.cfi_startproc
	endbr64
	xorl	%eax, %eax
	testl	%edi, %edi
	je	.L6
	.p2align 4,,10
	.p2align 3
.L5:
	leal	-1(%rdi), %edx
	addl	$1, %eax
	andl	%edx, %edi
	jne	.L5
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	ret
	.cfi_endproc
.LFE40:
	.size	hamming_weight_bis, .-hamming_weight_bis
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	testl	%eax, %eax
	je	.L11
	movl	%eax, %edx
	xorl	%r8d, %r8d
	.p2align 4,,10
	.p2align 3
.L10:
	leal	-1(%rdx), %eax
	addl	$1, %r8d
	andl	%eax, %edx
	jne	.L10
.L9:
	movl	%r8d, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore_state
	xorl	%r8d, %r8d
	jmp	.L9
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
