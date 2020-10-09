.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
#
# If the length of the vector is less than 1,
# this function exits with error code 8.
# ==============================================================================
relu:
    # Prologue
    li t2, 0

loop_start:
  lw t1, 0(a0) #t1 is the current VALUE
  bge t1, x0, loop_continue
  li t1, 0
  sw t1, 0(a0)
  addi a0, a0, 4 #moves the pointer
  addi t2, t2, 1
  blt  t2, a1, loop_start
  beq t2, a1, loop_end

loop_continue:
  sw t1, 0(a0)
  addi a0, a0, 4 #moves the pointer
  addi t2, t2, 1 #t2 is loop counter
  blt  t2, a1, loop_start
  beq t2, a1, loop_end
loop_end:


    # Epilogue


	ret
