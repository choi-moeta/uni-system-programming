# 14
# В матрице А[m][n] найти строку с максимальной суммой
# элементов и строку с минимальной суммой элементов. Далее сформировать
# вектор В[2...M], у которого чередовались бы элементы из максимальной и
# минимальной строк матрицы

	.data
# Output strings
out_new_line: .string "\n"
out_space: .string "%d  "
scanf_format: .string "%d"
out_enter_size_cols: .string "Enter number of columns: "
out_enter_size_rows: .string "Enter number of rows: "
out_enter_num: .string "  Element: "
out_show_array: .string "Array:\n"
out_enter_row: .string "Row %d\n"
out_array_max_row_format: .string "Max row: %d\n"
out_array_min_row_format: .string "Min row: %d\n"
out_vec: .string "Vector B: "

err_size: .string "Error! Incorret size, should be greater than 0.\n"

array_row_size_bytes: .space 4
array_size_bytes: .space 4
array_size: .space 4
array_cols: .space 4
array_rows: .space 4
array_elem: .space 4
array_min_row: .space 4
array_min_row_temp: .space 4
array_min_row_index: .space 4
array_max_row: .space 4
array_max_row_temp: .space 4
array_max_row_index: .space 4
array_start_point: .space 4

.equ elem_size, 4 
.equ elem_max_size, 999

.text
init_array:
	pushl %ebp
	movl %esp, %ebp # save pointer

	pushl $out_enter_size_cols
	call printf
	addl $4, %esp # выравнивание стека 
	
	pushl $array_cols # read number of cols
	pushl $scanf_format
	call scanf
	addl $8, %esp

	pushl $out_enter_size_rows
	call printf
	addl $4, %esp

	pushl $array_rows # read number of rows
	pushl $scanf_format
	call scanf
	addl $8, %esp
	
	# calculate additional data
	movl $elem_size, %eax
	mull array_cols
	movl %eax, array_row_size_bytes
	mull array_rows
	movl %eax, array_size_bytes

	# check for inccorect input
	cmpl $0, array_cols
	je error_size
	cmpl $0, array_rows
	je error_size

	# memory allocation
	pushl array_size_bytes
	call malloc
	addl $4, %esp
	movl %eax, %esi # save into register
	movl %eax, array_start_point # save start point

	movl $0, %edi # row counter

enter_line:
	movl $0, %ebx # column(elem) counter

	cmpl array_rows, %edi
	je end_init

	incl %edi
	pushl %edi
	pushl $out_enter_row
	call printf
	decl %edi
	addl $8, %esp

enter_element:
	pushl $out_enter_num
	call printf
	addl $4, %esp

	pushl $array_elem
	pushl $scanf_format
	call scanf
	addl $8, %esp

	movl array_row_size_bytes, %eax
	mull %edi
	movl %eax, %ecx
	movl $elem_size, %eax
	mull %ebx
	addl %eax, %ecx
	movl array_elem, %eax
	movl %eax, (%esi, %ecx)
	incl %ebx

	cmpl %ebx, array_cols
	jne enter_element
	incl %edi

	jmp enter_line

end_init:
	movl %ebp, %esp # restore pointer
	popl %ebp
	ret

error_size:
	pushl $error_size
	call printf
	addl $4, %esp
	ret

print_array:
	movl $0, %ebx
	movl $0, %edi
	movl array_start_point, %esi

print_line:
	cmpl %edi, array_rows
	je print_array_end

	cmpl %ebx, array_cols
	je print_line_end

	pushl (%esi)
	pushl $out_space
	addl $4, %esi
	call printf
	addl $8, %esp

	incl %ebx
	jmp print_line

print_line_end:
	pushl $out_new_line
	call printf
	addl $4, %esp
	incl %edi
	movl $0, %ebx
	jmp print_line

print_array_end:
	ret

process_array:
	movl $0, %ebx # counter cols
	movl $0, %edi # counter rows
	movl array_start_point, %esi # item adr

	movl $0, array_min_row_temp
	movl $elem_max_size, array_min_row
	movl $0, array_max_row_temp
	movl $0, array_max_row

process_line:
	cmpl %edi, array_rows
	je process_array_end

	cmpl %ebx, array_cols
	je procces_line_end_comp

	movl (%esi), %eax
	addl %eax, array_min_row_temp
	addl %eax, array_max_row_temp

	addl $4, %esi
	incl %ebx
	jmp process_line

procces_line_end_comp:
	movl array_max_row_temp, %eax

	cmpl %eax, array_min_row
	jge process_min

	cmpl %eax, array_max_row
	jle process_max

	jmp process_line_end

process_min:
	movl array_min_row_temp, %eax
	movl %eax, array_min_row
	movl %edi, array_min_row_index

	jmp process_line_end

process_max:
	movl array_max_row_temp, %eax
	movl %eax, array_max_row
	movl %edi, array_max_row_index

process_line_end:
	movl $0, array_min_row_temp
	movl $0, array_max_row_temp

	incl %edi
	movl $0, %ebx
	jmp process_line

process_array_end:
	ret

print_vec:
	movl $0, %ebx
	movl $0, %edi
	movl array_start_point, %esi

	movl $0, %eax
	addl $elem_size, %eax
	mull array_cols
	mull array_min_row_index
	movl %eax, array_min_row_temp

	movl $0, %eax
	addl $elem_size, %eax
	mull array_cols
	mull array_max_row_index
	movl %eax, array_max_row_temp

	pushl $out_vec
	call printf
	addl $4, %esp

print_vec_line:
	cmpl %ebx, array_cols
	je print_vec_end

	addl array_min_row_temp, %esi

	pushl (%esi)
	pushl $out_space
	call printf
	addl $8, %esp

	subl array_min_row_temp, %esi

	addl array_max_row_temp, %esi

	pushl (%esi)
	pushl $out_space
	call printf
	addl $8, %esp

	subl array_max_row_temp, %esi

	addl $4, %esi

	incl %ebx
	jmp print_vec_line

print_vec_end:
	pushl $out_new_line
	call printf
	addl $4, %esp
	ret

.globl main
main:
	call init_array

	movl $0, %eax
	cmpl %eax, array_cols
	je end
	jng end

	pushl $out_show_array
	call printf
	addl $4, %esp
	call print_array

	call process_array
	movl array_min_row_index, %eax
	addl $1, %eax
	pushl %eax
	pushl $out_array_min_row_format
	call printf
	addl $8, %esp

	movl array_max_row_index, %eax
	addl $1, %eax
	pushl %eax
	pushl $out_array_max_row_format
	call printf
	addl $8, %esp

	call print_vec
end:
	ret