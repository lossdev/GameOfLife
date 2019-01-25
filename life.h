#ifndef LIFE_H_
#define LIFE_H_

struct coordinates_t {
        int x;
        int y;
        struct coordinates_t *next;
};

struct options_t {
        int red;
        int green;
        int blue;
        int width;
        int height;
        int sprite_size;
        char *filename;
        char *origin;
        int x_origin;
        int y_origin;
        char *edge;
        char char_edge;
};

unsigned char **init_matrix(int rows, int cols);
unsigned char **zero_funct(unsigned char **a, int rows, int cols);
struct coordinates_t *get_coordinates(struct coordinates_t *coordinate, struct options_t *options);
struct coordinates_t *insert_head(struct coordinates_t *head, struct coordinates_t *coordinate, int x_init, int y_init);
struct coordinates_t *create_coordinate(int x_init, int y_init);
void convert_origin(struct options_t *option);
int check_color(int color);
void check_sprite(struct options_t *option);
void string_convert_char(struct options_t *option);
void plot_first(struct coordinates_t *coordinate, struct options_t *options, unsigned char **a);
unsigned char **iterate_a(unsigned char **a, unsigned char **b, int rows, int cols, struct options_t *option);
unsigned char **iterate_b(unsigned char **b, unsigned char **a, int rows, int cols, struct options_t *option);
int count_neighbors(unsigned char **a, int rows, int cols, struct options_t *option, int x, int y);

#endif
