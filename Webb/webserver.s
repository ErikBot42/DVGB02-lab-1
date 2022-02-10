	.file	"webserver.c"
	.text
	.globl	prefix
	.type	prefix, @function
prefix:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncmp@PLT
	testl	%eax, %eax
	sete	%al
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	prefix, .-prefix
	.section	.rodata
.LC0:
	.string	"%.*s"
	.text
	.globl	writeAndPrint
	.type	writeAndPrint, @function
writeAndPrint:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movl	-4(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	writeAndPrint, .-writeAndPrint
	.globl	pln
	.type	pln, @function
pln:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	pln, .-pln
	.section	.rodata
.LC1:
	.string	"socket failed"
.LC2:
	.string	"bind failed"
.LC3:
	.string	"listen failed"
	.align 8
.LC4:
	.string	"---------------------------------"
	.align 8
.LC5:
	.string	"waiting for connection request..."
.LC6:
	.string	""
.LC7:
	.string	"accept failed"
.LC8:
	.string	"Recived request:\n"
.LC9:
	.string	" \n"
.LC10:
	.string	"requestMethod invalid"
.LC11:
	.string	"Request method: %s\n"
.LC12:
	.string	"requestedFile invalid"
.LC13:
	.string	"Request file: %s\n"
.LC14:
	.string	"httpVersion invalid"
.LC15:
	.string	"HTTP version: %s\n"
.LC16:
	.string	"response:"
.LC17:
	.string	"r"
.LC18:
	.string	"%s HTTP version: %s\n"
.LC19:
	.string	"first: %s HTTP version: %s\n"
.LC20:
	.string	"cannot open requested file"
	.align 8
.LC21:
	.string	"%s 200 OK\nServer: A Web Server\nContent-Length: %d\nContent-Type: text/html\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$4096, %rsp
	orq	$0, (%rsp)
	addq	$-128, %rsp
	movl	%edi, -4212(%rbp)
	movq	%rsi, -4224(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-4128(%rbp), %rax
	movl	$16, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movw	$2, -4128(%rbp)
	movl	$0, %edi
	call	htonl@PLT
	movl	%eax, -4124(%rbp)
	movl	$8080, %edi
	call	htons@PLT
	movw	%ax, -4126(%rbp)
	movl	$6, %edx
	movl	$1, %esi
	movl	$2, %edi
	call	socket@PLT
	movl	%eax, -4200(%rbp)
	cmpl	$0, -4200(%rbp)
	jns	.L6
	leaq	.LC1(%rip), %rdi
	call	fatal
.L6:
	movl	$1, -4204(%rbp)
	leaq	-4204(%rbp), %rdx
	movl	-4200(%rbp), %eax
	movl	$4, %r8d
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	setsockopt@PLT
	leaq	-4128(%rbp), %rcx
	movl	-4200(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	bind@PLT
	movl	%eax, -4196(%rbp)
	cmpl	$0, -4196(%rbp)
	jns	.L7
	leaq	.LC2(%rip), %rdi
	call	fatal
.L7:
	movl	-4200(%rbp), %eax
	movl	$10, %esi
	movl	%eax, %edi
	call	listen@PLT
	movl	%eax, -4192(%rbp)
	cmpl	$0, -4192(%rbp)
	jns	.L17
	leaq	.LC3(%rip), %rdi
	call	fatal
.L17:
	leaq	.LC4(%rip), %rdi
	call	pln
	leaq	.LC5(%rip), %rdi
	call	pln
	leaq	.LC6(%rip), %rdi
	call	pln
	leaq	.LC6(%rip), %rdi
	call	pln
	movl	-4200(%rbp), %eax
	movl	$0, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	accept@PLT
	movl	%eax, -4188(%rbp)
	cmpl	$0, -4188(%rbp)
	jns	.L9
	leaq	.LC7(%rip), %rdi
	call	pln
	jmp	.L16
.L9:
	leaq	-4112(%rbp), %rcx
	movl	-4188(%rbp), %eax
	movl	$4096, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	leaq	.LC8(%rip), %rdi
	call	pln
	leaq	-4112(%rbp), %rax
	movq	%rax, %rdi
	call	pln
	leaq	-4112(%rbp), %rax
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -4184(%rbp)
	cmpq	$0, -4184(%rbp)
	jne	.L11
	leaq	.LC10(%rip), %rdi
	call	pln
	jmp	.L16
.L11:
	movq	-4184(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC11(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC9(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -4176(%rbp)
	cmpq	$0, -4176(%rbp)
	jne	.L12
	leaq	.LC12(%rip), %rdi
	call	pln
	jmp	.L16
.L12:
	movq	-4176(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC9(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -4168(%rbp)
	cmpq	$0, -4168(%rbp)
	jne	.L13
	leaq	.LC14(%rip), %rdi
	call	pln
	jmp	.L16
.L13:
	movq	-4168(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC15(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC16(%rip), %rdi
	call	pln
	movq	-4176(%rbp), %rax
	addq	$1, %rax
	leaq	.LC17(%rip), %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -4160(%rbp)
	movl	$1048576, %edi
	call	malloc@PLT
	movq	%rax, -4152(%rbp)
	cmpq	$0, -4160(%rbp)
	jne	.L14
	movq	-4168(%rbp), %rdx
	movq	-4168(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC18(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-4168(%rbp), %rdx
	movq	-4168(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC19(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-4168(%rbp), %rcx
	movq	-4168(%rbp), %rdx
	movq	-4152(%rbp), %rax
	leaq	.LC18(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	movq	-4152(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-4152(%rbp), %rcx
	movl	-4188(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	writeAndPrint
	movq	-4168(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC15(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC20(%rip), %rdi
	call	pln
	jmp	.L15
.L14:
	movq	-4160(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-4160(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, -4144(%rbp)
	movq	-4160(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-4144(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -4136(%rbp)
	movq	-4144(%rbp), %rdx
	movq	-4160(%rbp), %rcx
	movq	-4136(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-4144(%rbp), %rcx
	movq	-4168(%rbp), %rdx
	movq	-4152(%rbp), %rax
	leaq	.LC21(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	movq	-4152(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-4152(%rbp), %rcx
	movl	-4188(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	writeAndPrint
	movq	-4144(%rbp), %rdx
	movq	-4136(%rbp), %rcx
	movl	-4188(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	writeAndPrint
	movq	-4136(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-4160(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
.L15:
	movq	-4152(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	-4188(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
.L16:
	jmp	.L17
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.globl	fatal
	.type	fatal, @function
fatal:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE10:
	.size	fatal, .-fatal
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
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
