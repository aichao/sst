#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <termios.h>

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

