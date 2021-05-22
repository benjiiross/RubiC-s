#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubiks.h"


int main() {
    srand(time(NULL)); // initializes time for random scramble movements
    RUBIKS *rubiks;
    int choice=0;
    rubiks = create_rubiks(); // malloc
    init_rubiks(rubiks);
    disp_main(rubiks);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            scramble_rubiks(rubiks);
            break;
        case 2:
            init_rubiks(rubiks);
            break;
        case 3:
            blank_rubiks(rubiks);
            break;
        case 4:

        case 5:
            solve_rubiks(rubiks);
            break;
        case 6:
            printf("Thank you !");
            exit(EXIT_SUCCESS);
        default:
            system("cls");
            printf("Please enter a valid option.");
    }

    display_rubiks(rubiks);

    scramble_rubiks(rubiks);
    solve_rubiks(rubiks);

    free_rubiks(rubiks);
    return 0;
}
