#Spring20 Lab5 Template File

# Macro that stores the value in %reg on the stack 
#  and moves the stack pointer.
.macro push(%reg)
	subi $sp  $sp 4				# Move stack pointer 
	sw   %reg 0($sp)			# Store the word
.end_macro 

# Macro takes the value on the top of the stack and 
#  loads it into %reg then moves the stack pointer.
.macro pop(%reg)
	lw   %reg 0($sp)			# Load the word
	addi $sp  $sp 4				# Move stack pointer
.end_macro

# Macro that takes as input coordinates in the format
# (0x00XX00YY) and returns 0x000000XX in %x and 
# returns 0x000000YY in %y
.macro getCoordinates(%input %x %y)
	srl  %x %input 0x10			# Shift right logical to single out the x values
	andi %y %input 0xFF			# Mask to single out the y values
.end_macro

# Macro that takes Coordinates in (%x,%y) where
# %x = 0x000000XX and %y= 0x000000YY and
# returns %output = (0x00XX00YY)
.macro formatCoordinates(%output %x %y)
	sll %output %x      0x10		# Shift left logical to move the x values
	add %output %output %y			# add the y values to the end
.end_macro 


.data
originAddress: .word 0xFFFF0000

.text
####################################################
# pseudocode :
# clear_bitmap:
#	(see subroutine for more detail)
# draw_pixel:
# 	(see subroutine for more detail)
# get_pixel:
#	(see subroutine for more detail)
# draw_solid_circle:
# 	(see subroutine for more detail)
# draw_circle:
# 	(see subroutine for more detail)
# draw_circle_pixels:
# 	(see subroutine for more detail)
####################################################


j done
    
    done: nop
    li $v0 10 
    syscall

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#*****************************************************
#Clear_bitmap: Given a color, will fill the bitmap display with that color.
#   Inputs:
#    $a0 = Color in format (0x00RRGGBB) 
#   Outputs:
#    No register outputs
#    Side-Effects: 
#    Colors the Bitmap display all the same color
#*****************************************************
######################################################
# Psuedocode:
# clear_bitmap:
# 	loop counter starts at 0x4000 because thats how many pixels there are
#	start addressing at 0xffff0000 to fill in bitmap
# clear_loop:
#	check if loop is done. if it is jump to clear_exit
#	decrement loop counter by one
#	store color at address
#	increment address by one word (4)
#	jump back to top of loop
# clear_exit:
#	jump to return address
############################################
clear_bitmap: 	nop
		addi $t0 $0  0x4000		# Loop counter (to be decremendted)
		addi $t1 $0  0xffff0000	# Start address at 0xffff0000
clear_loop:	nop
		beqz $t0 clear_exit		# If loop is done jump to clear_exit
		nop
		subi $t0 $t0 1			# Decrement loop counter
		sw   $a0 ($t1)			# store color at location
		addi $t1 $t1 4			# increment location
		b    clear_loop			# go back to top of loop
		nop
	
clear_exit:	nop
		jr   $ra
	
#*****************************************************
# draw_pixel:
#  Given a coordinate in $a0, sets corresponding value
#  in memory to the color given by $a1	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#*****************************************************
#############################################
# Psuedocode:
# draw_pixel:
#	getCooridinates to break x and y out of their format
#	store the color at ((((y-point * width) + x-point) * 4) + 0xFFFF0000)
#	jump to return address
##############################################
draw_pixel: 	nop
		# (((y-coordinate * width) + x-coordinate) * 4) + 0xFFFF0000
		getCoordinates($a0 $t0 $t1)  # find x and y coordinates
		mul  $t1 $t1 128             #(y-point * width)
		add  $t1 $t1 $t0             #((y-point * width) + x-point)
		mul  $t1 $t1 4               #(((y-point * width) + x-point) * 4)
		addi $t1 $t1 0xFFFF0000      #(((y-point * width) + x-point) * 4) + 0xFFFF0000
		sw   $a1 ($t1)               # store the color in the correct address according to the coordinates
	
		jr   $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#   Outputs:
#    Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
###############################################
# Psuedocode:
# get_pixel:
#	getCooridinates to break x and y out of their format
#	load the color at ((((y-point * width) + x-point) * 4) + 0xFFFF0000)
#	jump to return address
###############################################
get_pixel: 	nop
		# (((y-coordinate * width) + x-coordinate) * 4) + 0xFFFF0000
		getCoordinates($a0 $t0 $t1)  # find x and y coordinates
		mul  $t1 $t1 128             #(y-point * width)
		add  $t1 $t1 $t0             #((y-point * width) + x-point)
		mul  $t1 $t1 4               #(((y-point * width) + x-point) * 4)
		addi $t1 $t1 0xFFFF0000      #(((y-point * width) + x-point) * 4) + 0xFFFF0000
		lw   $v0 ($t1)               # load the color in the correct address according to the coordinates
		jr   $ra

#***********************************************
# draw_solid_circle:
#  Considering a square arround the circle to be drawn  
#  iterate through the square points and if the point 
#  lies inside the circle (x - xc)^2 + (y - yc)^2 = r^2
#  then plot it.
#-----------------------------------------------------
# Psuedocode:
# draw_solid_circle(int xc, int yc, int r) 
#    xmin = xc-r
#    xmax = xc+r
#    ymin = yc-r
#    ymax = yc+r
#    for (i = xmin; i <= xmax; i++) 
#        for (j = ymin; j <= ymax; j++) 
#            a = (i - xc)*(i - xc) + (j - yc)*(j - yc)	 
#            if (a < r*r ) 
#                draw_pixel(x,y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#***************************************************
draw_solid_circle: 	nop
			# Preserve S registers
			push($s0)
			push($s1)
			push($s2)
			push($s3)
			push($s4)
			push($s5)
			push($s6)
			push($s7)
	
			# $s0: xc
			# $s1: yc
			# $s2: xmin
			# $s3: xmax
			# $s4: ymin
			# $s5: ymax
			# $t0: i
			# $t1: j
			# $s6: radius
			# $a1: color
			getCoordinates($a0 $s0 $s1)		# xc in $s0, yc in $s1
			add  $s6 $a1 $0				# radius in $s6
			sub  $s2 $s0 $s6			# $s2 = xc - radius = xmin
			add  $s3 $s0 $s6			# $s3 = xc + radius = xmax
			sub  $s4 $s1 $s6			# $s4 = yc - radius = ymin
			add  $s5 $s1 $s6			# $s5 = yc + radius = ymax
			add  $a1 $a2 $0				# move color into $a1 for draw_pixel subroutine
	
			subi $t0 $s2 1				# i = xmin - 1 (so that when I increment $t0 the first time its accurate)
			
solid_outer_for:	nop
			addi $t0 $t0 1				# increment i by 1
			bgt  $t0 $s3 solid_done		# if i is not <= xmax, branch to solid_done
			nop
	
			subi $t1 $s4 1				# j = ymin - 1 (so that when I increment $t1 the first time its accurate)
solid_inner_for:	nop
			addi $t1 $t1 1				# Increment j by 1
			bgt  $t1 $s5 solid_outer_for		# if j is not <= ymax, branch back to outer loop
			nop
			# a = (i - xc)*(i - xc) + (j - yc)*(j - yc)	 
			sub  $t2 $t0 $s0			# (i - xc)
			mul  $t2 $t2 $t2			# (i - xc) * (i - xc)
			sub  $t3 $t1 $s1			# (j - yc)
			mul  $t3 $t3 $t3			# (j - yc) * (j - yc)
			add  $t2 $t2 $t3			# a = $t2 = (i - xc)*(i - xc) + (j - yc)*(j - yc)
			mul  $t3 $s6 $s6			# radius * radius
			bge  $t2 $t3 solid_inner_for		# if a is not < r*r branch back to top of inner loop
			nop
	
			# otherwise save the return address and jump to draw_pixel subroutine
			formatCoordinates($a0 $t0 $t1)		# format the coordinates to be printed in draw pixel
			push ($ra)				# save return address to stack
			push ($t0)				# preserve value in $t0 because this is the caller
			push ($t1)				# preserve value in $t1 because this is the caller
			jal  draw_pixel				# jump and link to draw_pixel subroutine
			pop  ($t1)				# restore $t1
			pop  ($t0)				# restore $t0
			pop  ($ra)				# restore $ra
			j    solid_inner_for			# jump back to top of inner loop
	
solid_done:		nop
			# restore S registers
			pop($s7)
			pop($s6)
			pop($s5)
			pop($s4)
			pop($s3)
			pop($s2)
			pop($s1)
			pop($s0)
	
			jr   $ra
		
#***********************************************
# draw_circle:
#  Given the coordinates of the center of the circle
#  plot the circle using the Bresenham's circle 
#  drawing algorithm 	
#-----------------------------------------------------
# Psuedocode:
# draw_circle(xc, yc, r) 
#    x = 0 
#    y = r 
#    d = 3 - 2 * r 
#    draw_circle_pixels(xc, yc, x, y) 
#    while (y >= x) 
#        x=x+1 
#        if (d > 0) 
#            y=y-1  
#            d = d + 4 * (x - y) + 10 
#        else
#            d = d + 4 * x + 6 
#        draw_circle_pixels(xc, yc, x, y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of the circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color of line in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#***************************************************
draw_circle: 		nop
			# Preserve $ra and s registers
			push($ra)
			push($s0)
			push($s1)
			push($s2)
			push($s3)
			push($s4)

			# $s0: x
			# $s1: y
			# $s2: d
			# $s3: r
			# $s4: for arithmatic
			add  $s0 $0  $0				# x = 0
			add  $s1 $a1 $0				# y = radius
			add  $s2 $a1 $a1			# 2 * radius
			addi $s3 $0  3				# $s3 = 3 (temporarily)
			sub  $s2 $s3 $s2			# 3 - 2 * radius
			add  $s3 $a1 $0				# $s3 = radius
			add  $a1 $a2 $0				# move color into $a1 for draw_circle_pixels
draw:			nop
			add  $a2 $s0 $0				# move x into $a2 for draw_circle_pixels
			add  $a3 $s1 $0				# move y into $a3 for draw_circle_pixels
			jal  draw_circle_pixels		# jump and link to draw_circle_pixels
	
draw_circle_while:	nop
			blt  $s1 $s0 draw_circle_done		# while y >= x loop. when y < x branch to draw_circle_done
			nop
			addi $s0 $s0 1				# increment x
			blez $s2 draw_circle_else		# if d <= 0 jump to draw_circle_else. Otherwise continue
			nop
			subi $s1 $s1 1				# Decrement y by 1
			sub  $s4 $s0 $s1			# $s4 = x - y
			mul  $s4 $s4 4				# 4 * (x - y)
			addi $s4 $s4 10				# 4 * (x - y) + 10
			add  $s2 $s2 $s4			# d = d + 4 * (x - y) + 10
	
			j    draw				# jump to draw
	
draw_circle_else:	nop
			mul  $s4 $s0 4				# 4 * x
			addi $s4 $s4 6				# 4 * x + 6
			add  $s2 $s2 $s4			# d = d + 4 * x + 6
	
			j    draw				# jump to draw
	
	
draw_circle_done:	nop
			# Restor $ra and s registers
			pop($s4)
			pop($s3)
			pop($s2)
			pop($s1)
			pop($s0)
			pop($ra)
	
			jr   $ra
	
#*****************************************************
# draw_circle_pixels:
#  Function to draw the circle pixels 
#  using the octans' symmetry
#-----------------------------------------------------
# Psuedocode:
# draw_circle_pixels(xc, yc, x, y)  
#    draw_pixel(xc+x, yc+y) 
#    draw_pixel(xc-x, yc+y)
#    draw_pixel(xc+x, yc-y)
#    draw_pixel(xc-x, yc-y)
#    draw_pixel(xc+y, yc+x)
#    draw_pixel(xc-y, yc+x)
#    draw_pixel(xc+y, yc-x)
#    draw_pixel(xc-y, yc-x)
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#    $a2 = current x value from the Bresenham's circle algorithm
#    $a3 = current y value from the Bresenham's circle algorithm
#   Outputs:
#    No register outputs	
#*****************************************************
draw_circle_pixels: 	nop
			# Preserve $ra and s registers
			push($ra)
			push($s0)
			push($s1)
			push($s2)
			push($s3)
			push($a0)
	
			# xc:    $s0
			# yc:    $s1
			# temp:  $s2
			# temp2: $s3
			# x:     $a2
			# y:     $a3
	
			getCoordinates($a0 $s0 $s1)			# xc in $s0, yc in $s1
	
			# draw_pixel(xc+x, yc+y)
			add  $s2 $s0 $a2				# xc + x
			add  $s3 $s1 $a3				# yc + y
			formatCoordinates($a0 $s2 $s3)			# format(xc+x, yc+y)
			jal  draw_pixel
	
			# draw_pixel(xc-x, yc+y)
			sub  $s2 $s0 $a2				# xc - x
			add  $s3 $s1 $a3				# yc + y
			formatCoordinates($a0 $s2 $s3)			# format(xc-x, yc+y)
			jal  draw_pixel
	
			# draw_pixel(xc+x, yc-y)
			add  $s2 $s0 $a2				# xc + x
			sub  $s3 $s1 $a3				# yc - y
			formatCoordinates($a0 $s2 $s3)			# format(xc+x, yc-y)
			jal  draw_pixel
	
			# draw_pixel(xc-x, yc-y)
			sub  $s2 $s0 $a2				# xc - x
			sub  $s3 $s1 $a3				# yc - y
			formatCoordinates($a0 $s2 $s3)			# format(xc-x, yc-y)
			jal  draw_pixel
	
			# draw_pixel(xc+y, yc+x)
			add  $s2 $s0 $a3				# xc + y
			add  $s3 $s1 $a2				# yc + x
			formatCoordinates($a0 $s2 $s3)			# format(xc+y, yc+x)
			jal  draw_pixel
	
			# draw_pixel(xc-y, yc+x)
			sub  $s2 $s0 $a3				# xc - y
			add  $s3 $s1 $a2				# yc + x
			formatCoordinates($a0 $s2 $s3)			# format(xc-y, yc+x)
			jal  draw_pixel
	
			# draw_pixel(xc+y, yc-x)
			add  $s2 $s0 $a3				# xc + y
			sub  $s3 $s1 $a2				# yc - x
			formatCoordinates($a0 $s2 $s3)			# format(xc+y, yc-x)
			jal  draw_pixel
	
			# draw_pixel(xc-y, yc-x)
			sub  $s2 $s0 $a3				# xc - y
			sub  $s3 $s1 $a2				# yc - x
			formatCoordinates($a0 $s2 $s3)			# format(xc-y, yc-x)
			jal  draw_pixel

			pop($a0)
			pop($s3)
			pop($s2)
			pop($s1)
			pop($s0)
			pop($ra)
	
			jr   $ra
