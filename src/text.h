// The screens and the road, as pictures
#ifndef TEXT_H
#define TEXT_H

// A table is lines of a picture, each drawn from column 0 of its row, up to
// LINES_END: the characters, and their colours as runs. A run is a colour
// letter and how many characters it covers (the last one: to the end):
//   k black, w white, r red, c cyan, g green, b blue, y yellow, n brown,
//   d dark grey, m grey, l light grey
//   * the colour play_rows_ink is given
//   . the characters stay as they are on the screen
// The characters are A-Z, the digits, space and punctuation as they are, and
// stand-ins for the graphics:
//   #  solid block                    _  lower half
//   /  upper left triangle            ^  upper seven eighths
//   \  upper right triangle           z  checker quarters
//   d  lower right triangle           m  lower left quarter
//   b  lower left triangle            n  lower right quarter
//   +  cross                          ~  horizontal line
//   %  checkerboard                   t  top line
//   h  lower half checkerboard        u  upper quarter
//   c  left half checkerboard         f  lower quarter
//   |  vertical line                  o  corner, top left
//   x  diagonal, down to the right    p  corner, top right
//   y  diagonal, up to the right      l  corner, bottom left
//   q  slash                          j  corner, bottom right
//   [  left bar                       e  T, right
//   ]  right bar                      s  T, left
//   !  left bar, the same             i  T, down
//   {  left half                      w  T, up
//   }  left three eighths             a  up arrow
//   k  right three eighths
typedef struct {
	char row;
	const char *chars, *colours;
} Line;

#define LINES_END {0xff}

#define GLYPHS 37
extern const char glyphs[GLYPHS][2];

extern const Line country_start[];
extern const Line country_a[];
extern const Line country_b[];
extern const Line city_top[];
extern const Line city_sides[];
extern const Line city_a[];
extern const Line city_b[];
extern const Line city_c[];
extern const Line tunnel_in[];
extern const Line tunnel_mouth[];
extern const Line tunnel_start[];
extern const Line tunnel_a[];
extern const Line tunnel_b[];
extern const Line left_curve_start[];
extern const Line left_curve_a[];
extern const Line left_curve_b[];
extern const Line right_curve_start[];
extern const Line right_curve_a[];
extern const Line right_curve_b[];
extern const Line bridge_start[];
extern const Line bridge_a[];
extern const Line bridge_b[];
extern const Line title_page[];
extern const Line car_page[];
extern const Line controls_page[];
extern const Line keys_page[];
extern const Line aim_page[];
extern const Line plan_page[];
extern const Line credits_page[];

#pragma compile("text.c")

#endif
