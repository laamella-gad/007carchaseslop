// The screens and the road's rows, drawn ahead as spans of screen codes
#ifndef TEXT_H
#define TEXT_H

// A table is rows, each a list of
//   row, column, colour, length, then that many screen codes
//   CLEAR, colour: the screen cleared
//   CLEAR_ROAD, colour: rows 0-19 cleared
// up to ROW_END. TABLE_END after the last row. INK as a colour is the colour play_rows_ink is given
#define ROW_END     0xff
#define TABLE_END   0xfe
#define CLEAR       0xfd
#define CLEAR_ROAD  0xfc
#define INK         0x40

extern const char country_start[];
extern const char country_a[];
extern const char country_b[];
extern const char city_top[];
extern const char city_sides[];
extern const char city_a[];
extern const char city_b[];
extern const char city_c[];
extern const char tunnel_in[];
extern const char tunnel_mouth[];
extern const char tunnel_start[];
extern const char tunnel_a[];
extern const char tunnel_b[];
extern const char left_curve_start[];
extern const char left_curve_a[];
extern const char left_curve_b[];
extern const char right_curve_start[];
extern const char right_curve_a[];
extern const char right_curve_b[];
extern const char bridge_start[];
extern const char bridge_a[];
extern const char bridge_b[];
extern const char title_page[];
extern const char car_page[];
extern const char controls_page[];
extern const char keys_page[];
extern const char aim_page[];
extern const char plan_page[];
extern const char credits_page[];

#pragma compile("text.c")

#endif
