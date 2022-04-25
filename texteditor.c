#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

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
	window_size[1] = windowsize.ws_row-3;
}

void render_screen(unsigned int width, unsigned int height, struct screen_part_t screen[][width]) {
	char* result;
	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			result += screen[i][j].value;
		}
		result += '\n';
	}
	printf("%s", result);
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
