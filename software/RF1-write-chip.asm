F43B  31 FF F7  lxi     sp,$F7FF
F43E  06 10     mvi     b,$10
F440  3E 82     mvi     a,$82
F442  D3 80     out     $80
F444  3E 60     mvi     a,'`'
F446  D3 81     out     $81
F448  21 00 F4  lxi     h,$F400
F44B  11 00 04  lxi     d,$0400
F44E  2B        dcx     h
F44F  1B        dcx     d
F450  7B        mov     a,e
F451  D3 83     out     $83
F453  7A        mov     a,d
F454  F6 60     ori     '`'
F456  D3 81     out     $81
F458  DB 82     in      $82
F45A  BE        cmp     m
F45B  3E 81     mvi     a,$81
F45D  C2 69 F4  jnz     $F469
F460  7A        mov     a,d
F461  B3        ora     e
F462  C2 4E F4  jnz     $F44E
F465  06 01     mvi     b,$01
F467  3E 0F     mvi     a,$0F
F469  F5        push    psw
F46A  0E 0C     mvi     c,$0C
F46C  3E A0     mvi     a,$A0
F46E  D3 81     out     $81
F470  3E 80     mvi     a,$80
F472  D3 80     out     $80
F474  21 00 F4  lxi     h,$F400
F477  11 00 04  lxi     d,$0400
F47A  2B        dcx     h
F47B  1B        dcx     d
F47C  7B        mov     a,e
F47D  D3 83     out     $83
F47F  7A        mov     a,d
F480  F6 A0     ori     $A0
F482  D3 81     out     $81
F484  7E        mov     a,m
F485  D3 82     out     $82
F487  7A        mov     a,d
F488  F6 90     ori     $90
F48A  D3 81     out     $81
F48C  3E 10     mvi     a,$10
F48E  3D        dcr     a
F48F  C2 8E F4  jnz     $F48E
F492  7A        mov     a,d
F493  F6 A0     ori     $A0
F495  D3 81     out     $81
F497  7A        mov     a,d
F498  B3        ora     e
F499  C2 7A F4  jnz     $F47A
F49C  0D        dcr     c
F49D  C2 74 F4  jnz     $F474
F4A0  F1        pop     psw
F4A1  05        dcr     b
F4A2  C2 40 F4  jnz     $F440
F4A5  D3 00     out     $00
F4A7  76        hlt
