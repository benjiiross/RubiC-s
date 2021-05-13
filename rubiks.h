typedef enum {W, O, G, R, B, Y, LG} T_COLOR;
typedef enum {UP, LEFT, FRONT, RIGHT, BACK, DOWN} T_SIDE;

typedef struct {
    T_SIDE side;
    T_COLOR grid[3][3];
} FACES;

typedef struct {
    FACES faces[6];
} RUBIKS;

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
void white_face(RUBIKS*);
RUBIKS* create_rubiks();
