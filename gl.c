#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "SDL2/SDL.h"
#include "sdl.h"
#include "life.h"

int main(int argc, char *argv[])
{
        //getopt: red, green, blue, width, height, sprite_size, filename, origin, help
        struct coordinates_t *coordinate = NULL;
        struct options_t *option = NULL;
        coordinate = malloc(sizeof(struct coordinates_t));
        option = malloc(sizeof(struct options_t));
        /* colors are RGB model valid values [0, 255] */
        int opt = 0;
        unsigned char **a;
        unsigned char **b;
        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */

        while ((opt = getopt(argc, argv, ":w:h:e:r:g:b:s:f:o:H")) != -1) {
                switch (opt) {
                        case 'w':
                                option -> width = atoi(optarg);
                                break;
                        case 'h':
                                option -> height = atoi(optarg);
                                break;
                        case 'e':
                                option -> edge = optarg;
                                break;
                        case 'r':
                                option -> red = atoi(optarg);
                                option -> red = check_color(option -> red);
                                break;
                        case 'g':
                                option -> green = atoi(optarg);
                                option -> green = check_color(option -> green);
                                break;
                        case 'b':
                                option -> blue = atoi(optarg);
                                option -> blue = check_color(option -> blue);
                                break;
                        case 's':
                                option -> sprite_size = atoi(optarg);
                                check_sprite(option);
                                break;
                        case 'f':
                                option -> filename = optarg;
                                break;
                        case 'o':
                                option -> origin = optarg;
                                convert_origin(option);
                                break;
                        case 'H':
                                printf("Usage: -w[width] -h[height] -e[edge] -r[red] -g[green] -b[blue] -s[sprite size]"
                                       "-f[filename] -o[origin] -H[help]\n");
                                exit(EXIT_FAILURE);
                                break;
                        default:
                                printf("Usage: -w[width] -h[height] -e[edge] -r[red] -g[green] -b[blue] -s[sprite size]"
                                       "-f[filename] -o[origin] -H[help]\n");
                                exit(EXIT_FAILURE);
                                break;
                }

        }

        /* set up SDL -- works with SDL2 */
	init_sdl_info(&sdl_info, option -> width, option -> height, option -> sprite_size, option -> red, option -> green, option -> blue);

        int rows = (option -> width / option -> sprite_size);
        int cols = (option -> height / option -> sprite_size);
        coordinate = get_coordinates(coordinate, option);
        a = init_matrix(rows, cols);
        b = init_matrix(rows, cols);
        a = zero_funct(a, rows, cols);
        b = zero_funct(b, rows, cols);
        string_convert_char(option);
        plot_first(coordinate, option, a);

        /* Main loop: loop forever. */
        int count = 1;
        sdl_render_life(&sdl_info, a);
	while (1)
	{
		if (SDL_GetTicks() % 10 == 0) {
                        if (count % 2 == 1) {
                                b = iterate_a(a, b, rows, cols, option);
                                sdl_render_life(&sdl_info, b);
                        }
                        else if (count % 2 == 0) {
                                a = iterate_b(b, a, rows, cols, option);
                                sdl_render_life(&sdl_info, a);
                        }
                        count++;
                }

                 /* Poll for events, and handle the ones we care about.
                  * You can click the X button to close the window
                  */
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type) {
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
                        /* If escape is pressed, return (and thus, quit) */
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
				break;
			case SDL_QUIT:
				return(0);
			}
		}
	}
	return 0;
}
