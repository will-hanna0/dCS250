.globl matmul


.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
#   The order of error codes (checked from top to bottom):
#   If the dimensions of m0 do not make sense,
#   this function exits with exit code 2.
#   If the dimensions of m1 do not make sense,
#   this function exits with exit code 3.
#   If the dimensions don't match,
#   this function exits with exit code 4.
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# =======================================================

matmul:

case2:
    mul t0 a1 a2
    bgt t0 zero case3
    li a1 2
    jal exit2
case3:
    mul t0 a4 a5
    bgt t0 zero case4
    li a1 3
    jal exit2
case4:
    beq a2 a4 setup
    li a1 4
    jal exit2


setup:
    # Prologue
    addi sp sp -20 #make space for 5 variables
    sw s0 0(sp) #save s registers
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)

    li s0 0
    li s1 0

outer_loop_start:
    bge s1 a1  outer_loop_end
    li s2 0

    slli t0 s1 2
    mul t0 t0 a2
    add s3 a0 t0


inner_loop_start:
    bge s2 a5 inner_loop_end

    slli t2 s2 2
    add  t2 t2 a3

    addi sp sp -24 # make space for 6 variables
    sw ra 0(sp)
    sw a0 4(sp)
    sw a1 8(sp)
    sw a2 12(sp)
    sw a3 16(sp)
    sw a4 20(sp)

    mv a0 s3
    mv a1 t2
    mv a2 a2
    li a3 1
    mv a4 a5


    jal ra dot #multiply the vectors

    slli t1 s0 2
    add t1 t1 a6
    sw a0 0(t1)
    addi s0 s0 1

    lw ra 0(sp) #load back ra and a registers
    lw a0 4(sp)
    lw a1 8(sp)
    lw a2 12(sp)
    lw a3 16(sp)
    lw a4 20(sp)
    addi sp sp 24

    addi s2 s2 1

    j inner_loop_start

inner_loop_end:
    addi s1 s1 1
    j outer_loop_start

outer_loop_end:
    # Epilogue

    lw s0 0(sp) #load back the s registers
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    sw s4 16(sp)
    addi sp sp  20 #move back stack pointer

    ret
