
.virtual $00c5
; read by: frame_keys, turbo_keys, unused_smoke_follow
last_key:		.byte	?
.endv

*=$0340

; ---------------------------------------------------------------- sprites (low)
; Sprite blocks the BASIC copies from sprite_source (lines 8000-8028).
; 13 player car, 14 enemy car, 15 helicopter
sprite_player_car:
		.binary	"sprites_13_15.bin"
sprite_enemy_car = $0380
sprite_helicopter = $03c0

.virtual $0400
; written by: print_credit
screen_ram:
		.fill	925
; 007 Car Chase (Coplin Software, 1985): a BASIC V2 game (007.bas) with a machine
; code helper at $c000 (file "007"). BASIC draws the road by PRINTing rows and calls
; the helper with SYS between them; the two talk through $cfd0-$cfff and the VIC.
; ---------------------------------------------------------------- screen
; screen row 22, columns 13-31: the helper prints "(c) coplin software" here
; written by: print_credit
credit_text:
		.fill	75
.endv

.virtual $07f8
; read by: guns_animate
; written by: fire_guns, guns_animate, fire_missile, fire_smoke
sprite_pointers:
		.fill	8
; ---------------------------------------------------------------- sprites (high)
; block 32: left over from the loader's BASIC program, not a sprite
leftover_0800:
		.fill	64
.endv

*=$0840

; 33 explosion, 34 helicopter bomb.
; The copy for block 33 starts 2 bytes late in sprite_source (52255, not 52253)
sprite_explosion:
		.binary	"sprites_33_34.bin"
sprite_bomb = $0880

.virtual $08c0
; blocks 35-39: left over from the loader's title text, not sprites
leftover_08c0:
		.fill	320
.endv

*=$0a00

; 40-45 gun fire animation (44 and 45 are cleared by line 8015: the flash ends),
; 46 missile, 47 smoke, 48 player car on the bridge, 49 enemy car on the bridge,
; 50 headlights in the tunnel, 51 bonus car, 52-54 title logo "007"
sprite_guns:
		.binary	"sprites_40_54.bin"
sprite_missile = $0b80
sprite_smoke = $0bc0
sprite_bridge_player = $0c00
sprite_bridge_enemy = $0c40
sprite_headlights = $0c80
sprite_bonus_car = $0cc0
sprite_logo = $0d00

.virtual $0dc0
untouched_0dc0:
		.fill	576
.endv

*=$1000

; ---------------------------------------------------------------- BASIC
basic_start_zero:
		.byte	$00

; The game's BASIC program (007.bas), listed in 07.bas
basic_program:
		.binary	"007bas.prg", 2

.virtual $9817
; BASIC's simple variables and arrays, then free memory, then the strings
basic_variables:
		.fill	316
untouched_9953:
		.fill	1702
basic_strings:
		.fill	8
untouched_a001:
		.fill	8191
.endv

*=$c000

; ---------------------------------------------------------------- frame update
; sys49152, called between the road's PRINT rows: a second frame update when turbo
; (F1) is on, else nothing
turbo_frame:
		jmp turbo_check

; sys49155: one frame of the game. Keys M/Z steer, SPACE guns, '.' missile, ','
; smoke; then the three enemy cars, F1/F3, the car from behind, the helicopter
; and the weapon. Every move is a run of inx/dex.
frame_update:
		nop 
; jumped to by: turbo_check
frame_keys:
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
		nop 
		lda #$24
		cmp last_key
		beq lC020
		bne lC023
; jumped to by: frame_keys
lC020:
		jsr player_right
; jumped to by: frame_keys
lC023:
		lda #$0c
		cmp last_key
		beq lC02B
		bne lC02E
; jumped to by: frame_keys
lC02B:
		jsr player_left
; jumped to by: frame_keys
lC02E:
		lda #$3c
		cmp last_key
		beq lC036
		bne lC039
; jumped to by: frame_keys
lC036:
		jsr fire_guns
; jumped to by: frame_keys
lC039:
		lda #$2c
		cmp last_key
		beq lC041
		bne lC044
; jumped to by: frame_keys
lC041:
		jsr fire_missile
; jumped to by: frame_keys
lC044:
		lda #$2f
		cmp last_key
		beq lC04C
		bne frame_car1
; jumped to by: frame_keys
lC04C:
		jsr fire_smoke
; line 4 pokes nops over $c015-$c017
; jumped to by: frame_keys
frame_car1:
		nop 
		nop 
		nop 
		lda #$05
		cmp car1_direction
		beq lC05B
		bne lC05E
; jumped to by: frame_car1
lC05B:
		jsr car1_down_left5
; jumped to by: frame_car1
lC05E:
		lda #$01
		cmp car1_direction
		beq lC067
		bne lC06A
; jumped to by: frame_car1
lC067:
		jsr car1_down_left2
; jumped to by: frame_car1
lC06A:
		lda #$02
		cmp car1_direction
		beq lC073
		bne lC076
; jumped to by: frame_car1
lC073:
		jsr car1_down
; jumped to by: frame_car1
lC076:
		lda #$03
		cmp car1_direction
		beq lC07F
		bne lC082
; jumped to by: frame_car1
lC07F:
		jsr car1_down_right2
; jumped to by: frame_car1
lC082:
		lda #$04
		cmp car1_direction
		beq lC08B
		bne frame_car2
; jumped to by: frame_car1
lC08B:
		jsr car1_down_right5
; jumped to by: frame_car1
frame_car2:
		nop 
		nop 
		nop 
		lda #$01
		cmp car2_direction
		beq lC09A
		bne lC09D
; jumped to by: frame_car2
lC09A:
		jsr car2_down_left5
; jumped to by: frame_car2
lC09D:
		lda #$02
		cmp car2_direction
		beq lC0A6
		bne lC0A9
; jumped to by: frame_car2
lC0A6:
		jsr car2_down_left3
; jumped to by: frame_car2
lC0A9:
		lda #$03
		cmp car2_direction
		beq lC0B2
		bne lC0B5
; jumped to by: frame_car2
lC0B2:
		jsr car2_down
; jumped to by: frame_car2
lC0B5:
		lda #$04
		cmp car2_direction
		beq lC0BE
		bne lC0C1
; jumped to by: frame_car2
lC0BE:
		jsr car2_down_right3
; jumped to by: frame_car2
lC0C1:
		lda #$05
		cmp car2_direction
		beq lC0CA
		bne frame_car3
; jumped to by: frame_car2
lC0CA:
		jsr car2_down_right5
; jumped to by: frame_car2
frame_car3:
		nop 
		nop 
		nop 
		lda #$01
		cmp car3_direction
		beq lC0D9
		bne lC0DC
; jumped to by: frame_car3
lC0D9:
		jsr car3_down_left5
; jumped to by: frame_car3
lC0DC:
		lda #$02
		cmp car3_direction
		beq lC0E5
		bne lC0E8
; jumped to by: frame_car3
lC0E5:
		jsr car3_down_left3
; jumped to by: frame_car3
lC0E8:
		lda #$03
		cmp car3_direction
		beq lC0F1
		bne lC0F4
; jumped to by: frame_car3
lC0F1:
		jsr car3_down
; jumped to by: frame_car3
lC0F4:
		lda #$04
		cmp car3_direction
		beq lC0FD
		bne lC100
; jumped to by: frame_car3
lC0FD:
		jsr car3_down_right3
; jumped to by: frame_car3
lC100:
		lda #$05
		cmp car3_direction
		beq lC109
		bne frame_car4
; jumped to by: frame_car3
lC109:
		jsr car3_down_right5
; jumped to by: frame_car3
frame_car4:
		jsr turbo_keys
		lda #$01
		cmp car4_direction
		beq lC118
		bne lC11B
; jumped to by: frame_car4
lC118:
		jsr car4_up_right5
; jumped to by: frame_car4
lC11B:
		lda #$02
		cmp car4_direction
		beq lC124
		bne lC127
; jumped to by: frame_car4
lC124:
		jsr car4_up_right3
; jumped to by: frame_car4
lC127:
		lda #$03
		cmp car4_direction
		beq lC130
		bne lC133
; jumped to by: frame_car4
lC130:
		jsr car4_up
; jumped to by: frame_car4
lC133:
		lda #$04
		cmp car4_direction
		beq lC13C
		bne lC13F
; jumped to by: frame_car4
lC13C:
		jsr car4_up_left3
; jumped to by: frame_car4
lC13F:
		lda #$05
		cmp car4_direction
		beq lC148
		bne frame_car4_skip
; jumped to by: frame_car4
lC148:
		jsr car4_up_left5
; the car from behind in direction 5 ends the frame here: no helicopter, no weapon
; jumped to by: frame_car4
frame_car4_skip:
		lda #$05
		cmp car4_direction
		beq lC154
		bne frame_helicopter
; jumped to by: frame_car4_skip
lC154:
		rts 

; rts nop nop: a 3 byte instruction cut short to rts
pad_c155:
		.byte	$ea, $ea

; jumped to by: frame_car4_skip
frame_helicopter:
		nop 
		nop 
		nop 
		lda #$01
		cmp heli_state
		beq lC163
		bne lC166
; jumped to by: frame_helicopter
lC163:
		jsr heli_fly
; jumped to by: frame_helicopter
lC166:
		lda #$02
		cmp heli_state
		beq lC16F
		bne lC172
; jumped to by: frame_helicopter
lC16F:
		jsr heli_drop_bomb
; jumped to by: frame_helicopter
lC172:
		lda #$03
		cmp heli_state
		beq lC17B
		bne lC17E
; jumped to by: frame_helicopter
lC17B:
		jsr bomb_fall
; jumped to by: frame_helicopter
lC17E:
		lda #$04
		cmp heli_state
		beq lC187
		bne lC18A
; jumped to by: frame_helicopter
lC187:
		rts 

pad_c188:
		.byte	$ea, $ea

; jumped to by: frame_helicopter
lC18A:
		lda #$05
		cmp heli_state
		beq lC193
		bne lC196
; jumped to by: $c18f
lC193:
		rts 

pad_c194:
		.byte	$ea, $ea

; jumped to by: $c191
lC196:
		nop 
		nop 
		nop 
; sys49561: just the weapon
weapon_update:
		lda #$01
		cmp weapon_state
		beq lC1A2
		bne lC1A5
; jumped to by: weapon_update
lC1A2:
		jsr guns_animate
; jumped to by: weapon_update
lC1A5:
		lda #$02
		cmp weapon_state
		beq lC1AE
		bne lC1B1
; jumped to by: weapon_update
lC1AE:
		jsr missile_fly
; jumped to by: weapon_update
lC1B1:
		lda #$03
		cmp weapon_state
		beq lC1BA
		bne lC1BD
; jumped to by: weapon_update
lC1BA:
		jsr smoke_follow
; jumped to by: weapon_update
lC1BD:
		lda #$04
		cmp weapon_state
		beq lC1C6
		bne lC1C9
; jumped to by: weapon_update
lC1C6:
		rts 

pad_c1c7:
		.byte	$ea, $ea

; jumped to by: weapon_update
lC1C9:
		lda #$05
		cmp weapon_state
		beq lC1D2
		bne frame_extras
; jumped to by: $c1ce
lC1D2:
		rts 

pad_c1d3:
		.byte	$ea, $ea

; Runs on every weapon_update (the test above branches here when the state is
; not 5): headlights, crash reset, credit, joystick. Line 3 pokes
; jsr joystick_controls into $c1de and line 39 the rts at $c1e1.
; jumped to by: $c1d0
frame_extras:
		jsr headlights_follow
		jsr crash_reset_check
		jsr print_credit
		jsr joystick_controls
		rts 

; the operand of the instruction that was at $c1e1 before the rts: $c018
pad_c1e2:
		.byte	$18, $c0

; ---------------------------------------------------------------- player
; Moves the player car 10 pixels right; at the right kerb ($fa) checks the crash reset
; called by: frame_keys, joystick_controls
player_right:
		lda #$fa
		cmp vic_sprite_coords
		beq lC1ED
		bne lC1F0
; jumped to by: player_right
lC1ED:
		jmp crash_reset

; jumped to by: player_right
lC1F0:
		ldx vic_sprite_coords
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
		stx vic_sprite_coords
		rts 

.virtual $c201
unused_c201:
		.fill	9
.endv

*=$c20a

; 10 pixels left; at the left kerb ($50) checks the crash reset
; called by: frame_keys, joystick_controls
player_left:
		lda #$50
		cmp vic_sprite_coords
		beq lC213
		bne lC216
; jumped to by: player_left
lC213:
		jmp crash_reset

; jumped to by: player_left
lC216:
		ldx vic_sprite_coords
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
		stx vic_sprite_coords
		rts 

.virtual $c227
unused_c227:
		.fill	9
.endv

*=$c230

; ---------------------------------------------------------------- enemy cars
; Enemy car 1 (sprite 1), by direction in car1_direction: down 5 pixels a frame
; and sideways; at y $c8 (direction 4: $a0) the direction becomes 0 (BASIC respawns it)
; called by: frame_car1
car1_down_left5:
		ldx vic_sprite_coords + $2
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $2
		ldx vic_sprite_coords + $3
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $3
		lda #$c8
		cmp vic_sprite_coords + $3
		beq lC24E
		rts 

; jumped to by: car1_down_left5
lC24E:
		lda #$00
		sta car1_direction
		rts 

; called by: frame_car1
car1_down_left2:
		ldx vic_sprite_coords + $2
		dex 
		dex 
		stx vic_sprite_coords + $2
		ldx vic_sprite_coords + $3
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $3
		lda #$c8
		cmp vic_sprite_coords + $3
		beq lC26F
		rts 

; jumped to by: car1_down_left2
lC26F:
		lda #$00
		sta car1_direction
		rts 

.virtual $c275
unused_c275:
		.fill	3
.endv

*=$c278

; called by: frame_car1
car1_down:
		ldx vic_sprite_coords + $3
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $3
		lda #$c8
		cmp vic_sprite_coords + $3
		beq lC28B
		rts 

; jumped to by: car1_down
lC28B:
		lda #$00
		sta car1_direction
		rts 

.virtual $c291
unused_c291:
		.fill	4
.endv

*=$c295

; called by: frame_car1
car1_down_right2:
		ldx vic_sprite_coords + $2
		inx 
		inx 
		stx vic_sprite_coords + $2
		ldx vic_sprite_coords + $3
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $3
		lda #$c8
		cmp vic_sprite_coords + $3
		beq lC2B0
		rts 

; jumped to by: car1_down_right2
lC2B0:
		lda #$00
		sta car1_direction
		rts 

.virtual $c2b6
unused_c2b6:		.byte	?
.endv

*=$c2b7

; called by: frame_car1
car1_down_right5:
		ldx vic_sprite_coords + $2
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $2
		ldx vic_sprite_coords + $3
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $3
		lda #$a0
		cmp vic_sprite_coords + $3
		beq lC2D5
		rts 

; jumped to by: car1_down_right5
lC2D5:
		lda #$00
		sta car1_direction
		rts 

.virtual $c2db
unused_c2db:
		.fill	5
.endv

*=$c2e0

; Enemy car 2 (sprite 2), by car2_direction 1-5: left 5, left 3, straight, right 3,
; right 5; ends at y $c8 (direction 5: $a0)
; called by: frame_car2
car2_down_left5:
		ldx vic_sprite_coords + $4
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $4
		ldx vic_sprite_coords + $5
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $5
		lda #$c8
		cmp vic_sprite_coords + $5
		beq lC2FE
		rts 

; jumped to by: car2_down_left5
lC2FE:
		lda #$00
		sta car2_direction
		rts 

.virtual $c304
unused_c304:
		.fill	5
.endv

*=$c309

; called by: frame_car2
car2_down_left3:
		ldx vic_sprite_coords + $4
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $4
		ldx vic_sprite_coords + $5
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $5
		lda #$c8
		cmp vic_sprite_coords + $5
		beq lC325
		rts 

; jumped to by: car2_down_left3
lC325:
		lda #$00
		sta car2_direction
		rts 

.virtual $c32b
unused_c32b:		.byte	?
.endv

*=$c32c

; called by: frame_car2
car2_down:
		ldx vic_sprite_coords + $5
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $5
		lda #$c8
		cmp vic_sprite_coords + $5
		beq lC33F
		rts 

; jumped to by: car2_down
lC33F:
		lda #$00
		sta car2_direction
		rts 

.virtual $c345
unused_c345:
		.fill	4
.endv

*=$c349

; called by: frame_car2
car2_down_right3:
		ldx vic_sprite_coords + $4
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $4
		ldx vic_sprite_coords + $5
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $5
		lda #$c8
		cmp vic_sprite_coords + $5
		beq lC365
		rts 

; jumped to by: car2_down_right3
lC365:
		lda #$00
		sta car2_direction
		rts 

.virtual $c36b
unused_c36b:		.byte	?
.endv

*=$c36c

; called by: frame_car2
car2_down_right5:
		ldx vic_sprite_coords + $4
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $4
		ldx vic_sprite_coords + $5
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $5
		lda #$a0
		cmp vic_sprite_coords + $5
		beq lC38A
		rts 

; jumped to by: car2_down_right5
lC38A:
		lda #$00
		sta car2_direction
		rts 

; Enemy car 3 (sprite 3), as car 2
; called by: frame_car3
car3_down_left5:
		ldx vic_sprite_coords + $6
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $6
		ldx vic_sprite_coords + $7
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $7
		lda #$c8
		cmp vic_sprite_coords + $7
		beq lC3AE
		rts 

; jumped to by: car3_down_left5
lC3AE:
		lda #$00
		sta car3_direction
		rts 

; called by: frame_car3
car3_down_left3:
		ldx vic_sprite_coords + $6
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $6
		ldx vic_sprite_coords + $7
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $7
		lda #$c8
		cmp vic_sprite_coords + $7
		beq lC3D0
		rts 

; jumped to by: car3_down_left3
lC3D0:
		lda #$00
		sta car3_direction
		rts 

.virtual $c3d6
unused_c3d6:		.byte	?
.endv

*=$c3d7

; called by: frame_car3
car3_down:
		ldx vic_sprite_coords + $7
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $7
		lda #$c8
		cmp vic_sprite_coords + $7
		beq lC3EA
		rts 

; jumped to by: car3_down
lC3EA:
		lda #$00
		sta car3_direction
		rts 

.virtual $c3f0
unused_c3f0:
		.fill	4
.endv

*=$c3f4

; called by: frame_car3
car3_down_right3:
		ldx vic_sprite_coords + $6
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $6
		ldx vic_sprite_coords + $7
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $7
		lda #$c8
		cmp vic_sprite_coords + $7
		beq lC410
		rts 

; jumped to by: car3_down_right3
lC410:
		lda #$00
		sta car3_direction
		rts 

.virtual $c416
unused_c416:		.byte	?
.endv

*=$c417

; called by: frame_car3
car3_down_right5:
		ldx vic_sprite_coords + $6
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $6
		ldx vic_sprite_coords + $7
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $7
		lda #$a0
		cmp vic_sprite_coords + $7
		beq lC435
		rts 

; jumped to by: car3_down_right5
lC435:
		lda #$00
		sta car3_direction
		rts 

; Car 4 (sprite 4) comes from behind: up 5 pixels a frame, by car4_direction 1-5:
; right 5, right 3, straight, left 3, left 5; ends at y $50
; called by: frame_car4
car4_up_right5:
		ldx vic_sprite_coords + $8
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $8
		ldx vic_sprite_coords + $9
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $9
		lda #$50
		cmp vic_sprite_coords + $9
		beq lC459
		rts 

; jumped to by: car4_up_right5
lC459:
		lda #$00
		sta car4_direction
		rts 

; called by: frame_car4
car4_up_right3:
		ldx vic_sprite_coords + $8
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $8
		ldx vic_sprite_coords + $9
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $9
		lda #$50
		cmp vic_sprite_coords + $9
		beq lC47B
		rts 

; jumped to by: car4_up_right3
lC47B:
		lda #$00
		sta car4_direction
		rts 

.virtual $c481
unused_c481:		.byte	?
.endv

*=$c482

; called by: frame_car4
car4_up:
		ldx vic_sprite_coords + $9
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $9
		lda #$50
		cmp vic_sprite_coords + $9
		beq lC495
		rts 

; jumped to by: car4_up
lC495:
		lda #$00
		sta car4_direction
		rts 

.virtual $c49b
unused_c49b:
		.fill	4
.endv

*=$c49f

; called by: frame_car4
car4_up_left3:
		ldx vic_sprite_coords + $8
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $8
		ldx vic_sprite_coords + $9
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $9
		lda #$50
		cmp vic_sprite_coords + $9
		beq lC4BB
		rts 

; jumped to by: car4_up_left3
lC4BB:
		lda #$00
		sta car4_direction
		rts 

.virtual $c4c1
unused_c4c1:		.byte	?
.endv

*=$c4c2

; called by: frame_car4
car4_up_left5:
		ldx vic_sprite_coords + $8
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $8
		ldx vic_sprite_coords + $9
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $9
		lda #$50
		cmp vic_sprite_coords + $9
		beq lC4E0
		rts 

; jumped to by: car4_up_left5
lC4E0:
		lda #$00
		sta car4_direction
		rts 

; ---------------------------------------------------------------- helicopter
; heli_state 1: the helicopter (sprite 5) flies right 5 pixels a frame
; called by: frame_helicopter
heli_fly:
		ldx vic_sprite_coords + $a
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $a
		rts 

; heli_state 2: the bomb (sprite 6) starts at the helicopter, state 3
; called by: frame_helicopter
heli_drop_bomb:
		ldx vic_sprite_coords + $a
		stx vic_sprite_coords + $c
		ldx vic_sprite_coords + $b
		stx vic_sprite_coords + $d
		lda #$03
		sta heli_state
		rts 

.virtual $c504
unused_c504:
		.fill	3
.endv

*=$c507

; heli_state 3: the bomb falls down right 5/5 until y $c8, then state 1
; called by: frame_helicopter
bomb_fall:
		ldx vic_sprite_coords + $c
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $c
		ldx vic_sprite_coords + $d
		inx 
		inx 
		inx 
		inx 
		inx 
		stx vic_sprite_coords + $d
		lda #$c8
		cmp vic_sprite_coords + $d
		beq lC525
		rts 

; jumped to by: bomb_fall
lC525:
		lda #$01
		sta heli_state
		rts 

; ---------------------------------------------------------------- turbo
; jumped to by: turbo_frame
turbo_check:
		lda #$01
		cmp turbo
		beq lC533
		rts 

; jumped to by: turbo_check
lC533:
		jmp frame_keys

; F1 turns turbo on, F3 off
; called by: frame_car4
turbo_keys:
		lda #$04
		cmp last_key
		beq lC53E
		bne lC541
; jumped to by: turbo_keys
lC53E:
		jsr turbo_on
; jumped to by: turbo_keys
lC541:
		lda #$05
		cmp last_key
		beq lC549
		bne lC54C
; jumped to by: turbo_keys
lC549:
		jsr turbo_off
; jumped to by: turbo_keys
lC54C:
		rts 

; called by: turbo_keys
turbo_on:
		lda #$01
		sta turbo
		rts 

; called by: turbo_keys
turbo_off:
		lda #$00
		sta turbo
		rts 

; ---------------------------------------------------------------- weapons
; In the tunnel (headlights_on) the headlights (sprite 5) follow the player car
; called by: frame_extras
headlights_follow:
		lda #$01
		cmp headlights_on
		beq lC561
		rts 

; jumped to by: headlights_follow
lC561:
		lda vic_sprite_coords
		sta vic_sprite_coords + $a
		rts 

; Fires the guns (sprite 7, pointer 40) above the player car when no weapon is busy.
; Line 40 pokes the y ($c57c, 120).
; called by: frame_keys, joystick_controls
fire_guns:
		lda #$00
		cmp weapon_state
		beq lC570
		rts 

; jumped to by: fire_guns
lC570:
		lda #$28
		sta sprite_pointers + $7
		lda vic_sprite_coords
		sta vic_sprite_coords + $e
		lda #$78
		sta vic_sprite_coords + $f
		lda #$01
		sta weapon_state
		nop 
		nop 
		nop 
		rts 

; weapon 1: next gun frame until pointer 45, then the weapon is free
; called by: weapon_update
guns_animate:
		lda #$2d
		cmp sprite_pointers + $7
		bne lC596
		lda #$00
		sta weapon_state
		rts 

; jumped to by: guns_animate
lC596:
		ldx sprite_pointers + $7
		inx 
		stx sprite_pointers + $7
		rts 

; Fires the missile (pointer 46); line 40 pokes the y ($c5b2, 120)
; called by: frame_keys, joystick_controls
fire_missile:
		lda #$00
		cmp weapon_state
		beq lC5A6
		rts 

; jumped to by: fire_missile
lC5A6:
		lda #$02
		sta weapon_state
		lda vic_sprite_coords
		sta vic_sprite_coords + $e
		lda #$78
		sta vic_sprite_coords + $f
		lda #$2e
		sta sprite_pointers + $7
		rts 

; weapon 2: the missile flies up 5 pixels a frame until y 0
; called by: weapon_update
missile_fly:
		ldx vic_sprite_coords + $f
		dex 
		dex 
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $f
		lda #$00
		cmp vic_sprite_coords + $f
		beq lC5CF
		rts 

; jumped to by: missile_fly
lC5CF:
		lda #$00
		sta weapon_state
		rts 

; Drops smoke (pointer 47) behind the player car
; called by: frame_keys, joystick_controls
fire_smoke:
		lda #$00
		cmp weapon_state
		beq lC5DD
		rts 

; jumped to by: fire_smoke
lC5DD:
		lda #$2f
		sta sprite_pointers + $7
		lda vic_sprite_coords
		sta vic_sprite_coords + $e
		lda #$b4
		sta vic_sprite_coords + $f
		lda #$03
		sta weapon_state
		rts 

; an older smoke_follow that used the ',' key instead of joystick down; unused
unused_smoke_follow:
		lda vic_sprite_coords
		sta vic_sprite_coords + $e
		lda #$2f
		cmp last_key
		bne lC600
		rts 

; jumped to by: unused_smoke_follow
lC600:
		lda #$00
		sta weapon_state
		sta vic_sprite_coords + $e
		rts 

; called by: frame_extras
crash_reset_check:
		lda #$01
		cmp crash_reset_on
		beq crash_reset
		rts 

; With the player car back at the middle of the road (x $b4): all cars, the
; helicopter and the weapon stopped
; jumped to by: player_right, player_left, crash_reset_check
crash_reset:
		lda #$b4
		cmp vic_sprite_coords
		beq lC619
		rts 

; jumped to by: crash_reset
lC619:
		lda #$00
		sta car1_direction
		sta car2_direction
		sta car3_direction
		sta car4_direction
		sta heli_state
		sta weapon_state
		rts 

; Joystick in port 2: fire guns, up missile, down smoke, left, right
; called by: frame_extras
joystick_controls:
		lda #$6f
		cmp cia1_port_a
		bne lC638
		jsr fire_guns
; jumped to by: joystick_controls
lC638:
		lda #$7e
		cmp cia1_port_a
		bne lC642
		jsr fire_missile
; jumped to by: joystick_controls
lC642:
		lda #$7d
		cmp cia1_port_a
		bne lC64C
		jsr fire_smoke
; jumped to by: joystick_controls
lC64C:
		lda #$7b
		cmp cia1_port_a
		bne lC656
		jsr player_left
; jumped to by: joystick_controls
lC656:
		lda #$77
		cmp cia1_port_a
		bne lC660
		jsr player_right
; jumped to by: joystick_controls
lC660:
		rts 

; weapon 3: the smoke follows the player car while the joystick is held down
; called by: weapon_update
smoke_follow:
		lda vic_sprite_coords
		sta vic_sprite_coords + $e
		lda #$7d
		cmp cia1_port_a
		bne lC66F
		rts 

; jumped to by: smoke_follow
lC66F:
		lda #$00
		sta vic_sprite_coords + $e
		sta weapon_state
		rts 

; Writes "(c) coplin software" to screen row 23 in screen codes, every frame
; called by: frame_extras
print_credit:
		lda #$28
		sta credit_text
		lda #$03
		sta screen_ram + $39e
		lda #$29
		sta screen_ram + $39f
		lda #$03
		sta screen_ram + $3a1
		lda #$0f
		sta screen_ram + $3a2
		lda #$10
		sta screen_ram + $3a3
		lda #$0c
		sta screen_ram + $3a4
		lda #$09
		sta screen_ram + $3a5
		lda #$0e
		sta screen_ram + $3a6
		lda #$13
		sta screen_ram + $3a8
		lda #$0f
		sta screen_ram + $3a9
		lda #$06
		sta screen_ram + $3aa
		lda #$14
		sta screen_ram + $3ab
		lda #$17
		sta screen_ram + $3ac
		lda #$01
		sta screen_ram + $3ad
		lda #$12
		sta screen_ram + $3ae
		lda #$05
		sta screen_ram + $3af
		rts 

.virtual $c6ce
untouched_c6ce:
		.fill	6
.endv

*=$c6d4

; ---------------------------------------------------------------- sound
; sys50900: explosion, noise on voice 1 (also POKEd in from DATA lines 10000-)
sound_explosion:
		lda #$00
		sta sid_vol_filter
		sta voice1_control
		sta voice1_attack_decay
		lda #$0f
		sta sid_vol_filter
		lda #$81
		sta voice1_control
		lda #$88
		sta voice1_attack_decay
		lda #$28
		sta voice1_frequency + $1
		lda #$c8
		sta voice1_frequency
		rts 

; same as title_scroll; unused
unused_title_scroll:
		ldx vic_sprite_coords
		dex 
		dex 
		dex 
		stx vic_sprite_coords
		ldx vic_sprite_coords + $2
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $2
		ldx vic_sprite_coords + $4
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $4
		ldx vic_sprite_coords + $6
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $6
		rts 

.virtual $c71e
untouched_c71e:
		.fill	26
.endv

*=$c738

; sys51000: plays the next note of the tune on voice 2 (pulse).
; tune_pos is the offset before the next note, and BASIC starts it at 2: the
; first pass skips note 0. A pass ends at $e9, two notes past the end of the
; 76 note table (tune_overread).
tune_play:
		lda #$00
		sta voice2_attack_decay
		sta voice2_control
		lda #$0f
		sta sid_vol_filter
		lda #$09
		sta voice2_attack_decay
		lda #$41
		sta voice2_control
		lda #$00
		sta voice2_pulse_width + $1
		lda #$ff
		sta voice2_pulse_width
		ldx tune_pos
		inx 
		lda tune_notes, x
		sta voice2_frequency + $1
		inx 
		lda tune_notes, x
		sta voice2_frequency
		inx 
		lda tune_notes, x
		sta voice2_sustain_release
		stx tune_pos
		lda #$e9
		cmp tune_pos
		beq lC77C
		rts 

; jumped to by: tune_play
lC77C:
		lda #$5c
		sta tune_pos
		inc tune_loops
		lda #$05
		cmp tune_loops
		beq lC78C
		rts 

; jumped to by: tune_play
lC78C:
		lda #$02
		sta tune_pos
		sta tune_loops
		rts 

.virtual $c795
untouched_c795:
		.fill	105
.endv

*=$c7fe

; how often the tune has looped from $5c; after 3 loops it starts from the top
; read by: tune_play
; written by: tune_play
; modified by: tune_play
tune_loops:
		.byte	$02
; offset of the next note in tune_notes; 2 at the start, $e9 loops to $5c
; read by: tune_play
; written by: tune_play
tune_pos:		.byte	$74

; 76 notes: freq hi, freq lo, SR; DATA lines 10020-10038, POKEd to 51200
; read by: tune_play
tune_notes:
		.binary	"tune_notes.bin"

; power-on pattern past the table, read as the last two notes
tune_overread:
		.byte	$00, $ff, $00, $ff, $00, $ff

.virtual $c8ea
untouched_c8ea:
		.fill	22
unused_c900:
		.fill	444
.endv

*=$cabc

; ---------------------------------------------------------------- title
; sys51900: moves the title logo sprites 0-3 left 3 pixels
title_scroll:
		ldx vic_sprite_coords
		dex 
		dex 
		dex 
		stx vic_sprite_coords
		ldx vic_sprite_coords + $2
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $2
		ldx vic_sprite_coords + $4
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $4
		ldx vic_sprite_coords + $6
		dex 
		dex 
		dex 
		stx vic_sprite_coords + $6
		rts 

.virtual $cae1
unused_cae1:
		.fill	63
.endv

*=$cb20

; ---------------------------------------------------------------- sprite source
; Sprites the BASIC copies (lines 8000-8028) into the blocks at $0340 and $0840-$0dc0,
; 63 bytes each from 52000 on, but 63 to 65 bytes apart: 13 $cb20, 14 $cb5f, 15 $cb9f,
; 47 $cbde, 33 $cc1f, 34 $cc5f, 40-43 $cc9f, 46 $cd9f, 48-54 $cddf-$cf9e.
; The rewrite uses the copied blocks, so it shows what the original shows.
sprite_source:
		.byte	$01, $55, $40, $02, $aa, $80, $06, $aa, $90, $06, $aa, $90, $06, $aa, $90, $02
		.byte	$55, $80, $02, $aa, $80, $02, $aa, $80, $02, $aa, $80, $02, $aa, $80, $02, $55
		.byte	$80, $02, $55, $80, $02, $55, $80, $16, $aa, $94, $16, $eb, $94, $16, $eb, $94
		.byte	$01, $55, $40, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $02
		.byte	$aa, $80, $06, $aa, $90, $06, $aa, $90, $06, $aa, $90, $06, $aa, $90, $02, $55
		.byte	$80, $02, $55, $80, $02, $55, $80, $02, $55, $80, $02, $aa, $80, $06, $aa, $90
		.byte	$06, $aa, $90, $06, $28, $90, $02, $28, $80, $01, $55, $40, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$10, $00, $08, $04, $00, $0a, $01, $00, $0a, $00, $40, $0a, $00, $20, $0a, $82
		.byte	$90, $02, $aa, $a4, $00, $a9, $41, $00, $29, $50, $00, $11, $50, $00, $04, $00
		.byte	$00, $01, $00, $00, $00, $40, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $22
		.byte	$00, $00, $22, $00, $00, $2a, $80, $00, $2a, $80, $00, $aa, $80, $02, $aa, $a0
		.byte	$08, $aa, $a0, $08, $aa, $88, $02, $aa, $88, $0a, $aa, $88, $2a, $aa, $80, $22
		.byte	$aa, $82, $22, $aa, $22, $0a, $aa, $22, $08, $a0, $20, $08, $a0, $a0, $08, $88
		.byte	$a4, $0a, $88, $a4, $02, $28, $84, $00, $28, $04, $00, $20, $00, $00, $00, $0c
		.byte	$20, $00, $0a, $08, $00, $03, $80, $00, $0c, $c0, $00, $02, $2b, $e0, $00, $ce
		.byte	$28, $0a, $33, $c0, $0c, $36, $08, $03, $0b, $00, $08, $20, $00, $02, $3c, $00
		.byte	$00, $80, $c0, $02, $28, $00, $03, $f3, $c0, $00, $a0, $00, $00, $f3, $00, $00
		.byte	$00, $08, $00, $00, $00, $0c, $08, $20, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $ac, $00, $00, $b4, $00, $00
		.byte	$81, $40, $00, $f4, $14, $00, $b2, $41, $00, $00, $14, $00, $00, $01, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $82, $00, $00
		.byte	$c3, $00, $00, $82, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $82, $00, $00, $c3, $00
		.byte	$00, $82, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $82, $00, $00
		.byte	$c3, $00, $00, $82, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $82, $00, $00, $c3, $00, $00, $82
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $82, $00, $00, $c3, $00
		.byte	$00, $82, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $82, $00, $00
		.byte	$c3, $00, $00, $82, $00, $00, $82, $00, $00, $c3, $00, $00, $82, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $82, $00, $00, $c3, $00, $00, $82
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $08, $00, $00, $08, $00, $00, $08, $00, $00, $08, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01
		.byte	$55, $40, $02, $aa, $80, $2a, $aa, $a8, $2a, $aa, $a8, $2a, $aa, $a8, $02, $55
		.byte	$80, $02, $aa, $80, $02, $aa, $80, $02, $aa, $80, $02, $aa, $80, $02, $55, $80
		.byte	$02, $55, $80, $02, $55, $80, $2a, $aa, $a8, $2a, $eb, $a8, $2a, $eb, $a8, $01
		.byte	$55, $40, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $aa, $80, $00, $bf
		.byte	$80, $00, $bf, $80, $00, $bf, $80, $00, $bf, $80, $00, $bf, $80, $00, $bf, $80
		.byte	$00, $bf, $80, $00, $bf, $80, $00, $95, $80, $00, $95, $80, $00, $aa, $80, $00
		.byte	$2a, $00, $00, $2a, $00, $00, $08, $00, $00, $08, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $aa, $aa, $aa, $aa, $aa, $aa, $aa, $aa, $aa, $2a, $aa, $a8, $2a, $aa, $a8
		.byte	$2a, $aa, $a8, $0a, $aa, $a0, $0a, $aa, $a0, $0a, $aa, $a0, $02, $aa, $80, $02
		.byte	$aa, $80, $02, $aa, $80, $00, $82, $00, $00, $82, $00, $00, $82, $00, $00, $01
		.byte	$55, $40, $03, $ff, $c0, $07, $ff, $d0, $07, $ff, $d0, $07, $ff, $d0, $03, $55
		.byte	$c0, $03, $55, $c0, $03, $ff, $c0, $03, $ff, $c0, $03, $ff, $c0, $03, $ff, $c0
		.byte	$03, $ff, $c0, $03, $ff, $c0, $07, $ff, $d0, $07, $ff, $d0, $07, $ff, $d0, $03
		.byte	$ff, $d0, $07, $ff, $d0, $07, $ff, $d0, $07, $ff, $d0, $01, $55, $40, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $40, $f0
		.byte	$00, $c0, $0c, $3f, $00, $03, $ff, $ff, $fd, $3f, $ff, $fd, $0c, $3f, $c3, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $0f, $00, $00, $c3, $00, $30, $30, $00, $ff, $fc, $03, $15, $53, $03, $15
		.byte	$53, $3f, $14, $53, $3f, $14, $53, $3f, $14, $53, $3f, $14, $53, $3f, $14, $53
		.byte	$ff, $15, $53, $ff, $15, $53, $1f, $ff, $fc, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $ff, $ff, $03, $15
		.byte	$53, $ff, $00, $53, $ff, $00, $53, $ff, $01, $43, $ff, $05, $03, $ff, $05, $3f
		.byte	$ff, $05, $3f, $ff, $05, $3f, $ff, $ff, $ff, $3f, $ff, $ff, $00, $00, $00, $00
		.byte	$00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00

.virtual $cf9e
unused_cf9e:
		.fill	50
.endv

*=$cfd0

; ---------------------------------------------------------------- shared with BASIC
; 21 once the sprites are copied (53200); RUN again skips the copy
sprites_copied:
		.byte	$15

.virtual $cfd1
unused_cfd1:
		.fill	31
.endv

*=$cff0

; 1: turbo (F1), frame_update runs twice per sys49152 (53232)
; read by: turbo_check
; written by: turbo_on, turbo_off
turbo:
		.byte	$00
; 1: in the tunnel, the headlights follow the player (53233)
; read by: headlights_follow
headlights_on:		.byte	$00

.virtual $cff2
unused_cff2:		.byte	?
.endv

*=$cff3

; 1: crash_reset_check resets when the player is at the middle; BASIC never sets it
; read by: crash_reset_check
crash_reset_on:
		.byte	$00

.virtual $cff4
unused_cff4:
		.fill	5
.endv

*=$cff9

; enemy car directions 1-5, 0: off the road, BASIC respawns it (53241-53243)
; read by: frame_car1
; written by: car1_down_left5, car1_down_left2, car1_down, car1_down_right2, car1_down_right5, crash_reset
car1_direction:
		.byte	$02
; read by: frame_car2
; written by: car2_down_left5, car2_down_left3, car2_down, car2_down_right3, car2_down_right5, crash_reset
car2_direction:		.byte	$00
; read by: frame_car3
; written by: car3_down_left5, car3_down_left3, car3_down, car3_down_right3, car3_down_right5, crash_reset
car3_direction:		.byte	$04
; car from behind, direction 1-5, 0: gone (53244)
; read by: frame_car4, frame_car4_skip
; written by: car4_up_right5, car4_up_right3, car4_up, car4_up_left3, car4_up_left5, crash_reset
car4_direction:		.byte	$00
; 1 flying, 2 drop the bomb, 3 bomb falling, 0/4/5 off (53245)
; read by: frame_helicopter, $c18c
; written by: heli_drop_bomb, bomb_fall, crash_reset
heli_state:		.byte	$03
; 0 free, 1 guns, 2 missile, 3 smoke; 4 and 5 would skip frame_extras (53246)
; read by: weapon_update, $c1cb, fire_guns, fire_missile, fire_smoke
; written by: fire_guns, guns_animate, fire_missile, missile_fly, fire_smoke, unused_smoke_follow, crash_reset, smoke_follow
weapon_state:		.byte	$00

.virtual $cfff
unused_cfff:		.byte	?
; x and y of sprites 0-7
; read by: player_right, player_left, car1_down_left5, car1_down_left2, car1_down, car1_down_right2, car1_down_right5, car2_down_left5, car2_down_left3, car2_down, car2_down_right3, car2_down_right5, car3_down_left5, car3_down_left3, car3_down, car3_down_right3, car3_down_right5, car4_up_right5, car4_up_right3, car4_up, car4_up_left3, car4_up_left5, heli_fly, heli_drop_bomb, bomb_fall, headlights_follow, fire_guns, fire_missile, missile_fly, fire_smoke, unused_smoke_follow, crash_reset, smoke_follow, unused_title_scroll, title_scroll
; written by: player_right, player_left, car1_down_left5, car1_down_left2, car1_down, car1_down_right2, car1_down_right5, car2_down_left5, car2_down_left3, car2_down, car2_down_right3, car2_down_right5, car3_down_left5, car3_down_left3, car3_down, car3_down_right3, car3_down_right5, car4_up_right5, car4_up_right3, car4_up, car4_up_left3, car4_up_left5, heli_fly, heli_drop_bomb, bomb_fall, headlights_follow, fire_guns, fire_missile, missile_fly, fire_smoke, unused_smoke_follow, smoke_follow, unused_title_scroll, title_scroll
vic_sprite_coords:
		.fill	16
.endv

.virtual $d400
; written by: sound_explosion
voice1_frequency:		.word	?
.endv

.virtual $d404
; written by: sound_explosion
voice1_control:		.byte	?
; written by: sound_explosion
voice1_attack_decay:		.byte	?
.endv

.virtual $d407
; written by: tune_play
voice2_frequency:		.word	?
; written by: tune_play
voice2_pulse_width:		.word	?
; written by: tune_play
voice2_control:		.byte	?
; written by: tune_play
voice2_attack_decay:		.byte	?
; written by: tune_play
voice2_sustain_release:		.byte	?
.endv

.virtual $d418
; written by: sound_explosion, tune_play
sid_vol_filter:		.byte	?
.endv

.virtual $dc00
; keyboard columns, joystick port 2
; read by: joystick_controls, smoke_follow
cia1_port_a:		.byte	?
.endv

.virtual $e000
; ---------------------------------------------------------------- ROM
untouched_e000:
		.fill	7472
.endv

.virtual $fd50
untouched_fd50:
		.fill	688
.endv
