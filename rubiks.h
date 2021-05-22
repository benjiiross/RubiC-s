/* ==================================================
 *                   C PROJECT
 *               "The Rubik's Cube"
 * ==================================================
 *
 *  Wrote by Benjamin ROSSIGNOL              L1 INT-5
 *  Ulysse JUGET and
 *  Benjamin CORCOS
 *
 *  FILE : rubiks.h
 *
 * ==================================================
 *
 *  Table of contents
 *
 *   0   Types && Structures
 *   0.5 Logic
 *   1   Init
 *   2   Display & Fill
 *   3   Movements
 *   4   Solving Algorithms
 */


/*
 * =======================
 * 0.5 TYPES && STRUCTURES
 * =======================
 */



typedef enum {W, O, G, R, B, Y, LG} T_COLOR;
// Creates the enumerated type T_COLOR.
// Stored in rubiks.faces[face].grid[i][j]

typedef enum {UP, LEFT, FRONT, RIGHT, BACK, DOWN} T_SIDE;
// Creates the enumerated type T_SIDE.
// Used to access face with rubiks.faces[face]

typedef struct {
    T_COLOR grid[3][3];
} FACES;

typedef struct {
    FACES faces[6];
    char solve[100];
    int len_solve;
} RUBIKS;











void disp_main(RUBIKS*);

void display_rubiks(RUBIKS*);
void fill_rubiks(RUBIKS*);
void init_rubiks(RUBIKS*);
void rotate_face(int, T_SIDE, RUBIKS*);
void scramble_rubiks(RUBIKS*);
void blank_rubiks(RUBIKS*);
void free_rubiks(RUBIKS*);
void rotate_up(RUBIKS*);
void rotate_left(RUBIKS*);
void rotate_front(RUBIKS*);
void rotate_right(RUBIKS*);
void rotate_back(RUBIKS*);
void rotate_down(RUBIKS*);
void solve_rubiks(RUBIKS*);
void white_cross(RUBIKS*);
int near_white(RUBIKS*);
void white_face(RUBIKS*);
void second_layer(RUBIKS*);
void yellow_cross(RUBIKS*);
void perfect_yellow_cross(RUBIKS*);
void yellow_corners(RUBIKS*);
void perfect_cube(RUBIKS*);
RUBIKS* create_rubiks();
