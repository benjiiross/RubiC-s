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
    int choice=0, i, j, k;
    srand(time(NULL)); // initializes time for random scramble movements

    rubiks = create_rubiks(); // malloc
    init_rubiks(rubiks); // init rubiks with faces

    while (choice != 7) {
        //resetting rubiks front position

        //goto location
        start:
        choice = 0;
        rubiks->move_nbr=0; // resets rubiks move number

        printf("\n\n========================================RUBIK'S CUBE=========================================\n"
               "---------------------------------------------------------------------------------------------\n"
               "Scramble : 1     Reset : 2     Blank : 3     Play : 4     Fill : 5     Solve : 6     Exit : 7\n"
               "---------------------------------------------------------------------------------------------\n\n");

        display_rubiks(rubiks);
        printf("Action : ");
        scanf("%d", &choice);

        switch(choice) {
            case 1 :
                for (k=0;k<6;k++) {
                    for(i=0;i<3;i++) {
                        for (j=0;j<3;j++) {
                            if (rubiks->faces[k].grid[i][j] == LG) {
                                printf("Cannot scramble a rubiks with empty squares.");
                                goto start; //leaves the scrambling and goes to start
                            }
                        }
                    }
                }
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
                fill_rubiks(rubiks);
                break;
            case 6 :
                for (k=0;k<6;k++) {
                    for(i=0;i<3;i++) {
                        for (j=0;j<3;j++) {
                            if (rubiks->faces[k].grid[i][j] == LG) {
                                printf("Cannot solve a rubiks with empty squares.");
                                goto start; //leaves the scrambling and goes to start
                            }
                        }
                    }
                }
                choice_solve(rubiks);
                break;
            case 7 :
                printf("Thank you for playing our game !\n");
                break;
            default :
                printf("Please enter a valid option.\n");
                choice = 0;
                break;
        }
    }
    free_rubiks(rubiks);

    return 0;
}
