
WFDis v1.4 Interactive 6502 Disassembler

Human Mode @Version 2024-04-19 Changelog

This standalone version disassembles binary code for the 6502 processor and variants.

All processing is client-side JavaScript. The analyzed file is not uploaded to the server.
Requires a modern HTML5/ES6 browser (tested in Firefox and Chromium).

CPU model:
Select a file to disassemble (formats):

Help

Click to open/close these side tabs

Full docs are here, sample video here

Click and use cursor keys & shift to select bytes in the disassembly

ShiftA = spawn assembly trace at selected address

G = go to address
ShiftL = define/rename label
; = edit comment
ShiftB = toggle blank line above
[] = adjust indentation

B = display selection as bytes
W = display selection as 16-bit words
ShiftW = display selection as 16-bit addresses
T = display selection as PETSCII text
U = display selection as unknown
C = display selection as font characters
S = display selection as 64-byte sprites (63 bytes + 1 pad byte)
ShiftS = display selection as 63-byte sprites
M = toggle multicolor for character/sprite line

ShiftC = create byte at address being pointed to
Del = delete selected Unknown bytes from listing

ShiftR = run selected code range, for relocation/decompression

CtrlZ = undo
CtrlY = redo

Scroll Lock = toggle smooth scrolling when navigating

ShiftI = Import labels file into current overlay

CtrlShiftS = save to browser storage
CtrlShiftZ = revert to last save
ShiftD = download snapshot


Saves

007

Lc000               jmp Lc52b

Lc003               nop
Lc004               nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    nop
                    lda #$24
                    cmp $c5
                    beq Lc020
                    bne Lc023
Lc020               jsr Sc1e4
Lc023               lda #$0c
                    cmp $c5
                    beq Lc02b
                    bne Lc02e
Lc02b               jsr Sc20a
Lc02e               lda #$3c
                    cmp $c5
                    beq Lc036
                    bne Lc039
Lc036               jsr Sc568
Lc039               lda #$2c
                    cmp $c5
                    beq Lc041
                    bne Lc044
Lc041               jsr Sc59e
Lc044               lda #$2f
                    cmp $c5
                    beq Lc04c
                    bne Lc04f
Lc04c               jsr Sc5d5
Lc04f               nop
                    nop
                    nop
                    lda #$05
                    cmp $cff9
                    beq Lc05b
                    bne Lc05e
Lc05b               jsr Sc230
Lc05e               lda #$01
                    cmp $cff9
                    beq Lc067
                    bne Lc06a
Lc067               jsr Sc254
Lc06a               lda #$02
                    cmp $cff9
                    beq Lc073
                    bne Lc076
Lc073               jsr Sc278
Lc076               lda #$03
                    cmp $cff9
                    beq Lc07f
                    bne Lc082
Lc07f               jsr Sc295
Lc082               lda #$04
                    cmp $cff9
                    beq Lc08b
                    bne Lc08e
Lc08b               jsr Sc2b7
Lc08e               nop
                    nop
                    nop
                    lda #$01
                    cmp $cffa
                    beq Lc09a
                    bne Lc09d
Lc09a               jsr Sc2e0
Lc09d               lda #$02
                    cmp $cffa
                    beq Lc0a6
                    bne Lc0a9
Lc0a6               jsr Sc309
Lc0a9               lda #$03
                    cmp $cffa
                    beq Lc0b2
                    bne Lc0b5
Lc0b2               jsr Sc32c
Lc0b5               lda #$04
                    cmp $cffa
                    beq Lc0be
                    bne Lc0c1
Lc0be               jsr Sc349
Lc0c1               lda #$05
                    cmp $cffa
                    beq Lc0ca
                    bne Lc0cd
Lc0ca               jsr Sc36c
Lc0cd               nop
                    nop
                    nop
                    lda #$01
                    cmp $cffb
                    beq Lc0d9
                    bne Lc0dc
Lc0d9               jsr Sc390
Lc0dc               lda #$02
                    cmp $cffb
                    beq Lc0e5
                    bne Lc0e8
Lc0e5               jsr Sc3b4
Lc0e8               lda #$03
                    cmp $cffb
                    beq Lc0f1
                    bne Lc0f4
Lc0f1               jsr Sc3d7
Lc0f4               lda #$04
                    cmp $cffb
                    beq Lc0fd
                    bne Lc100
Lc0fd               jsr Sc3f4
Lc100               lda #$05
                    cmp $cffb
                    beq Lc109
                    bne Lc10c
Lc109               jsr Sc417
Lc10c               jsr Sc536
                    lda #$01
                    cmp $cffc
                    beq Lc118
                    bne Lc11b
Lc118               jsr Sc43b
Lc11b               lda #$02
                    cmp $cffc
                    beq Lc124
                    bne Lc127
Lc124               jsr Sc45f
Lc127               lda #$03
                    cmp $cffc
                    beq Lc130
                    bne Lc133
Lc130               jsr Sc482
Lc133               lda #$04
                    cmp $cffc
                    beq Lc13c
                    bne Lc13f
Lc13c               jsr Sc49f
Lc13f               lda #$05
                    cmp $cffc
                    beq Lc148
                    bne Lc14b
Lc148               jsr Sc4c2
Lc14b               lda #$05
                    cmp $cffc
                    beq Lc154
                    bne Lc157
Lc154               rts

Lc155               nop
                    nop
Lc157               nop
                    nop
                    nop
                    lda #$01
                    cmp $cffd
                    beq Lc163
                    bne Lc166
Lc163               jsr Sc4e6
Lc166               lda #$02
                    cmp $cffd
                    beq Lc16f
                    bne Lc172
Lc16f               jsr Sc4f2
Lc172               lda #$03
                    cmp $cffd
                    beq Lc17b
                    bne Lc17e
Lc17b               jsr Sc507
Lc17e               lda #$04
                    cmp $cffd
                    beq Lc187
                    bne Lc18a
Lc187               rts

Lc188               nop
                    nop
Lc18a               lda #$05
                    cmp $cffd
                    beq Lc193
                    bne Lc196
Lc193               rts

Lc194               nop
                    nop
Lc196               nop
                    nop
                    nop
                    lda #$01
                    cmp $cffe
                    beq Lc1a2
                    bne Lc1a5
Lc1a2               jsr Sc589
Lc1a5               lda #$02
                    cmp $cffe
                    beq Lc1ae
                    bne Lc1b1
Lc1ae               jsr Sc5bc
Lc1b1               lda #$03
                    cmp $cffe
                    beq Lc1ba
                    bne Lc1bd
Lc1ba               jsr Sc661
Lc1bd               lda #$04
                    cmp $cffe
                    beq Lc1c6
                    bne Lc1c9
Lc1c6               rts

Lc1c7               nop
                    nop
Lc1c9               lda #$05
                    cmp $cffe
                    beq Lc1d2
                    bne Lc1d5
Lc1d2               rts

Lc1d3               nop
                    nop
Lc1d5               jsr Sc559
                    jsr Sc609
                    jsr Sc678
                    jsr Sc62e
                    rts

                    c018
Sc1e4               lda #$fa
                    cmp d000_vSprite0X
                    beq Lc1ed
                    bne Lc1f0
Lc1ed               jmp Lc611

Lc1f0               ldx d000_vSprite0X
                    inx
                    inx
                    inx
                    inx
                    inx
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d000_vSprite0X
                    rts

                    00 00 00 00 00 00 00 00 00
Sc20a               lda #$50
                    cmp d000_vSprite0X
                    beq Lc213
                    bne Lc216
Lc213               jmp Lc611

Lc216               ldx d000_vSprite0X
                    dex
                    dex
                    dex
                    dex
                    dex
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d000_vSprite0X
                    rts

                    00 00 00 00 00 00 00 00 00
Sc230               ldx d002_vSprite1X
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d002_vSprite1X
                    ldx d003_vSprite1Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d003_vSprite1Y
                    lda #$c8
                    cmp d003_vSprite1Y
                    beq Lc24e
                    rts

Lc24e               lda #$00
                    sta $cff9
                    rts

Sc254               ldx d002_vSprite1X
                    dex
                    dex
                    stx d002_vSprite1X
                    ldx d003_vSprite1Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d003_vSprite1Y
                    lda #$c8
                    cmp d003_vSprite1Y
                    beq Lc26f
                    rts

Lc26f               lda #$00
                    sta $cff9
                    rts

                    00 00 00
Sc278               ldx d003_vSprite1Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d003_vSprite1Y
                    lda #$c8
                    cmp d003_vSprite1Y
                    beq Lc28b
                    rts

Lc28b               lda #$00
                    sta $cff9
                    rts

                    00 00 00 00
Sc295               ldx d002_vSprite1X
                    inx
                    inx
                    stx d002_vSprite1X
                    ldx d003_vSprite1Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d003_vSprite1Y
                    lda #$c8
                    cmp d003_vSprite1Y
                    beq Lc2b0
                    rts

Lc2b0               lda #$00
                    sta $cff9
                    rts

                    00
Sc2b7               ldx d002_vSprite1X
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d002_vSprite1X
                    ldx d003_vSprite1Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d003_vSprite1Y
                    lda #$a0
                    cmp d003_vSprite1Y
                    beq Lc2d5
                    rts

Lc2d5               lda #$00
                    sta $cff9
                    rts

                    00 00 00 00 00
Sc2e0               ldx d004_vSprite2X
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d004_vSprite2X
                    ldx d005_vSprite2Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d005_vSprite2Y
                    lda #$c8
                    cmp d005_vSprite2Y
                    beq Lc2fe
                    rts

Lc2fe               lda #$00
                    sta $cffa
                    rts

                    00 00 00 00 00
Sc309               ldx d004_vSprite2X
                    dex
                    dex
                    dex
                    stx d004_vSprite2X
                    ldx d005_vSprite2Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d005_vSprite2Y
                    lda #$c8
                    cmp d005_vSprite2Y
                    beq Lc325
                    rts

Lc325               lda #$00
                    sta $cffa
                    rts

                    00
Sc32c               ldx d005_vSprite2Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d005_vSprite2Y
                    lda #$c8
                    cmp d005_vSprite2Y
                    beq Lc33f
                    rts

Lc33f               lda #$00
                    sta $cffa
                    rts

                    00 00 00 00
Sc349               ldx d004_vSprite2X
                    inx
                    inx
                    inx
                    stx d004_vSprite2X
                    ldx d005_vSprite2Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d005_vSprite2Y
                    lda #$c8
                    cmp d005_vSprite2Y
                    beq Lc365
                    rts

Lc365               lda #$00
                    sta $cffa
                    rts

                    00
Sc36c               ldx d004_vSprite2X
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d004_vSprite2X
                    ldx d005_vSprite2Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d005_vSprite2Y
                    lda #$a0
                    cmp d005_vSprite2Y
                    beq Lc38a
                    rts

Lc38a               lda #$00
                    sta $cffa
                    rts

Sc390               ldx d006_vSprite3X
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d006_vSprite3X
                    ldx d007_vSprite3Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d007_vSprite3Y
                    lda #$c8
                    cmp d007_vSprite3Y
                    beq Lc3ae
                    rts

Lc3ae               lda #$00
                    sta $cffb
                    rts

Sc3b4               ldx d006_vSprite3X
                    dex
                    dex
                    dex
                    stx d006_vSprite3X
                    ldx d007_vSprite3Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d007_vSprite3Y
                    lda #$c8
                    cmp d007_vSprite3Y
                    beq Lc3d0
                    rts

Lc3d0               lda #$00
                    sta $cffb
                    rts

                    00
Sc3d7               ldx d007_vSprite3Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d007_vSprite3Y
                    lda #$c8
                    cmp d007_vSprite3Y
                    beq Lc3ea
                    rts

Lc3ea               lda #$00
                    sta $cffb
                    rts

                    00 00 00 00
Sc3f4               ldx d006_vSprite3X
                    inx
                    inx
                    inx
                    stx d006_vSprite3X
                    ldx d007_vSprite3Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d007_vSprite3Y
                    lda #$c8
                    cmp d007_vSprite3Y
                    beq Lc410
                    rts

Lc410               lda #$00
                    sta $cffb
                    rts

                    00
Sc417               ldx d006_vSprite3X
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d006_vSprite3X
                    ldx d007_vSprite3Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d007_vSprite3Y
                    lda #$a0
                    cmp d007_vSprite3Y
                    beq Lc435
                    rts

Lc435               lda #$00
                    sta $cffb
                    rts

Sc43b               ldx d008_vSprite4X
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d008_vSprite4X
                    ldx d009_vSprite4Y
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d009_vSprite4Y
                    lda #$50
                    cmp d009_vSprite4Y
                    beq Lc459
                    rts

Lc459               lda #$00
                    sta $cffc
                    rts

Sc45f               ldx d008_vSprite4X
                    inx
                    inx
                    inx
                    stx d008_vSprite4X
                    ldx d009_vSprite4Y
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d009_vSprite4Y
                    lda #$50
                    cmp d009_vSprite4Y
                    beq Lc47b
                    rts

Lc47b               lda #$00
                    sta $cffc
                    rts

                    00
Sc482               ldx d009_vSprite4Y
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d009_vSprite4Y
                    lda #$50
                    cmp d009_vSprite4Y
                    beq Lc495
                    rts

Lc495               lda #$00
                    sta $cffc
                    rts

                    00 00 00 00
Sc49f               ldx d008_vSprite4X
                    dex
                    dex
                    dex
                    stx d008_vSprite4X
                    ldx d009_vSprite4Y
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d009_vSprite4Y
                    lda #$50
                    cmp d009_vSprite4Y
                    beq Lc4bb
                    rts

Lc4bb               lda #$00
                    sta $cffc
                    rts

                    00
Sc4c2               ldx d008_vSprite4X
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d008_vSprite4X
                    ldx d009_vSprite4Y
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d009_vSprite4Y
                    lda #$50
                    cmp d009_vSprite4Y
                    beq Lc4e0
                    rts

Lc4e0               lda #$00
                    sta $cffc
                    rts

Sc4e6               ldx d00a_vSprite5X
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d00a_vSprite5X
                    rts

Sc4f2               ldx d00a_vSprite5X
                    stx d00c_vSprite6X
                    ldx d00b_vSprite5Y
                    stx d00d_vSprite6Y
                    lda #$03
                    sta $cffd
                    rts

                    00 00 00
Sc507               ldx d00c_vSprite6X
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d00c_vSprite6X
                    ldx d00d_vSprite6Y
                    inx
                    inx
                    inx
                    inx
                    inx
                    stx d00d_vSprite6Y
                    lda #$c8
                    cmp d00d_vSprite6Y
                    beq Lc525
                    rts

Lc525               lda #$01
                    sta $cffd
                    rts

Lc52b               lda #$01
                    cmp $cff0
                    beq Lc533
                    rts

Lc533               jmp Lc004

Sc536               lda #$04
                    cmp $c5
                    beq Lc53e
                    bne Lc541
Lc53e               jsr Sc54d
Lc541               lda #$05
                    cmp $c5
                    beq Lc549
                    bne Lc54c
Lc549               jsr Sc553
Lc54c               rts

Sc54d               lda #$01
                    sta $cff0
                    rts

Sc553               lda #$00
                    sta $cff0
                    rts

Sc559               lda #$01
                    cmp $cff1
                    beq Lc561
                    rts

Lc561               lda d000_vSprite0X
                    sta d00a_vSprite5X
                    rts

Sc568               lda #$00
                    cmp $cffe
                    beq Lc570
                    rts

Lc570               lda #$28
                    sta $07ff
                    lda d000_vSprite0X
                    sta d00e_vSprite7X
                    lda #$78
                    sta d00f_vSprite7Y
                    lda #$01
                    sta $cffe
                    nop
                    nop
                    nop
                    rts

Sc589               lda #$2d
                    cmp $07ff
                    bne Lc596
                    lda #$00
                    sta $cffe
                    rts

Lc596               ldx $07ff
                    inx
                    stx $07ff
                    rts

Sc59e               lda #$00
                    cmp $cffe
                    beq Lc5a6
                    rts

Lc5a6               lda #$02
                    sta $cffe
                    lda d000_vSprite0X
                    sta d00e_vSprite7X
                    lda #$78
                    sta d00f_vSprite7Y
                    lda #$2e
                    sta $07ff
                    rts

Sc5bc               ldx d00f_vSprite7Y
                    dex
                    dex
                    dex
                    dex
                    dex
                    stx d00f_vSprite7Y
                    lda #$00
                    cmp d00f_vSprite7Y
                    beq Lc5cf
                    rts

Lc5cf               lda #$00
                    sta $cffe
                    rts

Sc5d5               lda #$00
                    cmp $cffe
                    beq Lc5dd
                    rts

Lc5dd               lda #$2f
                    sta $07ff
                    lda d000_vSprite0X
                    sta d00e_vSprite7X
                    lda #$b4
                    sta d00f_vSprite7Y
                    lda #$03
                    sta $cffe
                    rts

                             ad 00 d0 8d 0e d0 a9 2f c5 c5 d0 01 60
                    a9 00 8d fe cf 8d 0e d0 60
Sc609               lda #$01
                    cmp $cff3
                    beq Lc611
                    rts

Lc611               lda #$b4
                    cmp d000_vSprite0X
                    beq Lc619
                    rts

Lc619               lda #$00
                    sta $cff9
                    sta $cffa
                    sta $cffb
                    sta $cffc
                    sta $cffd
                    sta $cffe
                    rts

Sc62e               lda #$6f
                    cmp $dc00
                    bne Lc638
                    jsr Sc568
Lc638               lda #$7e
                    cmp $dc00
                    bne Lc642
                    jsr Sc59e
Lc642               lda #$7d
                    cmp $dc00
                    bne Lc64c
                    jsr Sc5d5
Lc64c               lda #$7b
                    cmp $dc00
                    bne Lc656
                    jsr Sc20a
Lc656               lda #$77
                    cmp $dc00
                    bne Lc660
                    jsr Sc1e4
Lc660               rts

Sc661               lda d000_vSprite0X
                    sta d00e_vSprite7X
                    lda #$7d
                    cmp $dc00
                    bne Lc66f
                    rts

Lc66f               lda #$00
                    sta d00e_vSprite7X
                    sta $cffe
                    rts

Sc678               lda #$28
                    sta $079d
                    lda #$03
                    sta $079e
                    lda #$29
                    sta $079f
                    lda #$03
                    sta $07a1
                    lda #$0f
                    sta $07a2
                    lda #$10
                    sta $07a3
                    lda #$0c
                    sta $07a4
                    lda #$09
                    sta $07a5
                    lda #$0e
                    sta $07a6
                    lda #$13
                    sta $07a8
                    lda #$0f
                    sta $07a9
                    lda #$06
                    sta $07aa
                    lda #$14
                    sta $07ab
                    lda #$17
                    sta $07ac
                    lda #$01
                    sta $07ad
                    lda #$12
                    sta $07ae
                    lda #$05
                    sta $07af
                    rts

                                                              00 ff
                    00 ff 00 ff a9 00 8d 18 d4 8d 04 d4 8d 05 d4 a9
                    0f 8d 18 d4
Lc6e4               lda #$81
                    sta d404_sVoc1Control
                    lda #$88
                    sta d405_sVoc1AttDec
                    lda #$28
                    sta d401_sVoc1FreqHi
                    lda #$c8
                    sta d400_sVoc1FreqLo
                    rts

                                               ae 00 d0 ca ca ca 8e
                    00 d0 ae 02 d0 ca ca ca 8e 02 d0 ae 04 d0 ca ca
                    ca 8e 04 d0 ae 06 d0 ca ca ca 8e 06 d0 60 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff
Lc738               lda #$00
                    sta d40c_sVoc2AttDec
                    sta d40b_sVoc2Control
                    lda #$0f
                    sta d418_sFiltMode
                    lda #$09
                    sta d40c_sVoc2AttDec
                    lda #$41
                    sta d40b_sVoc2Control
                    lda #$00
                    sta d40a_sVoc2PWidthHi
                    lda #$ff
                    sta d409_sVoc2PWidthLo
                    ldx $c7ff
                    inx
                    lda $c800,x
                    sta d408_sVoc2FreqHi
                    inx
                    lda $c800,x
                    sta d407_sVoc2FreqLo
                    inx
                    lda $c800,x
                    sta d40d_sVoc2SusRel
                    stx $c7ff
                    lda #$e9
                    cmp $c7ff
                    beq Lc77c
                    rts

Lc77c               lda #$5c
                    sta $c7ff
                    inc $c7fe
                    lda #$05
                    cmp $c7fe
                    beq Lc78c
                    rts

Lc78c               lda #$02
                    sta $c7ff
                    sta $c7fe
                    rts

                                   ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 02 89
                    06 10 ff 06 6c ff 06 10 ff 06 6c ff 06 10 ff 06
                    6c ff 06 10 ff 06 6c ff 09 9f 88 0a cd 88 0b 72
                    88 09 9f 88 0a cd 88 0b 72 88 09 9f 88 0a cd 88
                    0b 72 88 09 9f 88 0a cd 88 0b 72 88 09 9f 88 0a
                    cd 88 0b 72 88 09 9f 88 0a cd 88 0b 72 88 09 9f
                    88 0a cd 88 0b 72 88 09 9f 88 0a cd 41 0a cd 41
                    0a cd 41 09 9f 41 09 9f 41 09 9f 41 09 9f 41 0b
                    72 41 0b 72 41 0a cd 41 0a cd 41 0a cd 41 09 9f
                    88 0a cd 41 0a cd 41 0a cd 41 09 9f 41 09 9f 41
                    09 9f 41 09 9f 41 0b 72 41 0b 72 41 0a cd 41 0a
                    cd 41 0a cd 41 09 9f 88 0a cd 41 0a cd 41 0a cd
                    41 09 9f 41 09 9f 41 09 9f 41 09 9f 41 0b 72 41
                    0b 72 41 0a cd 41 0a cd 41 0a cd 41 0a cd 41 0a
                    3c 88 09 9f 88 10 2f ff 0e 6b ff 0c d8 ff 0c 20
                    ff 0c d8 88 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff 00 ff
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 ae 00 d0 ca
                    ca ca 8e 00 d0 ae 02 d0 ca ca ca 8e 02 d0 ae 04
                    d0 ca ca ca 8e 04 d0 ae 06 d0 ca ca ca 8e 06 d0
                    60 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    01 55 40 02 aa 80 06 aa 90 06 aa 90 06 aa 90 02
                    55 80 02 aa 80 02 aa 80 02 aa 80 02 aa 80 02 55
                    80 02 55 80 02 55 80 16 aa 94 16 eb 94 16 eb 94
                    01 55 40 00 00 00 00 00 00 00 00 00 00 00 00 02
                    aa 80 06 aa 90 06 aa 90 06 aa 90 06 aa 90 02 55
                    80 02 55 80 02 55 80 02 55 80 02 aa 80 06 aa 90
                    06 aa 90 06 28 90 02 28 80 01 55 40 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    10 00 08 04 00 0a 01 00 0a 00 40 0a 00 20 0a 82
                    90 02 aa a4 00 a9 41 00 29 50 00 11 50 00 04 00
                    00 01 00 00 00 40 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 22
                    00 00 22 00 00 2a 80 00 2a 80 00 aa 80 02 aa a0
                    08 aa a0 08 aa 88 02 aa 88 0a aa 88 2a aa 80 22
                    aa 82 22 aa 22 0a aa 22 08 a0 20 08 a0 a0 08 88
                    a4 0a 88 a4 02 28 84 00 28 04 00 20 00 00 00 0c
                    20 00 0a 08 00 03 80 00 0c c0 00 02 2b e0 00 ce
                    28 0a 33 c0 0c 36 08 03 0b 00 08 20 00 02 3c 00
                    00 80 c0 02 28 00 03 f3 c0 00 a0 00 00 f3 00 00
                    00 08 00 00 00 0c 08 20 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 ac 00 00 b4 00 00
                    81 40 00 f4 14 00 b2 41 00 00 14 00 00 01 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 82 00 00
                    c3 00 00 82 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 82 00 00 c3 00
                    00 82 00 00 00 00 00 00 00 00 00 00 00 82 00 00
                    c3 00 00 82 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 82 00 00 c3 00 00 82
                    00 00 00 00 00 00 00 00 00 00 00 82 00 00 c3 00
                    00 82 00 00 00 00 00 00 00 00 00 00 00 82 00 00
                    c3 00 00 82 00 00 82 00 00 c3 00 00 82 00 00 00
                    00 00 00 00 00 00 00 00 00 82 00 00 c3 00 00 82
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 08 00 00 08 00 00 08 00 00 08 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
                    55 40 02 aa 80 2a aa a8 2a aa a8 2a aa a8 02 55
                    80 02 aa 80 02 aa 80 02 aa 80 02 aa 80 02 55 80
                    02 55 80 02 55 80 2a aa a8 2a eb a8 2a eb a8 01
                    55 40 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 aa 80 00 bf
                    80 00 bf 80 00 bf 80 00 bf 80 00 bf 80 00 bf 80
                    00 bf 80 00 bf 80 00 95 80 00 95 80 00 aa 80 00
                    2a 00 00 2a 00 00 08 00 00 08 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 aa aa aa aa aa aa aa aa aa 2a aa a8 2a aa a8
                    2a aa a8 0a aa a0 0a aa a0 0a aa a0 02 aa 80 02
                    aa 80 02 aa 80 00 82 00 00 82 00 00 82 00 00 01
                    55 40 03 ff c0 07 ff d0 07 ff d0 07 ff d0 03 55
                    c0 03 55 c0 03 ff c0 03 ff c0 03 ff c0 03 ff c0
                    03 ff c0 03 ff c0 07 ff d0 07 ff d0 07 ff d0 03
                    ff d0 07 ff d0 07 ff d0 07 ff d0 01 55 40 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 40 f0
                    00 c0 0c 3f 00 03 ff ff fd 3f ff fd 0c 3f c3 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 0f 00 00 c3 00 30 30 00 ff fc 03 15 53 03 15
                    53 3f 14 53 3f 14 53 3f 14 53 3f 14 53 3f 14 53
                    ff 15 53 ff 15 53 1f ff fc 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 ff ff 03 15
                    53 ff 00 53 ff 00 53 ff 01 43 ff 05 03 ff 05 3f
                    ff 05 3f ff 05 3f ff ff ff 3f ff ff 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    00 00 00 00 00 00 00 00 00 03 04 04 03 03 00

