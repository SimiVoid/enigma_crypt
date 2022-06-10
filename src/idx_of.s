
.global idx_of
.type idx_of, @function

idx_of:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, %eax
        movq    %rsi, -32(%rbp)
        movb    %al, -20(%rbp)
        movl    $0, -4(%rbp)
        movl    $69, -8(%rbp)
        jmp     .loop
.loop_inc:
        addl    $1, -4(%rbp)
.loop:
        cmpl    $68, -4(%rbp)
        jg      .end
        movl    -4(%rbp), %eax
        movslq  %eax, %rdx
        movq    -32(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        cmpb    %al, -20(%rbp)
        jne     .loop_inc
.end:
        movl    -4(%rbp), %eax
        popq    %rbp
        ret
