# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

Reverse-engineering workspace for "007 Car Chase" (c) Coplin Software, a Commodore 64 game. No git, no tests. Original disk image is `007CARCH.d64`; everything else was extracted from it or derived from those extracts.

## Files

- `007CARCH.d64` — original disk. Contains three PRGs: `007 car chase`, `007.bas`, `007`.
- `007 car chase` — tokenized BASIC loader at $0801. Shows title screen, sets BASIC start to $1000 (`poke 44,16`), then stuffs the keyboard buffer to `LOAD"007.BAS",8` + `RUN`.
- `007.bas` — tokenized main game BASIC at $1001 (`file` misreports it as C16/Plus4 because of the load address; it is C64 BASIC V2).
- `07.bas` — `petcat` text listing of `007.bas`. Read/grep this, not the binary.
- `007` — machine-code PRG loaded at $C000 (`load"007",8,1` on line 0 of `007.bas`). Original from disk.
- `007.prg` — Makefile output name; currently a 4096-byte file that differs from `007` in ~358 bytes. Treat `007` as the reference binary.
- `code.asm` — **raw copy-paste of a WFDis (web 6502 disassembler) session**, not valid 64tass source. It begins with the WFDis UI help text, has no `* = $c000`, uses undefined symbolic names like `d002_vSprite1X`, and data regions are bare hex rows rather than `.byte`. Needs cleanup before it can assemble.
- `1.bin`, `2.bin` — small raw dumps (screen-code / sprite-like data).
- `vice-snapshot-*.vsf` — VICE snapshot of the running game.

## Commands

```sh
make                      # 64tass -C -a -B -i code.asm -o 007.prg  (fails today: see code.asm note)
petcat -2 -- 007.bas      # detokenize BASIC (same as 07.bas)
petcat -w2 -l 1001 -o 007.bas -- 07.bas   # retokenize; byte-identical round-trip (must load at $1001)
c1541 -attach 007CARCH.d64 -list  # list disk; -read / -write to extract/replace files
x64sc 007CARCH.d64        # run in VICE (LOAD"*",8 then RUN)
```

To verify a rebuilt binary, `cmp` it against `007` (both carry a 2-byte $C000 load address header).
The `demo.prg` Makefile target is leftover boilerplate; its sources do not exist.

## Architecture

The game is a BASIC program driving a machine-code helper library. Game logic (collision checks, scoring, lives, level flow) lives in BASIC; the ML at $C000 does joystick/keyboard reading, sprite movement, scrolling and sound.

ML entry points called from BASIC (`grep -i sys 07.bas`):
- `SYS 49152` ($C000) → `jmp $C52B`, init/main routine
- `SYS 49155` ($C003) — per-frame routine: reads key in $C5, then dispatches on state bytes $CFF9–$CFFE to sprite-movement subroutines
- `SYS 49561` ($C199), `SYS 50900` ($C6D4), `SYS 51000` ($C738), `SYS 51900` ($CABC) — other helpers

BASIC also self-modifies the ML with POKEs (e.g. `poke49173,234` ×3 NOPs out code at $C015; `poke49630..49633` patches $C1DE–$C1E1), so the binary on disk is not exactly what runs.

**Shared state block $CFD0–$CFFF** (53200–53247) is the BASIC↔ML mailbox. BASIC PEEK/POKEs these by decimal address, ML uses `$cffX`. Key ones: $CFF9–$CFFE (direction/state flags, 53241–53246), $CFF0 (53232, used in score calc at line 18), $CFD0 (53200). When tracing behavior, correlate decimal addresses in `07.bas` with hex in `code.asm`.

Other conventions in BASIC: `v=53248` (VIC base, so `v+N` = VIC registers); sprite pointers at 2040–2047; sprite shapes copied from ML data at 52000+ into 832 (`gosub 8000`).
