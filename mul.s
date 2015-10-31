/*
00000000 <mul>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	8b 45 08             	mov    0x8(%ebp),%eax
   6:	8b 55 0c             	mov    0xc(%ebp),%edx
   9:	0f af c2             	imul   %edx,%eax
   c:	89 ec                	mov    %ebp,%esp
   e:	5d                   	pop    %ebp
   f:	c3                   	ret
*/

.data
.text
.globl mul
mul:
	pushl %ebp
	movl %esp,%ebp

	movl 8(%ebp), %eax
	movl 12(%ebp), %edx
	imull %edx, %eax

	movl %ebp, %esp
	popl %ebp
	ret
