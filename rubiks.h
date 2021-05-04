typedef enum {R, B, G, W, Y, O, LG} T_COLOR;
typedef enum {FRONT, BACK, UP, DOWN, RIGHT, LEFT} T_SIDE;

typedef struct {
    T_SIDE side;
    T_COLOR grid[3][3];
} FACES;

typedef struct {
    FACES faces[6];
} RUBIKS;
