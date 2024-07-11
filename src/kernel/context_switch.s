.section .text
.global context_switch

context_switch:
    push {r4-r11, lr}

    mov r12, r0
    ldmia r12!, {r4-r11, lr}

    bx lr
