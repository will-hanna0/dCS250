.import ../../src/read_matrix.s
.import ../../src/utils.s

.data
file_path: .asciiz "inputs/test_read_matrix/test_input.bin"

.text
main:
# Read matrix into memory
addi a0 x0 4
jal ra malloc
mv a1 a0

addi a0 x0 4
jal ra malloc
mv a2 a0

la a0 file_path

jal ra read_matrix

# Print out elements of matrix
lw a1 0(a1)
lw a2 0(a2)
jal ra print_int_array

# Terminate the program
addi a0, x0, 10
ecall
