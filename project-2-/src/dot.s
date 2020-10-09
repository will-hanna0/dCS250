.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
#
# If the length of the vector is less than 1,
# this function exits with error code 5.
# If the stride of either vector is less than 1,
# this function exits with error code 6.
# =======================================================
dot:

    # Prologue
    li t0, 1
    blt a2, t0, endfive
    blt a3, t0, endeight
    blt a4, t0, endeight
    li t1, 4
    mul a3, a3, t1
    mul a4, a4, t1
    li t1, 0
     # t1 is Final answer
    # a3 v0 stride variable
    # a4 v1 stride variable
    li t4, 0 #loop count
    # 1


    j loop_start

loop_start:
    addi t4, t4, 1
    lw t2, 0(a0) # set t2 to current v0 value
    lw t3, 0(a1) # set t3 to current v1 value
    mul t5, t2, t3 #t5 is the step variable
    add t1, t1, t5
    add a0, a0, a3 #increment the pointers
    add a1, a1, a4
    blt t4, a2, loop_start
    j loop_end

endfive:
  li, a1, 5
  jal ra exit2

endeight:
  li, a1, 8
  jal ra exit2

loop_end:

  mv a0, t1


    # Epilogue


    ret
