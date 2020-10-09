.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
#
# If the length of the vector is less than 1,
# this function exits with error code 7.
# =================================================================
argmax:

    # Prologue
    li t2, 0 # t2 will be the MAX VALUE
    li t4, 0 #t4 is loopcount


loop_start:
  lw t1, 0(a0) #t1 is current VALUE
  bgt t1, t2, loop_large
  #bge t1, t2, loop_same
  addi a0, a0, 4 # move pointer
  addi t4, t4, 1
  blt t4, a1, loop_start
  bge t4, a1, loop_end

loop_same:


loop_large:
  mv t2, t1 #sets t2 to the max value
  mv t5, t4
  addi a0, a0, 4 # move pointer
  addi t4, t4, 1
  blt t4, a1, loop_start
  bge t4, a1, loop_end




loop_end:

  mv a0, t5


    # Epilogue


    ret
