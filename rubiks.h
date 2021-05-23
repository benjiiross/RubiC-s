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
 *   3   Movements && Algorithms
 *   4   Solving
 */



/*
 * =====================
 * 0 TYPES && STRUCTURES
 * =====================
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
    char solve[50000];
    int move_nbr;
} RUBIKS;



/*
 * =========
 * 0.5 LOGIC
 * =========
 */

int select_color(T_COLOR);
char select_letter(T_COLOR);



/*
 * ======
 * 1 INIT
 * ======
 */

RUBIKS* create_rubiks();
void init_rubiks(RUBIKS* rubiks);



/*
 * ================
 * 2 DISPLAY & FILL
 * ================
 */

void disp_main(RUBIKS*);
void display_rubiks(RUBIKS*);
void display_movements(RUBIKS*);
void play_rubiks(RUBIKS*);
void blank_rubiks(RUBIKS*);
void free_rubiks(RUBIKS*);



/*
 * =========================
 * 3 MOVEMENTS && ALGORITHMS
 * =========================
 */

void rotate_face(int, T_SIDE, RUBIKS*);
void rotate_up(RUBIKS*);
void rotate_upC(RUBIKS*);
void rotate_left(RUBIKS*);
void rotate_leftC(RUBIKS*);
void rotate_front(RUBIKS*);
void rotate_frontC(RUBIKS*);
void rotate_right(RUBIKS*);
void rotate_rightC(RUBIKS*);
void rotate_back(RUBIKS*);
void rotate_backC(RUBIKS*);
void rotate_down(RUBIKS*);
void rotate_downC(RUBIKS*);
void simplify_moves(RUBIKS*);
void front_r(RUBIKS*);
void front_l(RUBIKS*);
void front_rC(RUBIKS*);
void solve_ycross(RUBIKS*);
void solve_perf_ycross(RUBIKS*);
void solve_corners(RUBIKS*);
void scramble_rubiks(RUBIKS*);
void rotate_rubiks_clockwise(RUBIKS*);
void rotate_rubiks(RUBIKS*);



/*
 * =========
 * 4 SOLVING
 * =========
 */

void solve_rubiks(RUBIKS*);
T_SIDE middle_white(RUBIKS*);
T_SIDE corner_white(RUBIKS*);
int all_four_white(RUBIKS*);
int perfect_cross(RUBIKS*);
void white_cross(RUBIKS*);
void solve_back(RUBIKS*);
void solve_front(RUBIKS*);
void solve_right(RUBIKS*);
void solve_left(RUBIKS*);
void white_face(RUBIKS*);
void second_layer(RUBIKS*);
void yellow_cross(RUBIKS*);
void perfect_yellow_cross(RUBIKS*);
int corner_spot(RUBIKS*);
void yellow_corners(RUBIKS*);
void perfect_cube(RUBIKS*);