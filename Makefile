OSCAR64 ?= oscar64
X64 ?= x64sc
PUCRUNCH ?= pucrunch

all: 007carchase.prg

# src/main.c includes the other sources
build/007carchase_raw.prg: src/*.c src/*.h src/*.bin
	mkdir -p build
	$(OSCAR64) -n -O2 -o=$@ src/main.c
	python3 tools/branchcheck.py build/007carchase_raw.asm || (rm $@; false)

# The released PRG, checked in. Starts at the oscar64 startup code after the
# BASIC SYS line ($080d)
007carchase.prg: build/007carchase_raw.prg
	$(PUCRUNCH) -c64 -x0x080d $< $@

# Times the original's BASIC lines in an emulator, from the snapshot (takes minutes)
build/c64time: tools/c64time.c
	mkdir -p build
	cc -O2 -o $@ $<

timing: build/c64time
	build/c64time 007.vsf /usr/local/share/vice/C64 20000 > build/timing.txt 2>/dev/null

# The strings, the row tables and the line times from the original
text: 007.bas build/timing.txt
	python3 tools/bas2c.py 007.bas build/timing.txt src

run: 007carchase.prg
	$(X64) -sound $<

clean:
	rm -rf build/007carchase_raw.*

.PHONY: all timing text run clean
