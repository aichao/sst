#include "osx.h"

#include <sstream>
#include <iomanip>

#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h> // need for read

void randomize(void) {
	srand((int)time(NULL));
}


int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int min(int a, int b) {
	if (a < b) return a;
	return b;
}

int getch(void) {
	char chbuf[1];
	struct termios oldstate, newstate;
	tcgetattr(0, &oldstate);
	newstate = oldstate;
	newstate.c_lflag &= ~ICANON;
	newstate.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW,  &newstate);
	read(0, &chbuf, 1);
	tcsetattr(0, TCSANOW, &oldstate);
}

std::string format_int(int i, int width) {
  std::ostringstream oss;
  oss << std::setw(width) << i;
  return oss.str();
}
std::string format_float(double f, int width, int precision) {
  std::ostringstream oss;
  oss << std::fixed << std::setw(width) << std::setprecision(precision) << f;
  return oss.str();
}
std::string format_float(double f, int precision) {
  std::ostringstream oss;
  oss.precision(precision);
  oss << std::fixed << f;
  return oss.str();
}
std::string fixed_width_string(std::string const& s, int width) {
  std::ostringstream oss;
  oss << std::setw(width) << s;
  return oss.str();
}
std::string format_coordinate(int key, int x, int y) {
  std::ostringstream oss;
	if (key == 1) oss << " Quadrant";
	else if (key == 2) oss << " Sector";
	oss << " " << format_int(x, 1) << " - " << format_int(y, 1);
  return oss.str();
}

