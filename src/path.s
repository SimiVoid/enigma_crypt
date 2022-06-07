
.extern idx_of

.global r_to_l_path
.type r_to_l_path, @function

r_to_l_path:
        pushq   %r13
        pushq   %r12
        pushq   %rbp
        pushq   %rbx
        movl    %edi, %r13d
        movq    %r8, %rbx
        movslq  %esi, %rsi
        movq    (%rdx,%rsi,8), %r12
        movslq  (%rcx,%rsi,4), %rax ; calculate offset
        movsbl  (%r12,%rax), %edi
        movq    %r8, %rsi
        call    idx_of
        movl    %eax, %ebp
        movsbl  %r13b, %edi ; get returned value from alphabet
        movq    %rbx, %rsi
        call    idx_of
        addl    %ebp, %eax
        movslq  %eax, %rdx
        imulq   $1991868891, %rdx, %rdx
        sarq    $37, %rdx
        movl    %eax, %ecx
        sarl    $31, %ecx
        subl    %ecx, %edx
        imull   $69, %edx, %edx
        subl    %edx, %eax
        cltq
        movsbl  (%r12,%rax), %edi
        movq    %rbx, %rsi
        call    idx_of
        subl    %ebp, %eax
        movslq  %eax, %rdx
        imulq   $1991868891, %rdx, %rdx
        sarq    $37, %rdx
        movl    %eax, %ecx
        sarl    $31, %ecx
        subl    %ecx, %edx
        imull   $69, %edx, %edx
        subl    %edx, %eax
        cltq
        movzbl  (%rbx,%rax), %eax
        popq    %rbx
        popq    %rbp
        popq    %r12
        popq    %r13
        ret

.global l_to_r_path
.type l_to_r_path, @function

l_to_r_path:
        pushq   %r13
        pushq   %r12
        pushq   %rbp
        pushq   %rbx
        movl    %edi, %r13d
        movq    %r8, %rbx
        movslq  %esi, %rsi
        movq    (%rdx,%rsi,8), %rbp
        movslq  (%rcx,%rsi,4), %rax ; calculate offset
        movsbl  0(%rbp,%rax), %edi
        movq    %r8, %rsi
        call    idx_of
        movl    %eax, %r12d
        movsbl  %r13b, %edi ; get new char from alphabet
        movq    %rbx, %rsi
        call    idx_of
        addl    %r12d, %eax
        movslq  %eax, %rdx
        imulq   $1991868891, %rdx, %rdx
        sarq    $37, %rdx
        movl    %eax, %ecx
        sarl    $31, %ecx
        subl    %ecx, %edx
        imull   $69, %edx, %edx
        subl    %edx, %eax
        cltq
        movzbl  (%rbx,%rax), %ecx
        movq    %rbp, %rdx
        movl    $0, %eax
.loop: ; while loop
        cmpb    (%rdx), %cl
        je      .end
        addl    $1, %eax
        addq    $1, %rdx
        cmpl    $69, %eax
        jne     .loop
.end:
        subl    %r12d, %eax
        movslq  %eax, %rdx
        imulq   $1991868891, %rdx, %rdx
        sarq    $37, %rdx
        movl    %eax, %ecx
        sarl    $31, %ecx
        subl    %ecx, %edx
        imull   $69, %edx, %edx
        subl    %edx, %eax
        cltq
        movzbl  (%rbx,%rax), %eax
        popq    %rbx
        popq    %rbp
        popq    %r12
        popq    %r13
        ret
