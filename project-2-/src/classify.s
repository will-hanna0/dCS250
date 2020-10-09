.globl classify

.text
classify:
    # =====================================
    # COMMAND LINE ARGUMENTS
    # =====================================
    # Args:
    #   a0 (int)    argc
    #   a1 (char**) argv
    #   a2 (int)    print_classification, if this is zero,
    #               you should print the classification. Otherwise,
    #               this function should not print ANYTHING.
    # Returns:
    #   a0 (int)    Classification
    #
    # If there are an incorrect number of command line args,
    # this function returns with exit code 49.
    #
    # Usage:
    #   main.s -m -1 <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>


        addi t0 x0 5 #set t0 to 5

        bne a0 t0 exit49 #error 49



        addi sp sp -36 # create space in sp

        #save ra and s registers
        sw ra 0(sp)
        sw s0 4(sp)
        sw s1 8(sp)
        sw s2 12(sp)
        sw s3 16(sp)
        sw s4 20(sp)
        sw s5 24(sp)
        sw s6 28(sp)
        sw s7 32(sp)


        mv s0 a1
        mv s1 a2

        addi sp sp -24 #make space for 6 in sp

        lw  a0 4(s0)
        addi a1 sp 0
        addi a2 sp 4
        jal ra read_matrix
        mv s2 a0

        lw a0 8(s0)
        addi a1 sp 8
        addi a2 sp 12
        jal ra read_matrix
        mv s3 a0


        lw a0 12(s0)
        addi a1 sp 16
        addi a2 sp 20
        jal ra read_matrix
        mv s4 a0
        lw t0 0(sp)
        lw t5 20(sp)

        mul s5 t0 t5
        slli a0 s5 2
        jal ra malloc
        mv  s6 a0

        #load back the t registers
        lw t0 0(sp)
        lw t1 4(sp)
        lw t6 16(sp)
        lw t5 20(sp)

        #move values into respective a registers
        mv a0 s2
        mv a1 t0
        mv a2 t1
        mv a3 s4
        mv a4 t6
        mv a5 t5
        mv a6 s6
        jal ra matmul

        mv a0 s6
        mv a1 s5
        jal ra relu

        lw t0 8(sp)
        lw t1 20(sp)
        mul s5 t0 t1
        slli a0 s5 2
        jal ra malloc
        mv s7 a0

        #load back the t registers
        lw t0 8(sp)
        lw t1 12(sp)
        lw t6 0(sp)
        lw t5 20(sp)

        #move values into respective a registers
        mv a0 s3
        mv a1 t0
        mv a2 t1
        mv a3 s6
        mv a4 t6
        mv a5 t5
        mv a6 s7
        jal ra matmul

        lw a0 16(s0)
        mv a1 s7
        lw a2 8(sp)
        lw a3 20(sp)
        jal ra write_matrix

        mv a0 s7
        mv a1 s5
        jal ra argmax

        bne s1 x0 print_nothing
        mv a1 a0
        jal ra print_int

    print_nothing:


        #new line
        li a1 '\n'
        jal print_char

        #free
        mv a0 s2
        jal ra free
        mv a0 s3
        jal ra free
        mv a0 s4
        jal ra free
        mv a0 s6
        jal ra free
        mv a0 s7
        jal ra free

        # Epilogue

        addi sp sp 24 #move up sp

        lw ra 0(sp)# load back ra and s registers
        lw s0 4(sp)
        lw s1 8(sp)
        lw s2 12(sp)
        lw s3 16(sp)
        lw s4 20(sp)
        lw s5 24(sp)
        lw s6 28(sp)
        lw s7 32(sp)

        addi sp sp 36 #move up sp all the way

        ret

        #exit code(s)

    exit49:
        li a1 49
        jal ra exit2
