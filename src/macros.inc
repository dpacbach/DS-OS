;=============================================================================
; MACROS FOR DS-OS
;=============================================================================

MOVZX   macro                           ; ex: MOVZX ax,bl
        pushf                           ;     MOVZX es,b[xxxx]
        push    ax                      ;     MOVZX w[xxxx],dh
        xor     ah,ah                   ;     MOVZX w[xxxx],b[xxxx]
        mov     al,#2
        mov     cs:[$+12],ax
        pop     ax
        push    cs:[$+7]
        jmp     short $+4
        nop
        nop
        pop     #1
        popf
        #em

;=============================================================================

MOVSX   macro                           ; ex: MOVSX ax,bl
        pushf                           ;     MOVSX es,b[xxxx]
        push    ax                      ;     MOVSX w[xxxx],dh
        mov     al,#2                   ;     MOVSX w[xxxx],b[xxxx]
        cbw
        mov     cs:[$+12],ax
        pop     ax
        push    cs:[$+7]
        jmp     short $+4
        nop
        nop
        pop     #1
        popf
        #em

;=============================================================================

MOVSX32 macro                           ; ex: MOVSX32 dx,ax,bx
        pushf                           ;     MOVSX32 cx,bx,w[xxxx]
        push    dx                      ;     MOVSX32 w[xxxx],dx,w[xxxx]
        push    ax                      ;     MOVSX32 w[xxxx],w[xxxx],w[xxxx]
        mov     ax,#3                   ;
        cwd                             ; will move #3 into #1:#2 while
        mov     cs:[$+23],ax            ; extending the sign
        mov     cs:[$+21],dx
        pop     ax
        pop     dx
        push    cs:[$+14]
        push    cs:[$+7]
        jmp     short $+6
        nop
        nop
        nop
        nop
        pop     #2
        pop     #1
        popf
        #em

;=============================================================================

BITMB   macro                           ; ex: BITMB shr,al,5
        xchg    al,#2                   ;     BITMB rol,ch,7
        push    cx                      ;     BITMB shr,bl,b[xxxx]
        mov     cl,#3                   ;     BITMB shl,b[xxxx],dh
        #1      al,cl                   ;     BITMB ror,b[xxxx],b[xxxx]
        pop     cx
        xchg    al,#2
        #em

;=============================================================================

BITMW   macro                           ; ex: same as above except with WORDs
        xchg    ax,#2
        push    cx
        mov     cl,#3
        #1      ax,cl
        pop     cx
        xchg    ax,#2
        #em

;=============================================================================

PUSH_A  macro
        db      50h,51h,52h,53h
        db      54h,55h,56h,57h
        #em

;=============================================================================

POP_A   macro
        db      5fh,5eh,5dh,5bh
        db      5bh,5ah,59h,58h         ; POP SP removed for 8086
        #em

;=============================================================================

PUSH_XX macro                           ; ex: PUSH_XX ax
        push    ax                      ;     PUSH_XX es
        mov     ax,#1                   ;     PUSH_XX w[xxxx]
        mov     cs:[$+12],ax            ;     PUSH_XX 50
        pop     ax
        push    cs:[$+7]
        jmp     short $+4
        nop
        nop
        #em

;=============================================================================

JCXNZ   macro                           ;ex: mov     cx,ax
        pushf                           ;    JCXNZ   L1
        or      cx,cx                   ;    ...
        jz      $+6                     ;L1:
        popf                            ;    ...
        jmp     #1
        popf
        #em

;=============================================================================

DIV16   macro                           ; will divide #1:#2 by #3.  Quotient
                                        ; will be placed in #1:#2 and
                                        ; remainder in #3.  All params must
                                        ; be words.  They can be registers,
                                        ; (seg regs too), memory, but not
                                        ; constants.  The registers can be
                                        ; anything except SP.  No other
                                        ; registers will be modified.  Will
                                        ; not modify any flags.  There will
                                        ; never be an overflow no matter what
                                        ; the numbers are.
        DIV32_i #1,#2,#3,#1,#2,#3
        #em

;=============================================================================

DIV16_i macro                           ; #1:#2 will be divided by #3.
                                        ; Quotient will be placed in #4:#5,
                                        ; with remainder in #6. All params
                                        ; must be words(registers or memory,
                                        ; can also be segment regs) regs can
                                        ; be anything except SP.  #1,#2,#3
                                        ; can be constans. No other registers
                                        ; will be modified.  Will not modify
                                        ; any flags.  There will never be an
                                        ; overflow no matter what the numbers
                                        ; are.
        pushf
        cli
        PUSH_A
        PUSH_XX #1
        PUSH_XX #2
        PUSH_XX #3
        pop     di
        pop     ax
        pop     dx
        call    div32_16
        push    cx
        push    bx
        push    si
        add     sp,6
        POP_A
        sub     sp,22
        pop     #6
        pop     #5
        pop     #4
        add     sp,16
        popf
        #em

;=============================================================================
