OSCAR64 ?= oscar64
X64 ?= x64sc
PUCRUNCH ?= pucrunch

all: 007carchase.prg

# src/main.c includes the other sources
build/007carchase_raw.prg: src/*.c src/*.h src/*.bin
	mkdir -p build
	$(OSCAR64) -n -O2 -o=$@ src/main.c

# The released PRG, checked in. Starts at the oscar64 startup code after the
# BASIC SYS line ($080d)
007carchase.prg: build/007carchase_raw.prg
	$(PUCRUNCH) -c64 -x0x080d $< $@

run: 007carchase.prg
	$(X64) -sound $<

clean:
	rm -rf build/007carchase_raw.*

.PHONY: all run clean
