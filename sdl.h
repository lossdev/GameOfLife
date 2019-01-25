#ifndef SDL_H
#define SDL_H

#include "SDL2/SDL.h"

struct color_t {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned int value;
};

/* structure to hold needed SDL parameters. This code is
 * designed for SDL 2 */
struct sdl_info_t {
 	SDL_Surface *screen;
	SDL_Window *window;
        SDL_Renderer *renderer;
	SDL_Texture *texture;
        struct color_t color;
        int width;
        int height;
        int sprite_size;
};


/* sprite_size must be 2, 4, 8, or 16 otherwise defaults to 2
 * this function sets up SDL so you can draw to the window */
void init_sdl_info(struct sdl_info_t *sdl_info, int width, int height, int sprite_size, unsigned int red, unsigned int green, unsigned int blue);
void sdl_render_life(struct sdl_info_t *sdl_info, unsigned char **a);
//void sdl_test(struct sdl_info_t *sdl_info, int m, int n);

#endif
