#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "rubiks.c"


int main() {
    RUBIKS *rubiks;

    rubiks = create_rubiks(); /* malloc */
    init_rubiks(rubiks);

    rubiks->faces[side_to_index(FRONT)].grid[0][2] = R;
    rubiks->faces[side_to_index(FRONT)].grid[1][1] = B;
    rubiks->faces[side_to_index(FRONT)].grid[2][2] = Y;
    rubiks->faces[side_to_index(FRONT)].grid[0][1] = O;
    rubiks->faces[side_to_index(FRONT)].grid[2][1] = LG;
    rubiks->faces[side_to_index(FRONT)].grid[0][0] = B;
    display_rubiks(rubiks);

    front_clockwise(rubiks, 1);
    display_rubiks(rubiks);

    blank_rubiks(rubiks);
    free_rubiks(rubiks);
    return 0;
}
