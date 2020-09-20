# 14
# В матрице А[m][n] найти строку с максимальной суммой
# элементов и строку с минимальной суммой элементов. Далее сформировать
# вектор В[2...M], у которого чередовались бы элементы из максимальной и
# минимальной строк матрицы

	.data
out_new_line: .asciiz "\n"
out_colon: .asciiz ": "
out_space: .asciiz " "
out_test: .asciiz "test"
out_greet: .asciiz "\nHello!\n"
out_enter_cols_count: .asciiz "Enter number of columns: "
out_enter_rows_count: .asciiz "Enter number of rows: "
out_enter_arr: .asciiz "Enter array: \n"
out_enter_row: .asciiz "Row "
out_enter_elem: .asciiz "  Element: "
out_show_array: .asciiz "Array:"
out_arr_size_bytes: .asciiz "Array size in bytes: "
out_arr_size: .asciiz "Array size: "
out_arr_row_size_bytes: .asciiz "Array row size in bytes: "
out_max_row: .asciiz "Max row: "
out_min_row: .asciiz "Min row: "
out_vector: .asciiz "Vector B: "
out_err_size: .asciiz "Error! IIncorret size, should be greater than 0.\n"

elem_size: .word 4
arr_row_size_bytes: .word 0
arr_size_bytes: .word 0
arr_rows: .word 0
arr_cols: .word 0
arr_size: .word 0
arr_offset: .word 0
arr_min_row: .word 0
arr_max_row: .word 0

	.text
main:
	li $v0, 4 # 4 - sys print int
	la $a0, out_greet # arg
	syscall

	jal init_arr
	li $v0, 4
	la $a0, out_new_line
	syscall

	lw $t1, arr_size
	beqz $t1, exit

	jal print_arr
	li $v0, 4
	la $a0, out_new_line
	syscall

	jal find_max_row
	li $v0, 4
	la $a0, out_max_row
	syscall
	li $v0, 1
	lw $a0, arr_max_row
	syscall
	li $v0, 4
	la $a0, out_new_line
	syscall

	jal find_min_row
	li $v0, 4
	la $a0, out_min_row
	syscall
	li $v0, 1
	lw $a0, arr_min_row
	syscall
	li $v0, 4
	la $a0, out_new_line
	syscall

	li $v0, 4
	la $a0, out_vector
	syscall
	jal mix

	li $v0, 10
	syscall

exit:
	li $v0, 10
	syscall

init_arr:
	li $v0, 4 # 4 - sys print int
	la $a0, out_enter_arr # arg
	syscall
	li $v0, 4 # 4 - sys print int
	la $a0, out_enter_cols_count # arg
	syscall
	li $v0, 5
	syscall
	sw $v0, arr_cols

	li $v0, 4
	la $a0, out_enter_rows_count
	syscall
	li $v0, 5
	syscall
	sw $v0, arr_rows

	lw $t0, elem_size
	lw $t1, arr_cols
	lw $t2, arr_rows
	mul $t3, $t0, $t1
	sw $t3, arr_row_size_bytes
	mul $t4, $t2, $t3
	sw $t4, arr_size_bytes
	mul $t5, $t1, $t2
	sw $t5, arr_size

	li $v0, 9 #9 - memory allocation
	lw $a0, arr_size_bytes
	syscall
	move $s7, $v0
	
	li $t0, 0
	lw $t1, arr_size
	beq $t0, $t1, end_init_arr
	li $t0, 0
	li $t7, 0
	lw $t2, arr_size
	move $s6, $s7

	li $t1, 0 # t1 - elem counter
	li $t2, 0 # t2 - row counter
	lw $t3, arr_cols # t3 - row size
	lw $t4, arr_rows # t4 - row count

enter_row:
	beq $t2, $t4, end_init_arr

	addi $t2, $t2, 1
	addi $t1, $zero, 0

	li $v0, 4
	la $a0, out_enter_row
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	li $v0, 4
	la $a0, out_new_line
	syscall

enter_elem:
	li $v0, 4
	la $a0, out_enter_elem
	syscall
	
	li $v0, 5
	syscall
	
	add $s7, $s7, $t7
	sw $v0, 0($s7)
	lw $t7, elem_size

	addi $t1, $t1, 1
	bne $t1, $t3, enter_elem
	addi $t0, $t0, 1
	j enter_row

end_init_arr:
	move $s7, $s6
	jr $ra

print_arr:
	li $t0, 0 # counter

	li $t1, 0 # t1 - elem counter
	li $t2, 0 # t2 - row counter
	lw $t3, arr_cols # t3 - row size
	lw $t4, arr_rows # t4 - row count

	lw $t7, arr_offset
	move $s6, $s7

	li $v0, 4
	la $a0, out_show_array
	syscall

print_row:
	li $v0, 4
	la $a0, out_new_line
	syscall

	beq $t2, $t4, end_print

	addi $t2, $t2, 1
	addi $t1, $zero, 0

print_elem:
	addi $t1, $t1, 1

	add $s7, $s7, $t7
	lw $t7, elem_size

	li $v0, 1
	lw $a0, 0($s7)
	syscall

	li $v0, 4
	la $a0, out_space
	syscall

	beq $t1, $t3, print_row

	j print_elem

end_print:
	move $s7, $s6
	jr $ra

find_max_row:
	li $t0, 0 # counter
	li $t1, 0 # t1 - elem counter
	li $t2, 0 # t2 - row counter
	lw $t3, arr_cols # t3 - row size
	lw $t4, arr_rows # t4 - row count
	li $t5, 0 # t5 - sum counter
	li $t6, 0 # t6 - max for
	lw $t7, arr_offset

	move $s6, $s7

find_max_loop:
	bgt $t5, $t6, change_max # t5 > t6 then
	beq $t2, $t4, end_find

	addi $t2, $t2, 1
	addi $t1, $zero, 0
	addi $t5, $zero, 0 # re sum counter

find_max_loop2:
	addi $t1, $t1, 1

	add $s7, $s7, $t7
	lw $t7, elem_size

	lw $s1, 0($s7)
	add $t5, $t5, $s1

	beq $t1, $t3, find_max_loop

	j find_max_loop2

change_max:
	sub $t2, $t2, 1
	sw $t2, arr_max_row
	addi $t2, $t2, 1
	move $t6, $t5
	li $t5, 0
	j find_max_loop

find_min_row:
	li $t0, 0 # counter
	li $t1, 0 # t1 - elem counter
	li $t2, 0 # t2 - row counter
	lw $t3, arr_cols # t3 - row size
	lw $t4, arr_rows # t4 - row count
	li $t5, 1000 # t5 - sum counter
	li $t6, 1000 # t6 - min
	lw $t7, arr_offset

	move $s6, $s7

find_min_loop:
	blt $t5, $t6, change_min # if t5 < t6 goto change_min
	beq $t2, $t4, end_find # if t2 = t4 goto end

	addi $t2, $t2, 1 # inc row counter
	addi $t1, $zero, 0 # re elem counter
	addi $t5, $zero, 0 # re sum counter

find_min_loop2:
	addi $t1, $t1, 1 # inc elem counter

	add $s7, $s7, $t7 # change offset
	lw $t7, elem_size # loading elem size

	lw $s1, 0($s7) # elem
	add $t5, $t5, $s1 # inc sum counter by elem

	beq $t1, $t3, find_min_loop # if t1 = t3 goto find_min_loop

	j find_min_loop2

change_min:
	sub $t2, $t2, 1 # row counter - 1
	sw $t2, arr_min_row # store row counter
	addi $t2, $t2, 1 # row counter + 1
	move $t6, $t5 # min = sum
	j find_min_loop

end_find:
	move $s7, $s6
	jr $ra

mix:
	lw $t1, arr_row_size_bytes # t1 - arr row size bytes
	lw $t2, arr_max_row # 
	mul $t3, $t1, $t2 # t3 - relative offset of max
	lw $t2, arr_min_row #
	mul $t4, $t1, $t2 # t4 - relative offset of min
	lw $t5, arr_cols # size of row
	li $t0, 0 # counter
	li $t7, 0

	move $s4, $s7
	# lw $t7, arr_offset

	add $s5, $s7, $t3 # s5 - abs offset for max
	add $s6, $s7, $t4 # s6 - abs offset for min

mix_odd:
	add $s5, $s5, $t7

	li $v0, 1
	lw $a0, 0($s5)
	syscall

	li $v0, 4
	la $a0, out_space
	syscall


	beq $t0, $t5, end_mix

	j mix_even

mix_even:
	add $s6, $s6, $t7
	lw $t7, elem_size

	li $v0, 1
	lw $a0, 0($s6)
	syscall

	li $v0, 4
	la $a0, out_space
	syscall

	addi $t0, $t0, 1
	beq $t0, $t5, end_mix

	j mix_odd

end_mix:
	li $v0, 4
	la $a0, out_new_line
	syscall

	move $s7, $s4
	jr $ra