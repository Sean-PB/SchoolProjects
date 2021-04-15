#################################################################
# Created by:  Brandon, Sean
#              spbrando
#              12 May 2020
#
# Assignment:  Lab 3: ASCII-risks (Asterisks)
#              CSE12/L, Computer Systems and Assembly Language
#              UC Santa Cruz, Spring 2020
#
# Description: This program asks the user for input on the 
#              height of the pattern. If the height is less
#              than 1 it will continue to ask for input until
#              height is greaater than 0. The pattern will be
#              a rectangle made up of two right triangles with
#              a upside down pyramid between them made up of
#              asterisks. The right triangles are made up of
#              ascending numbers.
#
# Notes:       This program is intended to be run from MARS IDE.
#################################################################

#################################################################
# Pseudocode:
#
# This program prints out a rectangle with a pattern of ascending
# numbers and astrisks. The rectangles height is determined by the
# user.
# .data
#         all static data
# .text
# prompt_loop
#         prompts user for height of pattern until the input > 0
# pattern
#         length = height x 2
# outer_loop
#         print new_line
#         increment row by 1
#         If height < row, jump to outer_exit
#         reset col to 0
# inner_loop
#         Increment col by 1
#         If col <= row, jump to first_half
#         If col > length - row, jump to second_half
#         Otherwise print asterisks and jump back to inner_loop
# first_half
#         left_num += 1
#         print left_num and tab
#         right_num = left_num
#         lef_num += 1
#         jump back to inner_loop
# second_half
#         print right_num
#         right_num -= 1
#         If col == length, jump to outer_loop
#         Otherwise print tab and jump back to inner_loop
# outer_exit
#         successfully end program
#
# print_string
#         Print string function
# print_num
#         Print num function
#################################################################
.data
        prompt: .asciiz "Enter the height of the pattern (must be greater than 0):\t"
        error_message: .asciiz "Invalid Entry!\n"
        star: .asciiz "*\t"
        tab: .asciiz "\t"
        new_line: .asciiz "\n"

.text
#################################################################
# BLOCK COMMENT
# Register Usage
# $a0: Used as arguement for printing
# $v0: Used as arguement for syscalls
# $s0: Height
# $s1: Length
# $t0: right_num
# $t1: left_num
# $t2: row
# $t3: col
# $t4: (length - row)
#################################################################



########################################################
# Register Usage
# $s0: height
# $a0: Used as arguement for printing
# $v0: Used as arguement for syscalls
########################################################
prompt_loop:
             la   $a0   prompt
             jal  print_string               # Prompt user for height
             li   $v0   5
             syscall                         # Get user input
             move $s0   $v0
             bgtz $s0   pattern              # Checks if users input is valid or not.
             la   $a0   error_message
             jal  print_string               # Prints error message
             j    prompt_loop
             
########################################################
# Register Usage
# $a0: Used as arguement for printing
# $s0: height
# $s1: Length
# $t2: row
# $t3: col
########################################################
pattern:
             add  $s1   $s0   $s0            # length = heihgt * 2 
outer_loop:
             la   $a0   new_line
             jal  print_string               # print new_line
             addi $t2   $t2   1              # Increment row by 1
             blt  $s0   $t2   outer_exit     # If height < row, jump to outer_exit
             addi $t3   $0    0              # resets col to 0 everytime
             
########################################################
# Register Usage
# $a0: Used as arguement for printing
# $s1: length
# $t2: row
# $t3: col
# $t4: (length - row)
########################################################
inner_loop:
             addi $t3   $t3   1              # Increment col by 1
             ble  $t3   $t2   first_half     # If col <= row, jump to first_half
             sub  $t4   $s1   $t2            # length - row
             bgt  $t3   $t4   second_half    # If col > length - row, jump to second_half
             la   $a0   star
             jal  print_string               # Print the asterisks
             j    inner_loop                 # Jump back to inner_loop
             
########################################################
# Register Usage
# $a0: Used as arguement for printing
# $t0: right_num
# $t1: left_num
########################################################
first_half:
             addi $t1   $t1   1              # left_num += 1
             move $a0   $t1
             jal  print_num                  # print left_num
             la   $a0   tab
             jal  print_string               # print tab after
             add  $t0   $0    $t1            # right_num = left_num
             j    inner_loop                 # Jump back to inner_loop
             
########################################################
# Register Usage
# $a0: Used as arguement for printing
# $s1: length
# $t0: right_num
# $t3: col
########################################################
second_half:
             move $a0   $t0
             jal  print_num                  # print right_num
             subi $t0   $t0   1              # right_num - 1
             beq  $t3   $s1   outer_loop     # If col == length, jump to outer_loop
             la   $a0   tab
             jal  print_string               # print tab after
             j    inner_loop                 # Jump back to inner_loop
             
########################################################
# Register Usage
# $a0: Used as arguement for printing
# $v0: Used as arguement for syscalls
########################################################
outer_exit:
             li   $v0   10
             syscall                         # Successfully end the program
             
########################################################
# Register Usage
# $a0: Used as arguement for printing
# $v0: Used as arguement for syscalls
########################################################
             
print_string:                                # Print string function
             addi $v0   $0   4
             syscall
             jr $ra

########################################################
# Register Usage
# $a0: Used as arguement for printing
# $v0: Used as arguement for syscalls
########################################################
print_num:                                   # Print num function
             addi $v0   $0   1
             syscall
             jr   $ra
