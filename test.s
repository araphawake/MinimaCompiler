/*
00000000 <test>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	89 c1                	mov    %eax,%ecx
   5:	89 c8                	mov    %ecx,%eax
   7:	8b 55 f8             	mov    -0x8(%ebp),%edx
   a:	89 55 f8             	mov    %edx,-0x8(%ebp)
   d:	8b 55 fc             	mov    -0x4(%ebp),%edx
  10:	8b 4d f8             	mov    -0x8(%ebp),%ecx
  13:	89 ec                	mov    %ebp,%esp
  15:	5d                   	pop    %ebp
  16:	c3                   	ret    

  6:	b8 50 c3 00 00       	mov    $0xc350,%eax
   b:	b8 70 11 01 00       	mov    $0x11170,%eax
  10:	b9 50 c3 00 00       	mov    $0xc350,%ecx

00000000 <test>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	89 c1                	mov    %eax,%ecx
   5:	89 c8                	mov    %ecx,%eax

00000007 <ANTES>:
   7:	3b 4d 08             	cmp    0x8(%ebp),%ecx
   a:	3b 4d 0c             	cmp    0xc(%ebp),%ecx
   d:	3b 4d 10             	cmp    0x10(%ebp),%ecx
  10:	3b 4d 14             	cmp    0x14(%ebp),%ecx
  13:	3b 4d 18             	cmp    0x18(%ebp),%ecx
  16:	74 ef                	je     7 <ANTES>
  18:	3b 4d fc             	cmp    -0x4(%ebp),%ecx
  1b:	3b 4d f8             	cmp    -0x8(%ebp),%ecx
  1e:	3b 4d f4             	cmp    -0xc(%ebp),%ecx
  21:	3b 4d f0             	cmp    -0x10(%ebp),%ecx
  24:	3b 4d ec             	cmp    -0x14(%ebp),%ecx
  27:	74 00                	je     29 <DEPOIS>

00000029 <DEPOIS>:
  29:	89 ec                	mov    %ebp,%esp
  2b:	5d                   	pop    %ebp
  2c:	c3                   	ret


*/
.data
.text
.globl test
test:

	pushl %ebp
	movl %esp,%ebp

	movl %eax, %ecx
	movl %ecx, %eax
ANTES:
	cmpl 8(%ebp), %ecx	
	cmpl 12(%ebp), %ecx 
	cmpl 16(%ebp), %ecx
	cmpl 20(%ebp), %ecx 
	cmpl 24(%ebp), %ecx 
	je ANTES

	cmpl -4(%ebp), %ecx
	cmpl -8(%ebp), %ecx
	cmpl -12(%ebp), %ecx
	cmpl -16(%ebp), %ecx
	cmpl -20(%ebp), %ecx
	je DEPOIS

DEPOIS: 
	movl %ebp, %esp
	popl %ebp
	ret
