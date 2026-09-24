%include "io64.inc"

section .bss
arr: resd 100

section .text
global main

main:
push rbp
mov rbp, rsp
sub rsp, 16

GET_DEC 4, eax
mov [rbp - 4], eax ; _size
mov dword[rbp - 8], 0 ;left 
cmp eax, 100
jle .greater_max
mov dword [rbp - 4], 100
.greater_max:
cmp eax, 0
jge .less_zero
mov dword [rbp-4], 0
.less_zero:
mov eax, [rbp - 4]
cmp eax, 0
je .stop_printing ;не забыть добавить
sub eax, 1
mov dword[rbp - 12], eax ; right
mov rbx, 0
.writing:
cmp ebx, [rbp - 4]
jge .stop_writing
GET_DEC 4, ecx
lea rdx, [arr]
mov [rdx+rbx*4], ecx
add rbx, 1
jmp .writing
.stop_writing:


mov r8, 0 ;i
mov r9, 0 ;j
mov r10, 1 ; swapped
mov r11d, 0 ; temp
mov r12d, [rbp - 8] ; left
mov r13d, [rbp - 12] ; right
mov r14d, 0; i+1 item
.start_cycle:
cmp r12, r13
jge .stop_sorting
cmp r10, 0
je .stop_sorting
mov r10, 0
mov r8, r12
.first_circle:
cmp r8, r13
jge .end_first_circle
mov r14d, [arr + r8*4 + 4]
cmp r14d, [arr + r8*4]
jge .skip_switching1
mov r11d, [arr + r8*4]
mov [arr + r8*4], r14d
mov [arr + r8*4 + 4], r11d
mov r10, 1
.skip_switching1:
add r8, 1
jmp .first_circle
.end_first_circle:
sub r13d, 1
cmp r10, 0
je .stop_sorting
mov r9d, r13d
mov r10, 0

.second_circle:
cmp r9, r12
jle .end_second_circle
mov r14d, [arr + r9*4 - 4]
cmp r14d, [arr + r9*4]
jle .skip_switching2
mov r11d, [arr + r9*4]
mov [arr + r9*4], r14d
mov [arr + r9*4 - 4], r11d
mov r10, 1
.skip_switching2:
sub r9, 1
jmp .second_circle
.end_second_circle:
add r12d, 1
cmp r10, 0
je .stop_sorting
jmp .start_cycle
.stop_sorting:

mov rbx, 0
.printing:
cmp ebx, [rbp - 4]
jge .stop_printing
lea rdx, [arr]
mov ecx, [rdx+rbx*4]
PRINT_DEC 4, ecx
PRINT_CHAR ' '
add rbx, 1
jmp .printing
.stop_printing:

mov rsp, rbp
pop rbp
ret
