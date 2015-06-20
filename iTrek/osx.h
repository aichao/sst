//
//  osx.h
//  iTrek_0
//
//  Created by Alan Chao on 6/19/15.
//
//

#ifndef iTrek_0_osx_h
#define iTrek_0_osx_h

#include <string>

void randomize(void);
int max(int, int);
int min(int, int);
int getch(void);

std::string format_int(int i, int width);
std::string format_float(double f, int width, int precision);
std::string format_float(double f, int precision);
std::string fixed_width_string(std::string const& s, int width);
std::string format_coordinate(int key, int x, int y);

#endif
