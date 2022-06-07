
.global idx_of
.type idx_of, @function

idx_of:
        movl    $0, %eax
.loop:
        cmpb    %dil, (%rsi)
        je      .end
        addl    $1, %eax
        addq    $1, %rsi
        cmpl    $69, %eax
        jne     .loop
.end:
        ret
