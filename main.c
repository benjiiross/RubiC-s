#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"



int main(){
    RUBIKS *rubiks;

    rubiks = create_rubiks();
    init_rubiks(rubiks);
    display_rubiks(rubiks);
    printf("%d", rubiks->faces[UP].side);
    rubiks->faces[side_to_index(DOWN)].grid[1][2] = R;
    display_rubiks(rubiks);

    blank_rubiks(rubiks);
    display_rubiks(rubiks);

    fill_rubiks(rubiks);
    display_rubiks(rubiks);

    free(rubiks);
    return 0;
    }
