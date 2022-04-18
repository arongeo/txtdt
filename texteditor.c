#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define MAX_WINDOW_WIDTH 1000
#define MAX_WINDOW_HEIGHT 1000

struct cursor_t {
	unsigned int x;
	unsigned int y;
};

struct window_t {
	unsigned int width;
	unsigned int height;
	struct cursor_t cursor;
};

struct screen_part_t {
	char value;
};

void clear_screen() {
	printf("\e[1;1H\e[2J");
}

void get_window_size(unsigned int window_size[2]) {
	struct winsize windowsize;
	ioctl(0, TIOCGWINSZ, (char *) &windowsize);
	window_size[0] = windowsize.ws_col-1;
	window_size[1] = windowsize.ws_row;
}

void render_screen(unsigned int width, unsigned int height, struct screen_part_t screen[][height]) {
	char* result;
}

int main() {
	clear_screen();
	unsigned int winsize[2];
	get_window_size(winsize);
	struct window_t window;
	window.width = winsize[0];
	window.height = winsize[1];
	struct screen_part_t screen[window.height][window.width];
	render_screen(window.width, window.height, screen);
	return 0;
}
