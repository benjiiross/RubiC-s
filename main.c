#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"

int side_to_index(T_SIDE side) {

    switch(side) {
        case FRONT :return 2;
        case BACK : return 4;
        case UP :   return 0;
        case DOWN : return 5;
        case LEFT : return 1;
        case RIGHT :return 3;

    }
}

T_COLOR side_to_color(T_SIDE side) {

    switch(side) {
        case FRONT :return G;
        case BACK : return B;
        case UP :   return W;
        case DOWN : return Y;
        case LEFT : return O;
        case RIGHT :return R;

    }
}

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
