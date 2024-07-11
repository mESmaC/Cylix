.section .text
.global _start

_start:
    ldr sp, =_stack_top

    bl init_sections

    bl main

    b .

init_sections:
    ldr r0, =_data_start
    ldr r1, =_data_end
    ldr r2, =_data_load

copy_data:
    cmp r0, r1
    beq init_bss
    ldr r3, [r2], #4
    str r3, [r0], #4
    b copy_data

init_bss:
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0

zero_bss:
    cmp r0, r1
    beq done
    str r2, [r0], #4
    b zero_bss

done:
    bx lr

.section .bss
.align 4
_stack_bottom:
.skip 16384 
_stack_top:
