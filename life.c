#include "life.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 512


/**
 * @param rows: vertical array
 * @param cols: horizontal array
 * @return: returns the initialized array of arrays
 */
unsigned char **init_matrix(int rows, int cols)
{
        int i;
        int j;
        unsigned char **a;
        /* allocate rows */
        a = malloc(rows * sizeof(int *));
        if(!a)
                return NULL;
        for(i = 0; i < rows; i++) {
                /* allocate cols for each row */
                a[i] = malloc(cols * sizeof(int));
                if (!a[i]) {
                        for (j = 0; j < i; j++)
                                free(a[j]);
                free(a);
                return NULL;
                }
        }
        return a;
}

/**
 * @param a is the matrix
 * @param rows is the vertical array
 * @param cols is the horizontal array
 */
unsigned char **zero_funct(unsigned char **a, int rows, int cols)
{
        int i, j;
        for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                        a[i][j] = 0;
                }
        }
        return a;
}

/**
 * @param coordinate is the linked list
 */
struct coordinates_t *get_coordinates(struct coordinates_t *coordinate, struct options_t *option)
{
        struct coordinates_t *tmp = NULL;
        struct coordinates_t *head = NULL;
        int x_init = 0;
        int y_init = 0;
        char buf[LEN];
        int count = 0;
        FILE *fp;
        fp = fopen(option -> filename, "r");
        fgets(buf, LEN, fp); //gets rid of the first line with #comment
        while(fgets(buf, LEN, fp)) {
                count++; //count of all non-comment lines in the file
        }
        fclose(fp);
        head = insert_head(head, coordinate, x_init, y_init);
        tmp = head;
        int i;
        for (i = 1; i < count; i++) {
                coordinate = create_coordinate(x_init, y_init); //linked list of coordinates
                tmp -> next = coordinate;
                tmp = tmp -> next;
        }
        int x_node;
        int y_node;
        tmp = head;
        fp = fopen(option -> filename, "r");
        fgets(buf, LEN, fp);
        while(fgets(buf, LEN, fp)) {
                sscanf(buf, "%d %d", &x_node, &y_node);
                tmp -> x = x_node;
                tmp -> y = y_node;
                tmp = tmp -> next;
        }
        return head;
}

/**
 * @head: the head node of the linked list
 * @coordinate is the linked list itself
 * @x_init is the initialization value of x in the nodes
 * @y_init is the initialization value of y in the nodes
 * @return is the node
 */
struct coordinates_t *insert_head(struct coordinates_t *head, struct coordinates_t *coordinate, int x_init, int y_init)
{
        coordinate = create_coordinate(x_init, y_init);
        coordinate -> next = head; //creates right hand connection to head
        head = coordinate; //head is now pointing to the new node
        return coordinate;
}

/**
 * @param x_init is the x initialization value
 * @y_init is the y initialization value
 * @return is the node
 */
struct coordinates_t *create_coordinate(int x_init, int y_init)
{
        struct coordinates_t *coordinate = malloc(sizeof(struct coordinates_t));
        coordinate -> x = x_init; //initializes the value system in the node
        coordinate -> y = y_init;
        coordinate -> next = NULL; //initializes the NULL terminator to the node
        return coordinate;
}

/**
 * @option is the struct that contains the x and y origin values
 */
void convert_origin(struct options_t *option)
{
        char *origin = option -> origin;
        char *x_origin = malloc(LEN);
        char *y_origin = malloc(LEN);
        int int_x_origin = 0;
        int int_y_origin = 0;
        x_origin = strtok(origin, ",");
        y_origin = strtok(NULL, "\n");
        sscanf(x_origin, "%d", &int_x_origin);
        sscanf(y_origin, "%d", &int_y_origin);
        option -> x_origin = int_x_origin;
        option -> y_origin = int_y_origin;
}

/**
 * @param color is from the option struct; contains the RGB value
 * @returns the fixed 0-255 color (if applicable)
 */
int check_color(int color)
{
        if (color > 255)
                color = 255;
        if (color < 0)
                color = 0;
        return color;
}

/**
 * @param option is the struct that contains the sprite size entered in getopt
 */
void check_sprite(struct options_t *option)
{
        int size = option -> sprite_size;
        if ((size != 2) && (size != 4) && (size != 8) && (size != 16)) {
                printf("Invalid sprite size entered, defaulting to 8\n");
                option -> sprite_size = 8;
        }
}

/**
 * @param coordinate is the linked list struct
 * @param option is the getopt struct that contains the x and y origin presets
 * @param a is the matrix
 */
void plot_first(struct coordinates_t *coordinate, struct options_t *option, unsigned char **a)
{
        struct coordinates_t *head = NULL;
        head = coordinate;
        int count = 0;
        int i;
        struct coordinates_t *tmp = NULL;
        tmp = head;
        while (tmp != NULL) {
                tmp = tmp -> next;
                count += 1;
        } //count of all elems in link list
        tmp = head;
        for (i = 0; i < count; i++) {
                a[option -> x_origin + tmp -> x][option -> y_origin + tmp -> y] = 1;
                tmp = tmp -> next;
        }
}

/**
 * @param option is the struct that holds the edge case
 */
void string_convert_char(struct options_t *option)
{
        size_t len = strlen(option -> edge);
        if (strncmp(option -> edge, "hedge", len) == 0)
                option -> char_edge = 'h';
        else if (strncmp(option -> edge, "torus", len) == 0)
                option -> char_edge = 't';
        else if (strncmp(option -> edge, "klein", len) == 0)
                option -> char_edge = 'k';
        else
                option -> char_edge = 'h';
}

/**
 * @param a is the matrix to read from
 * @param b is the matrix to write to
 * @param rows is the vertical array
 * @param cols is the horizontal array
 * @param option is the struct that holds the getopt options
 * @returns the second matrix b with changes read from a
 */
unsigned char **iterate_a(unsigned char **a, unsigned char **b, int rows, int cols, struct options_t *option)
{
        int x, y, count, alive;
        for (x = 0; x < rows; x++) {
                for (y = 0; y < cols; y++) {
                        count = count_neighbors(a, rows, cols, option, x, y);
                        alive = a[x][y];
                        if (alive == 1) {
                                if (count == 2 || count == 3)
                                        b[x][y] = a[x][y];
                                else
                                        b[x][y] = 0;
                        }
                        if (alive == 0) {
                                if (count == 3)
                                        b[x][y] = 1;
                                else
                                        b[x][y] = 0;
                        }
                }
        }
        return b;
}

/**
 * @param b is the matrix to read from
 * @param a is the matrix to write to
 * @param rows is the vertical array
 * @param cols is the horizontal array
 * @param option is the struct that holds the getopt options
 * @returns the first matrix b with changes read from a
 */
unsigned char **iterate_b(unsigned char **b, unsigned char **a, int rows, int cols, struct options_t *option)
{
        int x, y, count, alive;
        for (x = 0; x < rows; x++) {
                for (y = 0; y < cols; y++) {
                        count = count_neighbors(b, rows, cols, option, x, y);
                        alive = b[x][y];
                        if (alive == 1) {
                                if (count == 2 || count == 3)
                                        a[x][y] = b[x][y];
                                else
                                        a[x][y] = 0;
                        }
                        else {
                                if (count == 3)
                                        a[x][y] = 1;
                                else
                                        a[x][y] = 0;
                        }
                }
        }
        return a;
}

/**
 * @param a is the matrix to use for counting neighbors
 * @param rows is the vertical array
 * @param cols is the horizontal array
 * @param option is the struct that holds the getopt options
 * @param x is the current x index from the iterate() function
 * @param y is the current y index from the iterate() function
 * @returns the count of neighbors
 */
int count_neighbors(unsigned char **a, int rows, int cols, struct options_t *option, int x, int y)
{
        int i, j, x_entended, y_extended;
        int count = 0;
        for (i = -1; i < 2; i++) {
                for (j = -1; j < 2; j++) {
                        if (!(x + i > 0 && y + j > 0 && x + i < (rows - 1) && y + j < (cols - 1))) {
                                if (option -> char_edge == 'h') {
                                        ;
                                }

                                else if (option -> char_edge == 't') {
                                        x_entended = (x + i + rows) % rows;
                                        y_extended = (y + j + cols) % cols;
                                        if (!(a[x_entended][y_extended] == 0))
                                                count++;
                                        }
                                else if (option -> char_edge == 'k') {
                                                ; //not implemented yet
                                } else {
                                        ;
                                }
                        }
                        else {
                                if (!(a[x + i][y + j] == 0))
                                        count++;
                        }
                }
        }
        if (!(a[x][y] == 0))
                count--;
        return count;
}
