/* ==================================================
 *                   C PROJECT
 *               "The Rubik's Cube"
 * ==================================================
 *
 *  Wrote by Benjamin ROSSIGNOL              L1 INT-5
 *  Ulysse JUGET and
 *  Benjamin CORCOS
 *
 *  FILE : main.c
 *
 * ==================================================
 *
 *  Table of contents
 *
 *   0 #include Files
 *   1 Main
 */



/*
 * ================
 * 0 #INCLUDE FILES
 * ================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubiks.h"



/*
 * ======
 * 1 MAIN
 * ======
 */

int main() {
    RUBIKS *rubiks;
    int choice=0;
    srand(time(NULL)); // initializes time for random scramble movements

    rubiks = create_rubiks(); // malloc
    init_rubiks(rubiks); // init rubiks with faces

    while (choice != 6) {
        printf("\n\n==================================RUBIK'S CUBE==================================\n");
        disp_main(rubiks);
        display_rubiks(rubiks);
        printf("Action : ");
        scanf("%d", &choice);

        switch(choice) {
            case 1 :
                init_rubiks(rubiks);
                scramble_rubiks(rubiks);
                break;
            case 2 :
                init_rubiks(rubiks);
                break;
            case 3 :
                blank_rubiks(rubiks);
                break;
            case 4 :
                play_rubiks(rubiks);
                break;
            case 5 :
                solve_rubiks(rubiks);
                break;
            case 6 :
                printf("Thank you for playing our game !\n");
                break;
            default :
                printf("Please enter a valid option.\n");
        }
    }
    free_rubiks(rubiks);

    return 0;
}
