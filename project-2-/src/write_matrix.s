.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
#   If any file operation fails or doesn't write the proper number of bytes,
#   exit the program with exit code 1.
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
#
# If you receive an fopen error or eof,
# this function exits with error code 53.
# If you receive an fwrite error or eof,
# this function exits with error code 54.
# If you receive an fclose error or eof,
# this function exits with error code 55.
# ==============================================================================
write_matrix:

    # Prologue

    addi sp sp -24 #make space in stack

    sw ra 0(sp)# save s registers and ra
    sw s0 4(sp)
    sw s1 8(sp)
    sw s2 12(sp)

    sw a2 16(sp)# save a registers
    sw a3 20(sp)

    mv s1 a1
    mul s2 a2 a3 # size of the whole matrix (row*col)

    mv a1 a0
    li a2 1
    jal ra fopen
    blt a0 x0 exit53 # error 53
    mv s0 a0

    mv a1 s0
    addi a2 sp 16
    li a3 1
    li a4 4
    jal ra fwrite
    blt a0 x0 exit54 # error 54
    addi t1 x0 1
    bne a0 t1 exit1 # error 1

    mv a1 s0
    addi a2 sp 20
    li a3 1
    li a4 4
    jal ra fwrite
    blt a0 x0 exit54 # error 54
    addi t1 x0 1
    bne a0 t1 exit1 # error 1

    mv a1 s0
    mv a2 s1
    mv a3 s2
    li a4 4
    jal ra fwrite
    blt a0 x0 exit54 # error 54
    bne a0 s2 exit1 # error 1

    mv a1 s0
    jal ra fclose
    bne a0 x0 exit55 # error 55

    # Epilogue
    lw ra 0(sp)# load back s registers and ra
    lw s0 4(sp)
    lw s1 8(sp)
    lw s2 12(sp)

    addi sp sp 24 #put the pointer back to top

    ret



    #error codes

exit1:
    li a1 1
    jal ra exit2

exit53:
    li a1 53
    jal ra exit2

exit54:
    li a1 54
    jal ra exit2

exit55:
    li a1 55
    jal ra exit2
