
.extern idx_of

.global r_to_l_path
.type r_to_l_path, @function

r_to_l_path:
       pushq   %rbp
        movq    %rsp, %rbp
        subq    $48, %rsp
        movl    %edi, %eax
        movl    %esi, -24(%rbp)
        movq    %rdx, -32(%rbp)
        movq    %rcx, -40(%rbp)
        movq    %r8, -48(%rbp)
        movb    %al, -20(%rbp)
        movl    -24(%rbp), %eax
        cltq
        leaq    0(,%rax,8), %rdx
        movq    -32(%rbp), %rax
        addq    %rdx, %rax
        movq    (%rax), %rax
        movq    %rax, -8(%rbp)
        movl    -24(%rbp), %eax
        cltq
        leaq    0(,%rax,4), %rdx
        movq    -40(%rbp), %rax
        addq    %rdx, %rax
        movl    (%rax), %eax
        movslq  %eax, %rdx
        movq    -8(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movsbl  %al, %eax
        movq    -48(%rbp), %rdx
        movq    %rdx, %rsi
        movl    %eax, %edi
        call    idx_of
        movl    %eax, -12(%rbp)
        movsbl  -20(%rbp), %eax
        movq    -48(%rbp), %rdx
        movq    %rdx, %rsi
        movl    %eax, %edi
        call    idx_of
        movl    -12(%rbp), %edx
        addl    %eax, %edx
        movslq  %edx, %rax
        imulq   $1991868891, %rax, %rax
        shrq    $32, %rax
        sarl    $5, %eax
        movl    %edx, %ecx
        sarl    $31, %ecx
        subl    %ecx, %eax
        imull   $69, %eax, %ecx
        movl    %edx, %eax
        subl    %ecx, %eax
        movslq  %eax, %rdx
        movq    -8(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movsbl  %al, %eax
        movq    -48(%rbp), %rdx
        movq    %rdx, %rsi
        movl    %eax, %edi
        call    idx_of
        subl    -12(%rbp), %eax
        movslq  %eax, %rdx
        imulq   $1991868891, %rdx, %rdx
        shrq    $32, %rdx
        sarl    $5, %edx
        movl    %eax, %ecx
        sarl    $31, %ecx
        subl    %ecx, %edx
        imull   $69, %edx, %ecx
        subl    %ecx, %eax
        movl    %eax, %edx
        movslq  %edx, %rdx
        movq    -48(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        leave
        ret

.global l_to_r_path
.type l_to_r_path, @function

l_to_r_path:
         pushq   %rbp
        movq    %rsp, %rbp
        subq    $64, %rsp
        movl    %edi, %eax
        movl    %esi, -40(%rbp)
        movq    %rdx, -48(%rbp)
        movq    %rcx, -56(%rbp)
        movq    %r8, -64(%rbp)
        movb    %al, -36(%rbp)
        movl    -40(%rbp), %eax
        cltq
        leaq    0(,%rax,8), %rdx
        movq    -48(%rbp), %rax
        addq    %rdx, %rax
        movq    (%rax), %rax
        movq    %rax, -16(%rbp)
        movl    -40(%rbp), %eax
        cltq
        leaq    0(,%rax,4), %rdx
        movq    -56(%rbp), %rax
        addq    %rdx, %rax
        movl    (%rax), %eax
        movslq  %eax, %rdx
        movq    -16(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movsbl  %al, %eax
        movq    -64(%rbp), %rdx
        movq    %rdx, %rsi
        movl    %eax, %edi
        call    idx_of
        movl    %eax, -20(%rbp)
        movsbl  -36(%rbp), %eax
        movq    -64(%rbp), %rdx
        movq    %rdx, %rsi
        movl    %eax, %edi
        call    idx_of
        movl    -20(%rbp), %edx
        addl    %eax, %edx
        movslq  %edx, %rax
        imulq   $1991868891, %rax, %rax
        shrq    $32, %rax
        sarl    $5, %eax
        movl    %edx, %ecx
        sarl    $31, %ecx
        subl    %ecx, %eax
        imull   $69, %eax, %ecx
        movl    %edx, %eax
        subl    %ecx, %eax
        movslq  %eax, %rdx
        movq    -64(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movsbl  %al, %eax
        movl    %eax, -24(%rbp)
        movl    $0, -4(%rbp)
        jmp     .loop
.loop_inc:
        addl    $1, -4(%rbp)
.loop:
        cmpl    $68, -4(%rbp)
        jg      .loop
        movl    -4(%rbp), %eax
        movslq  %eax, %rdx
        movq    -16(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movsbl  %al, %eax
        cmpl    %eax, -24(%rbp)
        jne     .loop_inc
.end:
        movl    -4(%rbp), %eax
        subl    -20(%rbp), %eax
        movslq  %eax, %rdx
        imulq   $1991868891, %rdx, %rdx
        shrq    $32, %rdx
        sarl    $5, %edx
        movl    %eax, %ecx
        sarl    $31, %ecx
        subl    %ecx, %edx
        imull   $69, %edx, %ecx
        subl    %ecx, %eax
        movl    %eax, %edx
        movslq  %edx, %rdx
        movq    -64(%rbp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        leave
        ret
