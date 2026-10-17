// Made by tools/bas2c.py (deleted, in the git history) from 007.bas and the
// timing run; edited by hand now
#ifndef TEXT_H
#define TEXT_H

// cells: what the PRINT writes, for print_cells; tune: the line plays the
// tune first (sys51000)
typedef struct {
	const char *cells;
	char tune;
} Row;

extern const Row rows_91[2];	// lines 91-92
extern const Row rows_189[6];	// lines 189-194
extern const Row rows_200[15];	// lines 200-214
extern const Row rows_220[15];	// lines 220-234
extern const Row rows_381[7];	// lines 381-387
extern const Row rows_391[8];	// lines 391-398
extern const Row rows_401[6];	// lines 401-406
extern const Row rows_420[15];	// lines 420-434
extern const Row rows_451[21];	// lines 451-471
extern const Row rows_500[5];	// lines 500-504
extern const Row rows_510[7];	// lines 510-517
extern const Row rows_520[9];	// lines 520-528
extern const Row rows_794[20];	// lines 794-814
extern const Row rows_820[15];	// lines 820-834
extern const Row rows_1001[6];	// lines 1001-1006
extern const Row rows_1010[15];	// lines 1010-1024
extern const Row rows_1030[15];	// lines 1030-1044
extern const Row rows_1101[6];	// lines 1101-1106
extern const Row rows_1110[15];	// lines 1110-1124
extern const Row rows_1130[15];	// lines 1130-1144
extern const Row rows_2100[5];	// lines 2100-2105
extern const Row rows_2200[15];	// lines 2200-2214
extern const Row rows_2220[15];	// lines 2220-2234
extern const Row rows_6011[2];	// lines 6011-6012
extern const Row rows_11010[12];	// lines 11010-11021
extern const Row rows_12020[14];	// lines 12020-12034
extern const Row rows_12041[18];	// lines 12041-12066
extern const Row rows_12070[13];	// lines 12070-12089
extern const Row rows_12101[7];	// lines 12101-12107
extern const Row rows_12112[5];	// lines 12112-12189
extern const Row rows_12401[9];	// lines 12401-12417

#pragma compile("text.c")

#endif
