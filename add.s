/*
00000000 <add>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	8b 45 08             	mov    0x8(%ebp),%eax
   6:	8b 4d 0c             	mov    0xc(%ebp),%ecx
   9:	01 c8                	add    %ecx,%eax
   b:	89 ec                	mov    %ebp,%esp
   d:	5d                   	pop    %ebp
   e:	c3                   	ret    

*/

.data
.text
.globl add
add:
	pushl %ebp
	movl %esp,%ebp

	movl 8(%ebp), %eax
	movl 12(%ebp), %ecx
	addl %ecx, %eax

	movl %ebp, %esp
	popl %ebp
	ret
