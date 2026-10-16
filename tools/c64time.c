// c64time: runs the original game from the VICE snapshot on a small 6502 + C64
// model and reports how long each BASIC line takes, in PAL cycles, so the C
// rewrite can be paced like the original.
//
// The model: RAM, the BASIC and KERNAL ROMs, the VIC registers (raster, bad
// lines and sprite DMA steal cycles), CIA 1 timer A (the KERNAL's 60 Hz IRQ,
// no keys pressed), SID and colour RAM as plain registers.
//
// cc -O2 -o build/c64time tools/c64time.c
// build/c64time 007.vsf /usr/local/share/vice/C64 [seconds]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint64_t u64;

static u8 ram[65536], basic_rom[8192], kernal_rom[8192], io[4096];
static u8 a, x, y, sp, p;
static u16 pc;
static u64 now;                 // real cycles, including the ones the VIC steals
static u64 next_line;           // when the next raster line starts
static unsigned raster;
static unsigned key = 64;       // the matrix code of the key held down, 64: none
static u64 key_period, wait_period;
static int timer_a = 0x4025, latch_a = 0x4025, cia_icr, cia_mask = 0x81;

enum { C = 1, Z = 2, I = 4, D = 8, B = 16, U = 32, V = 64, N = 128 };

// ---------------------------------------------------------------- VIC timing

static void raster_line(void)
{
	unsigned stolen = 0;
	u8 d011 = io[0x11];
	if (raster >= 0x30 && raster <= 0xf7 && (raster & 7) == (d011 & 7) && (d011 & 0x10))
		stolen += 40;
	int sprites = 0;
	for (int i = 0; i < 8; i++)
		if (io[0x15] & (1 << i)) {
			unsigned sy = io[1 + 2 * i];
			unsigned h = (io[0x17] & (1 << i)) ? 42 : 21;
			if (raster >= sy && raster < sy + h)
				sprites++;
		}
	if (sprites)
		stolen += 3 + 2 * sprites;
	now += stolen;
	raster = (raster + 1) % 312;
}

static void tick(unsigned cycles)
{
	now += cycles;
	while (now >= next_line) {
		next_line += 63;
		raster_line();
	}
	// CIA 1 timer A counts every cycle
	static u64 last;
	u64 elapsed = now - last;
	last = now;
	timer_a -= (int)elapsed;
	while (timer_a < 0) {
		timer_a += latch_a + 1;
		cia_icr |= 0x01;
	}
}

// ---------------------------------------------------------------- memory

static u8 io_read(u16 addr)
{
	unsigned r = addr & 0xfff;
	if (r < 0x400) {
		r &= 0x3f;
		if (r == 0x12) return raster & 0xff;
		if (r == 0x11) return (io[0x11] & 0x7f) | ((raster & 0x100) ? 0x80 : 0);
		if (r == 0x1e || r == 0x1f) return 0;
		return io[r];
	}
	if (r < 0x800) {
		if ((r & 0x1f) == 0x1b) return rand();
		return 0;
	}
	if (r < 0xc00) return io[r] | 0xf0;
	if (r < 0xd00) {
		r &= 0x0f;
		if (r == 0x00) return io[0xc00] | 0x80;   // no joystick: bits as written
		if (r == 0x01) return key < 64 && !(io[0xc00] & (1 << (key >> 3))) ? ~(1 << (key & 7)) : 0xff;
		if (r == 0x04) return timer_a & 0xff;
		if (r == 0x05) return timer_a >> 8;
		if (r == 0x0d) {
			u8 v = cia_icr | ((cia_icr & cia_mask & 0x1f) ? 0x80 : 0);
			cia_icr = 0;
			return v;
		}
		return io[0xc00 + r];
	}
	return io[r];
}

static void io_write(u16 addr, u8 v)
{
	unsigned r = addr & 0xfff;
	if (r < 0x400) { io[r & 0x3f] = v; return; }
	if (r >= 0xc00 && r < 0xd00) {
		r &= 0x0f;
		if (r == 0x04) latch_a = (latch_a & 0xff00) | v;
		else if (r == 0x05) latch_a = (latch_a & 0x00ff) | (v << 8);
		else if (r == 0x0d) {
			if (v & 0x80) cia_mask |= v & 0x1f; else cia_mask &= ~v;
		}
		io[0xc00 + r] = v;
		return;
	}
	io[r] = v;
}

static u8 rd(u16 addr)
{
	u8 port = ram[1] | ~ram[0];
	if (addr >= 0xa000 && addr < 0xc000 && (port & 3) == 3) return basic_rom[addr - 0xa000];
	if (addr >= 0xe000 && (port & 2)) return kernal_rom[addr - 0xe000];
	if (addr >= 0xd000 && addr < 0xe000 && (port & 3) && (port & 4)) return io_read(addr);
	return ram[addr];
}

static void wr(u16 addr, u8 v)
{
	u8 port = ram[1] | ~ram[0];
	if (addr >= 0xd000 && addr < 0xe000 && (port & 3) && (port & 4)) { io_write(addr, v); return; }
	ram[addr] = v;
}

// ---------------------------------------------------------------- 6502

static unsigned extra;          // page-crossing cycles of the current instruction

static void push(u8 v) { wr(0x100 + sp--, v); }
static u8 pull(void) { return rd(0x100 + ++sp); }
static u16 rd16(u16 a_) { return rd(a_) | (rd(a_ + 1) << 8); }
static u16 rd16zp(u8 a_) { return rd(a_) | (rd((u8)(a_ + 1)) << 8); }
static void nz(u8 v) { p = (p & ~(N | Z)) | (v & N) | (v ? 0 : Z); }

static u16 imm(void) { return pc++; }
static u16 zp(void) { return rd(pc++); }
static u16 zpx(void) { return (u8)(rd(pc++) + x); }
static u16 zpy(void) { return (u8)(rd(pc++) + y); }
static u16 abso(void) { u16 r = rd16(pc); pc += 2; return r; }
static u16 absx(void) { u16 b = rd16(pc); pc += 2; u16 r = b + x; if ((b ^ r) & 0xff00) extra = 1; return r; }
static u16 absy(void) { u16 b = rd16(pc); pc += 2; u16 r = b + y; if ((b ^ r) & 0xff00) extra = 1; return r; }
static u16 indx(void) { return rd16zp(rd(pc++) + x); }
static u16 indy(void) { u16 b = rd16zp(rd(pc++)); u16 r = b + y; if ((b ^ r) & 0xff00) extra = 1; return r; }

static void adc(u8 v)
{
	if (p & D) {
		unsigned lo = (a & 15) + (v & 15) + (p & C);
		unsigned hi = (a >> 4) + (v >> 4);
		if (lo > 9) { lo += 6; hi++; }
		u8 bin = a + v + (p & C);
		p &= ~(N | V | Z | C);
		if (!bin) p |= Z;
		if (hi & 8) p |= N;
		if (~(a ^ v) & (a ^ (hi << 4)) & 0x80) p |= V;
		if (hi > 9) { hi += 6; p |= C; }
		a = (hi << 4) | (lo & 15);
		return;
	}
	unsigned s = a + v + (p & C);
	p &= ~(V | C);
	if (~(a ^ v) & (a ^ s) & 0x80) p |= V;
	if (s > 0xff) p |= C;
	a = s;
	nz(a);
}

static void sbc(u8 v)
{
	if (p & D) {
		int lo = (a & 15) - (v & 15) - !(p & C);
		int hi = (a >> 4) - (v >> 4);
		unsigned s = a - v - !(p & C);
		if (lo < 0) { lo -= 6; hi--; }
		if (hi < 0) hi -= 6;
		p &= ~(V | C);
		if ((a ^ v) & (a ^ s) & 0x80) p |= V;
		if (s < 0x100) p |= C;
		a = ((hi & 15) << 4) | (lo & 15);
		nz((u8)s);
		return;
	}
	adc(~v);
}

static void cmp(u8 r, u8 v) { unsigned s = r - v; p = (p & ~C) | (r >= v ? C : 0); nz(s); }
static void branch(int cond)
{
	int8_t o = rd(pc++);
	if (cond) {
		u16 t = pc + o;
		tick((t ^ pc) & 0xff00 ? 2 : 1);
		pc = t;
	}
}
static u8 asl(u8 v) { p = (p & ~C) | (v >> 7); v <<= 1; nz(v); return v; }
static u8 lsr(u8 v) { p = (p & ~C) | (v & 1); v >>= 1; nz(v); return v; }
static u8 rol(u8 v) { u8 c = p & C; p = (p & ~C) | (v >> 7); v = (v << 1) | c; nz(v); return v; }
static u8 ror(u8 v) { u8 c = p & C; p = (p & ~C) | (v & 1); v = (v >> 1) | (c << 7); nz(v); return v; }

static u8 INC(u8 v) { v++; nz(v); return v; }
static u8 DEC(u8 v) { v--; nz(v); return v; }

static void interrupt(u16 vector, int brk)
{
	push(pc >> 8); push(pc); push(brk ? (p | U | B) : ((p | U) & ~B));
	p |= I;
	pc = rd16(vector);
	tick(7);
}

#define RMW(addrmode, op, cyc) { u16 t = addrmode(); u8 v = rd(t); wr(t, op(v)); tick(cyc); } break
#define LD(reg, addrmode, cyc) { u16 t = addrmode(); reg = rd(t); nz(reg); tick(cyc + extra); } break

static void step(void)
{
	extra = 0;
	u8 op = rd(pc++);
	switch (op) {
	// loads and stores
	case 0xa9: LD(a, imm, 2); case 0xa5: LD(a, zp, 3); case 0xb5: LD(a, zpx, 4); case 0xad: LD(a, abso, 4);
	case 0xbd: LD(a, absx, 4); case 0xb9: LD(a, absy, 4); case 0xa1: LD(a, indx, 6); case 0xb1: LD(a, indy, 5);
	case 0xa2: LD(x, imm, 2); case 0xa6: LD(x, zp, 3); case 0xb6: LD(x, zpy, 4); case 0xae: LD(x, abso, 4); case 0xbe: LD(x, absy, 4);
	case 0xa0: LD(y, imm, 2); case 0xa4: LD(y, zp, 3); case 0xb4: LD(y, zpx, 4); case 0xac: LD(y, abso, 4); case 0xbc: LD(y, absx, 4);
	case 0x85: wr(zp(), a); tick(3); break; case 0x95: wr(zpx(), a); tick(4); break;
	case 0x8d: wr(abso(), a); tick(4); break; case 0x9d: wr(absx(), a); tick(5); break;
	case 0x99: wr(absy(), a); tick(5); break; case 0x81: wr(indx(), a); tick(6); break; case 0x91: wr(indy(), a); tick(6); break;
	case 0x86: wr(zp(), x); tick(3); break; case 0x96: wr(zpy(), x); tick(4); break; case 0x8e: wr(abso(), x); tick(4); break;
	case 0x84: wr(zp(), y); tick(3); break; case 0x94: wr(zpx(), y); tick(4); break; case 0x8c: wr(abso(), y); tick(4); break;
	// transfers
	case 0xaa: x = a; nz(x); tick(2); break; case 0xa8: y = a; nz(y); tick(2); break;
	case 0x8a: a = x; nz(a); tick(2); break; case 0x98: a = y; nz(a); tick(2); break;
	case 0xba: x = sp; nz(x); tick(2); break; case 0x9a: sp = x; tick(2); break;
	// stack
	case 0x48: push(a); tick(3); break; case 0x08: push(p | B | U); tick(3); break;
	case 0x68: a = pull(); nz(a); tick(4); break; case 0x28: p = pull() | U; tick(4); break;
	// arithmetic
#define ALU(base, fn) \
	case base + 0x09: { u16 t = imm(); fn(rd(t)); tick(2); } break; \
	case base + 0x05: { u16 t = zp(); fn(rd(t)); tick(3); } break; \
	case base + 0x15: { u16 t = zpx(); fn(rd(t)); tick(4); } break; \
	case base + 0x0d: { u16 t = abso(); fn(rd(t)); tick(4); } break; \
	case base + 0x1d: { u16 t = absx(); fn(rd(t)); tick(4 + extra); } break; \
	case base + 0x19: { u16 t = absy(); fn(rd(t)); tick(4 + extra); } break; \
	case base + 0x01: { u16 t = indx(); fn(rd(t)); tick(6); } break; \
	case base + 0x11: { u16 t = indy(); fn(rd(t)); tick(5 + extra); } break;
#define ORA(v) (a |= (v), nz(a))
#define AND(v) (a &= (v), nz(a))
#define EOR(v) (a ^= (v), nz(a))
#define CMPA(v) cmp(a, v)
	ALU(0x00, ORA) ALU(0x20, AND) ALU(0x40, EOR) ALU(0x60, adc) ALU(0xc0, CMPA) ALU(0xe0, sbc)
	case 0xe0: cmp(x, rd(imm())); tick(2); break; case 0xe4: cmp(x, rd(zp())); tick(3); break; case 0xec: cmp(x, rd(abso())); tick(4); break;
	case 0xc0: cmp(y, rd(imm())); tick(2); break; case 0xc4: cmp(y, rd(zp())); tick(3); break; case 0xcc: cmp(y, rd(abso())); tick(4); break;
	case 0x24: { u8 v = rd(zp()); p = (p & ~(N | V | Z)) | (v & (N | V)) | ((a & v) ? 0 : Z); tick(3); } break;
	case 0x2c: { u8 v = rd(abso()); p = (p & ~(N | V | Z)) | (v & (N | V)) | ((a & v) ? 0 : Z); tick(4); } break;
	// increments
	case 0xe6: RMW(zp, INC, 5); case 0xf6: RMW(zpx, INC, 6); case 0xee: RMW(abso, INC, 6); case 0xfe: RMW(absx, INC, 7);
	case 0xc6: RMW(zp, DEC, 5); case 0xd6: RMW(zpx, DEC, 6); case 0xce: RMW(abso, DEC, 6); case 0xde: RMW(absx, DEC, 7);
	case 0xe8: x++; nz(x); tick(2); break; case 0xca: x--; nz(x); tick(2); break;
	case 0xc8: y++; nz(y); tick(2); break; case 0x88: y--; nz(y); tick(2); break;
	// shifts
	case 0x0a: a = asl(a); tick(2); break; case 0x4a: a = lsr(a); tick(2); break;
	case 0x2a: a = rol(a); tick(2); break; case 0x6a: a = ror(a); tick(2); break;
	case 0x06: RMW(zp, asl, 5); case 0x16: RMW(zpx, asl, 6); case 0x0e: RMW(abso, asl, 6); case 0x1e: RMW(absx, asl, 7);
	case 0x46: RMW(zp, lsr, 5); case 0x56: RMW(zpx, lsr, 6); case 0x4e: RMW(abso, lsr, 6); case 0x5e: RMW(absx, lsr, 7);
	case 0x26: RMW(zp, rol, 5); case 0x36: RMW(zpx, rol, 6); case 0x2e: RMW(abso, rol, 6); case 0x3e: RMW(absx, rol, 7);
	case 0x66: RMW(zp, ror, 5); case 0x76: RMW(zpx, ror, 6); case 0x6e: RMW(abso, ror, 6); case 0x7e: RMW(absx, ror, 7);
	// jumps
	case 0x4c: pc = rd16(pc); tick(3); break;
	case 0x6c: { u16 t = rd16(pc); pc = rd(t) | (rd((t & 0xff00) | ((t + 1) & 0xff)) << 8); tick(5); } break;
	case 0x20: { u16 t = rd16(pc); pc++; push(pc >> 8); push(pc); pc = t; tick(6); } break;
	case 0x60: pc = pull(); pc |= pull() << 8; pc++; tick(6); break;
	case 0x40: p = pull() | U; pc = pull(); pc |= pull() << 8; tick(6); break;
	case 0x00: pc++; interrupt(0xfffe, 1); break;
	// branches
	case 0x10: branch(!(p & N)); tick(2); break; case 0x30: branch(p & N); tick(2); break;
	case 0x50: branch(!(p & V)); tick(2); break; case 0x70: branch(p & V); tick(2); break;
	case 0x90: branch(!(p & C)); tick(2); break; case 0xb0: branch(p & C); tick(2); break;
	case 0xd0: branch(!(p & Z)); tick(2); break; case 0xf0: branch(p & Z); tick(2); break;
	// flags
	case 0x18: p &= ~C; tick(2); break; case 0x38: p |= C; tick(2); break;
	case 0x58: p &= ~I; tick(2); break; case 0x78: p |= I; tick(2); break;
	case 0xb8: p &= ~V; tick(2); break; case 0xd8: p &= ~D; tick(2); break; case 0xf8: p |= D; tick(2); break;
	case 0xea: tick(2); break;
	default:
		fprintf(stderr, "illegal opcode $%02x at $%04x\n", op, pc - 1);
		exit(1);
	}
}

// ---------------------------------------------------------------- snapshot

static const u8 *module(const u8 *d, long size, const char *name)
{
	for (long i = 0; i + 16 < size; i++)
		if (!memcmp(d + i, name, strlen(name)) && d[i + strlen(name)] == 0)
			return d + i + 22;
	fprintf(stderr, "no %s module\n", name);
	exit(1);
}

static void load(const char *path, u8 *dst, long n)
{
	FILE *f = fopen(path, "rb");
	if (!f || fread(dst, 1, n, f) != (size_t)n) { fprintf(stderr, "can't read %s\n", path); exit(1); }
	fclose(f);
}

// ---------------------------------------------------------------- shadow printer
// The simple PETSCII printer the rewrite uses: no logical lines, no quote mode.
// It follows the KERNAL's screen output ($e716) on a copy of the screen, and each
// BASIC line's result is compared with what the KERNAL drew.

static u8 sh_screen[1000], sh_colour[1000];
static int sh_row, sh_col, sh_rvs, sh_ink, sh_used;
static unsigned unknown_codes[256];

static void sh_scroll(void)
{
	memmove(sh_screen, sh_screen + 40, 960);
	memmove(sh_colour, sh_colour + 40, 960);
	memset(sh_screen + 960, ' ', 40);
	memset(sh_colour + 960, sh_ink, 40);
	sh_row = 24;
}

static void sh_down(void) { if (++sh_row > 24) sh_scroll(); }

static const signed char colour_codes[256] = {
	[0x05] = 1 + 1, [0x1c] = 2 + 1, [0x1e] = 5 + 1, [0x1f] = 6 + 1, [0x81] = 8 + 1, [0x90] = 0 + 1,
	[0x95] = 9 + 1, [0x96] = 10 + 1, [0x97] = 11 + 1, [0x98] = 12 + 1, [0x99] = 13 + 1, [0x9a] = 14 + 1,
	[0x9b] = 15 + 1, [0x9c] = 4 + 1, [0x9e] = 7 + 1, [0x9f] = 3 + 1,
};

static void sh_put(u8 c)
{
	sh_used = 1;
	if (colour_codes[c]) { sh_ink = colour_codes[c] - 1; return; }
	switch (c) {
	case 0x0d: case 0x8d: sh_col = 0; sh_rvs = 0; sh_down(); return;
	case 0x13: sh_row = sh_col = 0; return;
	case 0x93:
		memset(sh_screen, ' ', 1000); memset(sh_colour, sh_ink, 1000);
		sh_row = sh_col = 0; return;
	case 0x11: sh_down(); return;
	case 0x91: if (sh_row) sh_row--; return;
	case 0x1d: if (++sh_col == 40) { sh_col = 0; sh_down(); } return;
	case 0x9d: if (sh_col) sh_col--; else if (sh_row) { sh_col = 39; sh_row--; } return;
	case 0x12: sh_rvs = 0x80; return;
	case 0x92: sh_rvs = 0; return;
	}
	u8 sc;
	if (c >= 0x20 && c < 0x40) sc = c;
	else if (c >= 0x40 && c < 0x60) sc = c - 0x40;
	else if (c >= 0x60 && c < 0x80) sc = c - 0x20;
	else if (c >= 0xa0 && c < 0xc0) sc = c - 0x40;
	else if (c >= 0xc0 && c < 0xff) sc = c - 0x80;
	else if (c == 0xff) sc = 0x5e;
	else { unknown_codes[c]++; return; }
	sh_screen[sh_row * 40 + sh_col] = sc | sh_rvs;
	sh_colour[sh_row * 40 + sh_col] = sh_ink;
	if (++sh_col == 40) { sh_col = 0; sh_down(); }
}

static void sh_start(void)
{
	memcpy(sh_screen, ram + 0x400, 1000);
	for (int i = 0; i < 1000; i++) sh_colour[i] = io[0x800 + i] & 15;
	sh_row = ram[0xd6];
	sh_col = ram[0xd3] % 40;
	sh_ink = ram[0x286] & 15;
	sh_rvs = ram[0xc7] ? 0x80 : 0;
	sh_used = 0;
}

static unsigned sh_lines_ok[65536], sh_lines_bad[65536], sh_cells_bad[65536];

static void sh_check(u16 line)
{
	if (!sh_used) return;
	// print_credit writes row 23, columns 5-23, every frame
	for (int i = 23 * 40 + 5; i <= 23 * 40 + 23; i++) { sh_screen[i] = ram[0x400 + i]; sh_colour[i] = io[0x800 + i] & 15; }
	unsigned bad = 0;
	for (int i = 0; i < 1000; i++)
		if (sh_screen[i] != ram[0x400 + i] || sh_colour[i] != (io[0x800 + i] & 15)) bad++;
	static int dumped;
	if (bad && dumped < 3) {
		dumped++;
		fprintf(stderr, "line %u: %u cells\n", line, bad);
		for (int i = 0; i < 1000; i++)
			if (sh_screen[i] != ram[0x400 + i] || sh_colour[i] != (io[0x800 + i] & 15))
				fprintf(stderr, "  row %2d col %2d: shadow %02x/%x real %02x/%x\n", i / 40, i % 40,
					sh_screen[i], sh_colour[i], ram[0x400 + i], io[0x800 + i] & 15);
	}
	if (bad) { sh_lines_bad[line]++; if (bad > sh_cells_bad[line]) sh_cells_bad[line] = bad; }
	else sh_lines_ok[line]++;
}

// ---------------------------------------------------------------- report

static u8 vsf[1 << 20];
static long vsf_size;

// Puts the machine back in the snapshot's state
static void restore(void)
{
	long size = vsf_size;
	const u8 *cpu = module(vsf, size, "MAINCPU");
	// clock (8), A, X, Y, SP, PC, P
	a = cpu[8]; x = cpu[9]; y = cpu[10]; sp = cpu[11]; pc = cpu[12] | (cpu[13] << 8); p = cpu[14] | U;
	const u8 *mem = module(vsf, size, "C64MEM");
	// the CPU port's data ($01) and direction ($00), 2 bytes, then the RAM
	memcpy(ram, mem + 4, 65536);
	ram[1] = mem[0]; ram[0] = mem[1];
	const u8 *vic = module(vsf, size, "VIC-II");
	memcpy(io, vic + 1, 0x40);

}

static unsigned stops[65536];
static u8 stop_x[65536];
static u8 line_sp;
static u64 line_open[65536];
static u64 line_cycles[65536], line_count[65536], line_min[65536], line_max[65536];

int main(int argc, char **argv)
{
	if (argc < 3) { fprintf(stderr, "usage: c64time game.vsf romdir [seconds]\n"); return 1; }
	double seconds = argc > 3 ? atof(argv[3]) : 120;
	char path[1024];
	snprintf(path, sizeof path, "%s/basic-901226-01.bin", argv[2]); load(path, basic_rom, 8192);
	snprintf(path, sizeof path, "%s/kernal-901227-03.bin", argv[2]); load(path, kernal_rom, 8192);

	FILE *f = fopen(argv[1], "rb");
	long size = fread(vsf, 1, sizeof vsf, f);
	fclose(f);
	vsf_size = size;
	restore();

	u64 end = (u64)(seconds * 985248);
	u16 line = 0xffff;
	u64 line_start = 0;
	u64 frames = 0, title_frames = 0, restarts = 0;
	for (int i = 0; i < 65536; i++) line_min[i] = ~0ull;
	while (now < end) {
		if ((cia_icr & cia_mask & 0x1f) && !(p & I))
			interrupt(0xfffe, 0);
		if (pc == 0xc003) frames++;
		if (pc == 0xcabc) title_frames++;
		u16 l = ram[0x39] | (ram[0x3a] << 8);
		if (l != line && ram[0x3a] != 0xff) {
			if (line != 0xffff) {
				u64 c = now - line_start;
				line_cycles[line] += c; line_open[line] += c;
				// a GOSUB leaves its frame (token $8d) on the stack: the line goes on after the
				// RETURN, so it isn't done yet. The subroutine's lines count on their own
				if (!(sp < line_sp && ram[0x100 + (u8)(sp + 1)] == 0x8d)) {
					line_count[line]++;
					c = line_open[line]; line_open[line] = 0;
					if (c < line_min[line]) line_min[line] = c;
					if (c > line_max[line]) line_max[line] = c;
				}
			}
			line_sp = sp;
			if (line != 0xffff) sh_check(line);
			line = l;
			line_start = now;
			sh_start();
		}
		if (pc == 0xe716) sh_put(a);
		// the game ENDs when a score ties the high score table: start again
		if (line == 20049) { memset(line_open, 0, sizeof line_open); restore(); restarts++; line = 0xffff; continue; }
		// stopped by an error: back to READY
		if (pc == 0xa474 && line != 0xffff) { memset(line_open, 0, sizeof line_open); stops[line]++; stop_x[line] = io[0]; restore(); line = 0xffff; continue; }
		// press a key where the game waits for one
		if (now / 100000 != wait_period) {
			wait_period = now / 100000;
			if (ram[0xc6] == 0 && rand() % 10 == 0) {
				if (line == 11070 || line == 11069) { ram[0x277] = rand() % 3 ? ' ' : 'I'; ram[0xc6] = 1; }
				if (line == 12035 || line == 12067 || line == 12090 || line == 12190) { ram[0x277] = ' '; ram[0xc6] = 1; }
				if (line == 20060) { ram[0x277] = 'A'; ram[0x278] = 13; ram[0xc6] = 2; }
				if (line == 20071) { ram[0x277] = ' '; ram[0xc6] = 1; }
			}
		}
		// a random key now and then: M, Z, SPACE, '.', ',' or none
		if (now / 400000 != key_period) {
			static const u8 keys[] = { 0x24, 0x24, 0x0c, 0x0c, 0x3c, 0x2c, 0x2f, 0x40, 0x40, 0x40 };
			key_period = now / 400000;
			key = keys[rand() % sizeof keys];
		}
		step();
	}
	printf("# %.0f s, %llu frame_update calls, %llu title_scroll calls\n", seconds,
	       (unsigned long long)frames, (unsigned long long)title_frames);
	printf("# line passes avg min max (PAL cycles per pass, without the subroutines it calls)\n");
	for (int i = 0; i < 65536; i++)
		if (line_count[i])
			printf("%5d %6llu %7llu %7llu %7llu\n", i, (unsigned long long)line_count[i],
			       (unsigned long long)(line_cycles[i] / line_count[i]),
			       (unsigned long long)line_min[i], (unsigned long long)line_max[i]);
	printf("# last line %u, pc $%04x, %llu restarts at line 20049\n", line, pc, (unsigned long long)restarts);
	printf("# curlin %02x%02x oldlin %02x%02x txtptr %02x%02x\n", ram[0x3a], ram[0x39], ram[0x3c], ram[0x3b], ram[0x7b], ram[0x7a]);
	for (int r = 0; r < 25; r++) {
		printf("# |");
		for (int c = 0; c < 40; c++) {
			u8 v = ram[0x400 + r * 40 + c] & 0x7f;
			putchar(v < 32 ? v + 64 : v < 64 ? v : '.');
		}
		printf("|\n");
	}
	for (int i = 0; i < 65536; i++)
		if (stops[i]) printf("# stopped by an error in line %d: %u times, last with x0 %u\n", i, stops[i], stop_x[i]);
	printf("# shadow printer: line ok bad max_cells_bad\n");
	for (int i = 0; i < 65536; i++)
		if (sh_lines_bad[i])
			printf("S %5d %6u %6u %4u\n", i, sh_lines_ok[i], sh_lines_bad[i], sh_cells_bad[i]);
	for (int i = 0; i < 256; i++)
		if (unknown_codes[i]) printf("U $%02x %u\n", i, unknown_codes[i]);
	return 0;
}
