.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#   If any file operation fails or doesn't read the proper number of bytes,
#   exit the program with exit code 1.
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
#
# If you receive an fopen error or eof,
# this function exits with error code 50.
# If you receive an fread error or eof,
# this function exits with error code 51.
# If you receive an fclose error or eof,
# this function exits with error code 52.
# ==============================================================================
read_matrix:

    # Prologue

    addi sp sp -24 #make space for ra and s registers
    sw ra 0(sp)
    sw s0 4(sp)
    sw s1 8(sp)
    sw s2 12(sp)
    sw s3 16(sp)
    sw s4 20(sp)

    mv s0 a1
    mv s1 a2

    mv a1 a0
    addi a2 x0 0
    jal ra fopen
    blt a0 zero exit50 #error 50
    mv s2 a0

    mv a1  s2
    mv a2  s0
    li a3  4
    jal ra fread
    blt a0 zero exit51 #error 51
    addi t3 x0 4
    bne a0 t3 exit1 #error 1

    mv a1  s2
    mv a2  s1
    li a3  4
    jal ra fread
    blt a0 zero exit51 #error 51
    addi t3 x0 4
    bne a0 t3 exit1 #error 1

    lw s0 0(s0)
    lw s1 0(s1)
    mul t3 s0 s1 #total size of row*col

    #make space
    slli s3 t3 2
    mv a0 s3
    jal ra malloc
    mv s4 a0

    mv a1 s2
    mv a2 s4
    mv a3 s3
    jal ra fread
    blt a0 zero exit51 #error 51
    bne a0 s3 exit1 #error 1

    mv a0 s2
    jal ra fclose
    bne a0 zero exit52 #error 52

    # Epilogue
    mv a0 s4 #set return

    lw ra 0(sp)# load back s registers and ra
    lw s0 4(sp)
    lw s1 8(sp)
    lw s2 12(sp)
    lw s3 16(sp)
    lw s4 20(sp)
    addi sp sp 24

    ret


		# Exit Codes

exit1:
    li a1 1
    jal ra exit2

exit50:
    li a1 50
    jal ra exit2

exit51:
    li a1 51
    jal ra exit2

exit52:
    li a1 52
    jal ra exit2
