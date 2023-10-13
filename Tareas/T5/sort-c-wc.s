	.file	"sort-c-wc.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	strCmp
	.type	strCmp, @function
strCmp:
	mv	a5,a0
	lbu	a4,0(a0)
	beq	a4,zero,.L8
	li	a3,0
	li	a0,0
	li	a2,32
	li	a6,0
	li	a7,1
	j	.L4
.L9:
	mv	a3,a6
.L3:
	addi	a5,a5,1
	lbu	a4,0(a5)
	beq	a4,zero,.L2
.L4:
	beq	a4,a2,.L9
	bne	a3,zero,.L3
	addi	a0,a0,1
	mv	a3,a7
	j	.L3
.L8:
	li	a0,0
.L2:
	lbu	a5,0(a1)
	beq	a5,zero,.L1
	li	a4,0
	li	a3,32
	li	a2,0
	li	a6,1
	j	.L7
.L10:
	mv	a4,a2
.L6:
	addi	a1,a1,1
	lbu	a5,0(a1)
	beq	a5,zero,.L1
.L7:
	beq	a5,a3,.L10
	bne	a4,zero,.L6
	addi	a0,a0,-1
	mv	a4,a6
	j	.L6
.L1:
	ret
	.size	strCmp, .-strCmp
	.align	2
	.globl	sort
	.type	sort, @function
sort:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	sw	s2,16(sp)
	sw	s3,12(sp)
	sw	s4,8(sp)
	slli	s3,a1,2
	addi	s3,s3,-4
	add	s3,a0,s3
	bgeu	a0,s3,.L13
	mv	s4,a0
	mv	s0,a0
	j	.L17
.L15:
	sw	s2,0(s0)
	sw	s1,4(s0)
	mv	s0,s4
.L17:
	lw	s1,0(s0)
	lw	s2,4(s0)
	mv	a1,s2
	mv	a0,s1
	call	strCmp
	bgt	a0,zero,.L15
	addi	s0,s0,4
	bgtu	s3,s0,.L17
.L13:
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	lw	s2,16(sp)
	lw	s3,12(sp)
	lw	s4,8(sp)
	addi	sp,sp,32
	jr	ra
	.size	sort, .-sort
	.ident	"GCC: (GNU) 11.1.0"
