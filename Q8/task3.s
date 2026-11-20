	.file	"task3_constants.c"
	.text
	.globl	compute_bill
	.type	compute_bill, @function
compute_bill:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	$5000, -8(%rbp)
	cmpl	$200, -20(%rbp)
	jle	.L2
	movl	-20(%rbp), %eax
	subl	$200, %eax
	cltq
	imulq	$450, %rax, %rax
	addq	%rax, -8(%rbp)
	addq	$22500, -8(%rbp)
	jmp	.L3
.L2:
	cmpl	$100, -20(%rbp)
	jle	.L4
	movl	-20(%rbp), %eax
	subl	$100, %eax
	cltq
	imulq	$225, %rax, %rax
	addq	%rax, -8(%rbp)
	jmp	.L3
.L4:
	cmpl	$0, -20(%rbp)
.L3:
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	compute_bill, .-compute_bill
	.section	.rodata
.LC0:
	.string	"%3d units -> Rs %ld.%02ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	$0, -48(%rbp)
	movl	$100, -44(%rbp)
	movl	$150, -40(%rbp)
	movl	$200, -36(%rbp)
	movl	$350, -32(%rbp)
	movl	$5, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L7
.L8:
	movl	-4(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	movl	%eax, %edi
	call	compute_bill
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rsi
	movabsq	$-6640827866535438581, %rdx
	movq	%rsi, %rax
	imulq	%rdx
	leaq	(%rdx,%rsi), %rax
	sarq	$6, %rax
	movq	%rax, %rdx
	movq	%rsi, %rax
	sarq	$63, %rax
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rsi, %rcx
	subq	%rax, %rcx
	movq	-16(%rbp), %rsi
	movabsq	$-6640827866535438581, %rdx
	movq	%rsi, %rax
	imulq	%rdx
	leaq	(%rdx,%rsi), %rax
	sarq	$6, %rax
	movq	%rax, %rdx
	movq	%rsi, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L7:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L8
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Debian 12.2.0-14+deb12u1) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
