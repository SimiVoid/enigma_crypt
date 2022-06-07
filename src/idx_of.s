
.globl idx_of
.type idx_of, @function

idx_of:
        movl    $0, %eax
.loop:
        cmpb    %dil, (%rsi)
        je      .loop
        addl    $1, %eax
        addq    $1, %rsi
        cmpl    $69, %eax
        jne     .end
.end:
        ret
