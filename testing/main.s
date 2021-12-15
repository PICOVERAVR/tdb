// gcc main.s -nostdlib -no-pie -o main.out
.global _start

	.text
_start:

	push %rbp
	mov %rsp, %rbp

	mov $0xFF, %r15

	// write
	mov $0x1, %rax
	mov $0x1, %rdi
	mov $message, %rsi
	mov $0x12, %rdx
	syscall

	// exit
	mov $60, %rax
	xor %rdi, %rdi
	syscall

message:
	.ascii "Hello World\n"
