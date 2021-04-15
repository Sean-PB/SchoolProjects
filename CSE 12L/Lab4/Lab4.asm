##############################################################################################
# Created by:  Brandon, Sean
# spbrando
# 22 May 2020
#
# Assignment:  Lab 4: Sorting Integers
#              CSE 12/L, Computer Systems and Assembly Language
#              UC Santa Cruz, Spring 2020
#
# Description: This program takes in program arguements in hex
#              form, prints them, converts them to decimal, 
#              prints them again, sorts them, then finally
#              prints the sorted decimal numbers
#
# Notes:       This program is intended to be run from the MARS IDE
##############################################################################################

################################################################################################################
# Psuedocode:
#         print first header
#     string_loop:
#         check if loop is done. If it is jump to print_converted
#         print argument the loop is on
#         print space
#         set sum to 0
#     convert_char:
#         load individual characters of each program argument
#         If finished with this individual program arguement jump to char_done
#         if the character being converted is above 9 jump to char
#         if not above 9, convert to int add jump to sum_add
#     char:
#         convert to int and jump to sum_add
#     sum_add:
#         multiply current sum by 16
#         add converted int to sum
#         jump back to convert_char
#     char_done:
#         store the sum in array
#         increment loop counter
#         move address pointer to next program argument
#         jump back to string_loop
#     print_converted:
#         print new line and second header
#         jal to extra_credit (section of code that prints out all values in array using only syscall 11)
#          
#         reset $t0
#     outer_loop:
#         if outer_loop is done jump to print_sorted
#         reset $t1 - $t5
#         increment outer_loop counter
#     inner_loop:
#         increment inner_loop counter before checking if inner_loop is done
#         if inner_loop is done jump to outer_loop
#         load in value from array
#         load in another value from array one value in front of the previously loaded value
#         if the first number is larger jump to swap
#         jump back to inner_loop and load in the numbers in front of the first number loaded in
#     swap:
#         swap the placements of the two numbers in array
#         jump back to inner_loop and load in the numbers in front of the first number loaded in
#     print_sorted:
#         print newline and 3rd header
#         jal to extra_credit (section of code that prints out all values in array using only syscall 11)
#
#         print new line
#         end program
#
#     printString:
#         this is a basic print string function
#
#     extra_credit:
#         reset $t0 and $t2 to 0
#     array_loop:
#         reset $t1, $t3, $t4, and $t5 to 0
#         if array_loop is done jump to return
#         increment loop counter
#         load in each number individually from array
#         if the number loaded in is not zero jump to number_loop
#         if it is zero, convert it to char by adding '0'
#         store the char in ascii_num
#         jump to print
#     number_loop:
#         divide the number by 10
#         convert remainder to char by adding '0'
#         store that char in ascii_num
#         if the number is 0 after being divided by 10 jump to print
#         if not 0 after being divided by 10, jump back to number_loop
#     print:
#         load the last char put into ascii_num
#         print that char
#         reset the location loaded from in ascii_num to 0
#         if done going through and printing chars in ascii_num, jump back to add_space
#         jump back to print
#     add_space:
#         print a space between numbers for output
#         jump back to array loop to start over with next int
#     return:
#         If completley done going through array and printing the ints as individual chars, jump back to $ra
################################################################################################################
.data
        array: .space 32
        ascii_num: .space 32
        program: .asciiz "Program arguements: \n"
        integer: .asciiz "\nInteger values: \n"
        sorted: .asciiz "\nSorted values: \n"
        new_line: .asciiz "\n"
        space: .asciiz " "
.text
#################################################
# REGISTER USAGE
# $s0: number of program arguments
# $t1: address to list of addresses for program 
#      arguments
#################################################
                 add  $s0 $a0 $0                      # num_of_args in $s0
                 add  $t1 $a1 $0                      # arg address in $t1

                 la   $a0 program
                 jal  printString                     # Print first header
                 
##################################################
# REGISTER USAGE
# $s0: number of program arguments
# $t1: address to list of addresses for program 
#      arguments
# $t2: 
# $t3: sum
# $t4: Argument being printed and converted
# $t5: Character from the argument to be converted
# $t6: Holds the number 16
###################################################
                 addi $t6 $t6 16                      # $t6 = 16 for later use in multiplication
string_loop:
                 beq  $s0 $t0 print_converted         # Check if loop is done
        
                 lw   $a0 ($t1)                       # Load the arg
                 jal  printString                     # Print arg
                 move $t4 $a0                         # move word location to $t4
                 la   $a0 space
                 jal  printString                     # Print space between each arg
        
                 addi $t3 $0  0                       # sum = 0
                
convert_char:
                 lb   $t5 2($t4)                      # Load the character to be converted starting after 0x
                 beqz $t5 char_done
                 addi $t4 $t4 1                       # add 1 to $t4 to move to the next character
        
        
                 bgt  $t5 57  char                    # if its A-F jump to char
                 subi $t5 $t5 48                      # if 0-9 convert
                 j    sum_add                         # jump to sum add
char:
                 subi $t5 $t5 55                      # if A-F convert
        
sum_add:
                 mul  $t3 $t3 $t6                     # sum = sum * 16
                 add  $t3 $t3 $t5                     # sum += converted digit
        
                 j    convert_char                    # Jump back to convert_char
        
char_done:
                 sw   $t3 array($t2)                  # storing converted number in array at $t2
                 addi $t2 $t2 4                       # moving $t2 to next address in preperation for next decimal

                 addi $t0 $t0 1                       # Increment loop counter
                 addi $t1 $t1 4                       # increment word pointer to next word
                 j    string_loop                     # Jump back to Loop1
        
print_converted:
                 la   $a0 new_line
                 jal  printString                     # Print new_line
                 la   $a0 integer             
                 jal  printString                     # Print 2nd header
                 
                 jal  extra_credit                    # Printing unsorted using only syscall 11 for extra credit
                 
###################################################
# REGISTER USAGE
# $s0: number of program arguments
# $t0: outer loop counter
# $t1: inner loop counter
# $t2: First number to be compared
# $t3: Second number to be compared
# $t4: Address of first number being compared
# $t5: Addres of second number being compared
###################################################
                 add  $t0 $0  $0                      # Reset $t0
outer_loop:
                 beq  $s0 $t0 print_sorted            # If inner and outer loops are done go to print_sorted
                 add  $t1 $0  $0                      # Reset $t1
                 add  $t2 $0  $0                      # Reset $t2
                 add  $t3 $0  $0                      # Reset $t3
                 add  $t4 $0  $0                      # Reset $t4
                 add  $t5 $0  $0                      # Reset $t5
                 addi $t0 $t0 1                       # Increment outer_loop
inner_loop:
                 addi $t1 $t1 1                       # Start loop incrementer at 1 so it loops through 1 less time preventing null from being swapped into the end of my array ALSO increments inner_loop
                 beq  $t1 $s0 outer_loop              # If inner_loop is done go to outer_loop
                 addi $t5 $t4 4                       # Make sure this address is one ahead of the other compared address
                 lw   $t2 array($t4)                  # Load first compare number
                 lw   $t3 array($t5)                  # Load second compare number
                 bgt  $t2 $t3 swap                    # compare first and second number. If first is greater than second j swap
                 addi $t4 $t4 4                       # If first not greater than second, move the compare number addresses...
                 j    inner_loop                      # then jump back to inner_loop
        
swap:                                                 # If swapping then:
                 sw   $t2 array($t5)                  # store first number (larger number) in second position
                 sw   $t3 array($t4)                  # store second number (smaller number) in first position
                 addi $t4 $t4 4                       # move the compare number addresses and...
                 j    inner_loop                      # jump back to inner_loop
        
        
print_sorted:
                 la   $a0 new_line
                 jal  printString                     # Print a new line to follow correct output format
                 la   $a0 sorted
                 jal  printString                     # Print 3rd header
                 
                 jal  extra_credit                    # printing sorted using only syscall 11 for extra credit points
                 
                 
                 la   $a0 new_line
                 jal  printString                     # Print a new line to follow correct output format
                 li   $v0 10
                 syscall                              # End program




printString:                                          # Print string fucntion
                 li   $v0 4
                 syscall
                 jr   $ra
                 

###################################################
# REGISTER USAGE
# $s0: number of program arguments
# $t0: loop counter
# $t1: Number to be converted to individual 
#      characters
# $t2: Location of the number to be converted
# $t3: Remainder
# $t4: Address of individual ascii characters in 
#      ascii_num
# $t5: ascii character to be printed
###################################################
extra_credit:
                 add  $t0 $0  $0                      # zero out $t0
                 add  $t2 $0  $0                      # zero out $t2
        
array_loop:
                 add  $t1 $0  $0                      # zero out $t1
                 add  $t3 $0  $0                      # zero out $t3
                 add  $t4 $0  $0                      # zero out $t4
                 add  $t5 $0  $0                      # zero out $t5
        
                 beq  $s0 $t0 return                  # if the loop is finished going through the array, j return
                 addi $t0 $t0 1                       # increment loop counter
                 lw   $t1 array($t2)                  # Load num into $t1 from place $t2 in array
                 addi $t2 $t2 4                       # Move $t2 to next location in array
                 bnez $t1 number_loop                 # If the number being converted to a string is not 0, move to number loop
                 addi $t1 $t1 '0'                     # If the number being converted to a string is 0, convert it to a string and...
                 sw   $t1 ascii_num                   # Store the 0 in ascii_num
                 j    print                           # jump to print
number_loop:
                 div  $t1 $t1 10                      # Divide num by 10
                 mfhi $t3                             # Remainder in $t3
                 addi $t3 $t3 '0'                     # Convert remainder to a string character
                 sw   $t3 ascii_num($t4)              # Store that string character in ascii_num at location $t4
                 beqz $t1 print                       # If the number is 0 after being divided by 10, then move to print
                 addi $t4 $t4 4                       # Move $t4 to the next location in ascii_num
                 j    number_loop                     # If the number is not 0 after being divided by 10 then jump back to number_loop
        
print:
                 lw   $t5 ascii_num($t4)              # Load the last value put into ascii_num
                 move $a0 $t5
                 sw   $0  ascii_num($t4)              # Reset that value to 0
                 li   $v0 11                          
                 syscall                              # Print the character that was loaded in
                 beqz $t4 add_space                   # If the address location pointer thing ($t4) is 0 j back to add_space. Otherwise...
                 subi $t4 $t4 4                       # Move $t4 to the next location to be loaded and printed in ascii_num
                 j    print                           # jump back to print
        
add_space:
                 li   $v0 4
                 la   $a0 space
                 syscall                              # Print a space in between numbers
                 j    array_loop                      # Jump back to array_loop
                 
return:
                 jr   $ra                             # If completley done, jump back to wherever this was called
