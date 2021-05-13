#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "rubiks.h"


int main() {
    srand(time(NULL)); // initializes time for random scramble movements
    RUBIKS *rubiks;

    rubiks = create_rubiks(); // malloc
    init_rubiks(rubiks);
    scramble_rubiks(rubiks);
    display_rubiks(rubiks);

    solve_rubiks(rubiks);


    display_rubiks(rubiks);

    blank_rubiks(rubiks);
    free_rubiks(rubiks);
    return 0;
}
