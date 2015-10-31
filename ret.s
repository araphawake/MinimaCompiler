/*
00000000 <ret>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	8b 45 08             	mov    0x8(%ebp),%eax
   6:	89 ec                	mov    %ebp,%esp
   8:	5d                   	pop    %ebp
   9:	c3                   	ret    

00000000 <ret>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 04             	sub    $0x4,%esp
   6:	8b 45 08             	mov    0x8(%ebp),%eax
   9:	89 45 fc             	mov    %eax,-0x4(%ebp)
   c:	8b 45 fc             	mov    -0x4(%ebp),%eax
   f:	89 ec                	mov    %ebp,%esp
  11:	5d                   	pop    %ebp
  12:	c3                   	ret    


*/

.data
.text
.globl ret
ret:
	pushl %ebp
	movl %esp, %ebp
	
	subl $4, %esp
	movl 8(%ebp), %eax
	movl %eax, -4(%ebp)
	movl -4(%ebp), %eax

	movl %ebp, %esp
	popl %ebp
	ret
