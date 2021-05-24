/* ==================================================
 *                   C PROJECT
 *               "The Rubik's Cube"
 * ==================================================
 *
 *  Wrote by Benjamin ROSSIGNOL              L1 INT-5
 *  Ulysse JUGET and
 *  Benjamin CORCOS
 *
 *  FILE : rubiks.c
 *
 * ==================================================
 *
 *  Table of contents
 *
 *   0   #include Files
 *   0.5 Logic
 *   1   Init
 *   2   Display & Fill
 *   3   Movements && Algorithms
 *   4   Solving
 */

/* TODO
 * check .h
 * put rubiks back on top
 * flush movements               NO
 * insert rotate cube ?
 * play_rubiks
 * simplify the equations ? ->
 *
 *
 * create fct that checks if rubiks is solvable :
 * computer speedrun
 * if return 1 -> change void to int && return 0
 * says is not possible
 */



/*
 * ================
 * 0 #INCLUDE FILES
 * ================
 */



#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "conio.h"
#include <time.h>


/*
 * =========
 * 0.5 LOGIC
 * =========
 */



/*
 * Function : select_color
 * ------------------------------------------------------------
 *
 * returns : color in whole letter to print in color in console
 * type    : int
 */


int select_color(T_COLOR color) {

    switch(color) {
        case R : return RED;
        case B : return BLUE;
        case G : return GREEN;
        case W : return WHITE;
        case O : return BROWN;
        case Y : return YELLOW;
        case LG :return LIGHTGRAY;
        default :exit(EXIT_FAILURE);
    }
}


/*
 * Function : select_letter
 * ---------------------------------------------
 *
 * returns : letter of color to print in console
 * type    : char
 */

char select_letter(T_COLOR color) {

    switch(color) {
        case R : return 'R';
        case B : return 'B';
        case G : return 'G';
        case W : return 'W';
        case O : return 'O';
        case Y : return 'Y';
        case LG :return 'L';
        default :exit(EXIT_FAILURE);

    }
}



/*
 * ======
 * 1 INIT
 * ======
 */



/*
 * Function : create_rubiks
 * -----------------------------------------------
 *
 * returns : dynamically allocated address of cube
 * type    : RUBIKS*
 */

RUBIKS* create_rubiks() {

    return (RUBIKS*)malloc(sizeof(RUBIKS));

}


/*
 * Function : init_rubiks
 * -----------------------------------------
 *
 * Fills the cube with faces names and color
 */

void init_rubiks(RUBIKS* rubiks) {

    int i, j, k;
    for (i=0;i<6;i++) {
        for (j=0;j<3;j++) {
            for (k=0;k<3;k++)
                rubiks->faces[i].grid[j][k] = i;
        }
    }
    rubiks->move_nbr = 0;
}



/*
 * ================
 * 2 DISPLAY & FILL
 * ================
 */



/*
 * Function : display_rubiks
 * -------------------------------------------
 *
 * Displays the rubiks with matching colors
 * Letters corresponds to colors of the rubiks
 */

void display_rubiks(RUBIKS* rubiks) {

    int i, j, k;

    printf("=============================\n\n");
    printf("        ");
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            c_textcolor(select_color(rubiks->faces[0].grid[i][j]));
            printf("%c ", select_letter(rubiks->faces[0].grid[i][j])); /* TOP FACE */}
        if (i<2)
            printf("\n        ");
    }
    printf("\n\n");
    for (i=0;i<3;i++) {
        for (j=1;j<5;j++) {
            for (k=0;k<3;k++) {
                c_textcolor(select_color(rubiks->faces[j].grid[i][k]));
                printf("%c ", select_letter(rubiks->faces[j].grid[i][k])); /* MID FACES (Lines faces)*/
            }
            printf("  ");
        }
        printf("\n");
    }
    printf("\n        ");
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            c_textcolor(select_color(rubiks->faces[5].grid[i][j]));
            printf("%c ", select_letter(rubiks->faces[5].grid[i][j])); /* BOTTOM FACE*/
        }
        if (i<2)
            printf("\n        ");
    }
    c_textcolor(WHITE);
    printf("\n=============================\n\n");
}


/*
 * Function : display_movements
 * -----------------------------------------------------
 *
 * Display all the movements stored while solving cube /
 * playing rubiks / scrambling.
 */

void display_movements(RUBIKS* rubiks) {

    int i;
    for (i=0;i<rubiks->move_nbr;i++) {
        // if we are not at the end && the move is done twice, for ex U2 OR
        // if we are not at the end && the move is done counterclockwise, for ex U'
        if (i < rubiks->move_nbr-1 && (rubiks->solve[i+1] == '2' || rubiks->solve[i+1] == '\''))
            printf("%c", rubiks->solve[i]);
        else if (i < rubiks->move_nbr-1 && rubiks->solve[i] == 'A')
            printf("\n");

        else
            printf("%c ", rubiks->solve[i]);
    }
    printf("\n");
    //adds backslash for better readability
    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'A';
}

/*
 * Function : fill_rubiks
 * --------------------------------------
 *
 * Let the user fill the rubiks.
 * Checks if valid solution by creating a
 * temp rubiks and solving it
 */


void fill_rubiks(RUBIKS* rubiks) {

    char replace[4] = "ABCD";
    T_SIDE side;
    T_COLOR color;
    RUBIKS* tempRubiks; // creating temp rubiks to check if solution is possible
    int solvable=0, i, j, k;

    while (!(solvable)) {
        while ((replace[0] != 'Q' && replace[1] != 'U' && replace[2] != 'I' && replace[3] != 'T') || solve_fast(tempRubiks)) {
            start:  //goto location
            printf("Please enter a face name, a location and a color to replace.\n"
                   "Ex : \'U21R\' will replace up face bottom center color to red.\n"
                   "Enter \'QUIT\' to leave. and \'RSET\' to reset the rubiks.\n");
            display_rubiks(rubiks);
            scanf("%s", replace);

            //if valid expression
            if ((replace[0] == 'U' || replace[0] == 'L' || replace[0] == 'F' || replace[0] == 'R' ||
                 replace[0] == 'B' || replace[0] == 'D') &&
                (replace[1] == '0' || replace[1] == '1' || replace[1] == '2') &&
                (replace[2] == '0' || replace[2] == '1' || replace[2] == '2') &&
                (replace[3] == 'W' || replace[3] == 'O' || replace[3] == 'G' || replace[3] == 'R' ||
                 replace[3] == 'B' || replace[3] == 'Y')) {

                //stores face
                switch (replace[0]) {
                    case 'U' :
                        side = UP;
                        break;
                    case 'L' :
                        side = LEFT;
                        break;
                    case 'F' :
                        side = FRONT;
                        break;
                    case 'R' :
                        side = RIGHT;
                        break;
                    case 'B' :
                        side = BACK;
                        break;
                    case 'D' :
                        side = DOWN;
                        break;
                }
                //stores color
                switch (replace[3]) {
                    case 'W' :
                        color = W;
                        break;
                    case 'O' :
                        color = O;
                        break;
                    case 'G' :
                        color = G;
                        break;
                    case 'R' :
                        color = R;
                        break;
                    case 'B' :
                        color = B;
                        break;
                    case 'Y' :
                        color = Y;
                        break;
                }

                // subtracts number from '0' to convert char to int
                rubiks->faces[side].grid[(int) (replace[1] - '0')][(int) (replace[2] - '0')] = color;
                goto start;
            }
            else if (replace[0] == 'Q' && replace[1] == 'U' && replace[2] == 'I' && replace[3] == 'T') {

                for (k=0;k<6;k++) {
                    for(i=0;i<3;i++) {
                        for (j=0;j<3;j++) {
                            if (rubiks->faces[k].grid[i][j] == LG) {
                                printf("You cannot exit with an empty square.\n");
                                goto start;
                            }
                        }
                    }
                }
                tempRubiks = (RUBIKS*)malloc(sizeof(RUBIKS));
                tempRubiks->move_nbr=0;

                for (k=0;k<6;k++) {
                    for (i=0;i<3;i++) {
                        for (j=0;j<3;j++)
                            tempRubiks->faces[k].grid[i][j] = rubiks->faces[k].grid[i][j]; // stores temp rubiks
                    }
                }
                if (solve_fast(tempRubiks))
                    printf("\nUnsolvable rubiks ! Please enter a valid option.\n");
                else {
                    solvable = 1;
                    printf("Returning to main program...\n");
                }
            }
            else if (replace[0] == 'R' && replace[1] == 'S' && replace[2] == 'E' && replace[3] == 'T') {
                init_rubiks(rubiks);
                goto start;
            }
            else {
                printf("Please enter a valid expression.\n");
                goto start;
            }

        }



    }
    free(tempRubiks);
}

/*
 * Function : play_rubiks
 * ------------------------------------
 *
 * Let the user enter manual movements.
 */

void play_rubiks(RUBIKS* rubiks) {

    char choice[2] = "OK";

    while(*(choice) != 'G' && *(choice+1) != 'O') {

        printf("Please enter a movement type :\n"
               "Enter a name face in capital letters,\n"
               "UP, LT, FT, RT, BK, DN and {letter}' for counter, ex : U'\n"
               "Enter RR for rotate right the entire rubiks and RU for rotate up the rubiks.\n");
        display_rubiks(rubiks);
        printf("Movement :");
        scanf("%s", choice);

        switch (*choice) {

            case 'U':
                if (*(choice+1) == '\'')
                    rotate_upC(rubiks);
                else if (choice[1] == 'P')
                    rotate_up(rubiks);
                *choice = 'O';      //resetting value
                *(choice+1) = 'K';
                break;
            case 'L':
                if (*(choice+1) == '\'')
                    rotate_leftC(rubiks);
                else
                    rotate_left(rubiks);
                *choice = 'O';
                *(choice+1) = 'K';
                break;
            case 'F':
                if (*(choice+1) == '\'')
                    rotate_frontC(rubiks);
                else
                    rotate_front(rubiks);
                *choice = 'O';
                *(choice+1) = 'K';
                break;
            case 'R':
                if (*(choice+1) == '\'')
                    rotate_rightC(rubiks);
                else if (*(choice+1) == 'R')
                    rotate_rubiks_clockwise(rubiks);
                else if (*(choice+1) == 'U')
                    rotate_rubiks(rubiks);
                else
                    rotate_right(rubiks);
                *choice = 'O';
                *(choice+1) = 'K';
                break;
            case 'B':
                if (*(choice+1) == '\'')
                    rotate_backC(rubiks);
                else
                    rotate_back(rubiks);
                *choice = 'O';
                *(choice+1) = 'K';
                break;
            case 'D':
                if (*(choice+1) == '\'')
                    rotate_downC(rubiks);
                else
                    rotate_down(rubiks);
                *choice = 'O';
                *(choice+1) = 'K';
                break;
            case 'O':
                if (*(choice+1) == 'K')
                    printf("Ending playing with rubiks");
                    break;
            default:
                printf("Please enter a valid option.\n");
                *choice = 'G';
                *(choice+1) = 'O';
        }
        simplify_moves(rubiks);
        display_movements(rubiks);

    }
}



/*
 * Function : blank_rubiks
 * ------------------------------------
 *
 * Fills the cube with Light Gray color
 */

void blank_rubiks(RUBIKS* rubiks) {

    int i, j, k;
    for (i=0;i<6;i++) {
        for (j=0;j<3;j++) {
            for (k=0;k<3;k++)
                rubiks->faces[i].grid[j][k] = LG;
        }
    }
}


/*
 * Function : free_rubiks
 * ----------------------------
 *
 * Frees the malloc-ated rubiks
 */

void free_rubiks(RUBIKS* rubiks) {
    free(rubiks);
}



/*
 * =========================
 * 3 MOVEMENTS && ALGORITHMS
 * =========================
 */



/*
 * Functions : rotate_face
 * --------------------------------------------------------
 *
 * Takes rotation nbr and a face to rotate, then rotates it
 *
 */

void rotate_face(int rotations, T_SIDE face, RUBIKS* rubiks) {

    int i;
    for (i=0;i<rotations;i++) {
        switch (face) {
            case UP :    rotate_up(rubiks); break;
            case LEFT :  rotate_left(rubiks); break;
            case FRONT : rotate_front(rubiks); break;
            case RIGHT : rotate_right(rubiks); break;
            case BACK :  rotate_back(rubiks); break;
            case DOWN :  rotate_down(rubiks); break;
            default :    exit(EXIT_FAILURE);
        }
    }
}


/*
 * Functions : rotate_{face_name} && rotate_{face_name}C
 * ------------------------------------------------------------------------------
 *
 * Rotates a face in clockwise direction
 * For counterclockwise movements, this function is called three times.
 *
 * Also, removes unnecessary turns in rubiks->move_nbr && rubiks->solve directly.
 */

void rotate_up(RUBIKS* rubiks) {

    int i, j;

    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            tempGrid[i][j] = rubiks->faces[UP].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[FRONT].grid[0][i]; // Stores temp FRONT side
    }

    // Rotating UP face
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            rubiks->faces[UP].grid[i][j] = tempGrid[2 - j][i];
    }

    // Rotating sides
    for (i = 0; i < 3; i++) {
        rubiks->faces[FRONT].grid[0][i] = rubiks->faces[RIGHT].grid[0][i];
        rubiks->faces[RIGHT].grid[0][i] = rubiks->faces[BACK].grid[0][i];
        rubiks->faces[BACK].grid[0][i] = rubiks->faces[LEFT].grid[0][i];
        rubiks->faces[LEFT].grid[0][i] = tempGrid[3][i];
    }

    //adds 1 to move_nbr && adds letter U (for up)
    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'U';
    simplify_moves(rubiks);
}

void rotate_upC(RUBIKS* rubiks) {

    rotate_up(rubiks);
    rotate_up(rubiks);
    rotate_up(rubiks);

}

void rotate_left(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3];

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[LEFT].grid[i][j];
        tempGrid[3][i] = rubiks->faces[FRONT].grid[i][0];
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[LEFT].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[FRONT].grid[i][0] = rubiks->faces[UP].grid[i][0];
        rubiks->faces[UP].grid[i][0] = rubiks->faces[BACK].grid[2 - i][2];
        rubiks->faces[BACK].grid[2 - i][2] = rubiks->faces[DOWN].grid[i][0];
        rubiks->faces[DOWN].grid[i][0] = tempGrid[3][i];
    }
    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'L';
    simplify_moves(rubiks);
}

void rotate_leftC(RUBIKS* rubiks) {

    rotate_left(rubiks);
    rotate_left(rubiks);
    rotate_left(rubiks);
}

void rotate_front(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3];

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[FRONT].grid[i][j];
        tempGrid[3][i] = rubiks->faces[UP].grid[2][i];
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[FRONT].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[UP].grid[2][i] = rubiks->faces[LEFT].grid[2-i][2];
        rubiks->faces[LEFT].grid[2-i][2] = rubiks->faces[DOWN].grid[0][2-i];
        rubiks->faces[DOWN].grid[0][2-i] = rubiks->faces[RIGHT].grid[i][0];
        rubiks->faces[RIGHT].grid[i][0] = tempGrid[3][i];
    }

    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'F';
    simplify_moves(rubiks);
}

void rotate_frontC(RUBIKS* rubiks) {

    rotate_front(rubiks);
    rotate_front(rubiks);
    rotate_front(rubiks);
}

void rotate_right(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3];

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[RIGHT].grid[i][j];
        tempGrid[3][i] = rubiks->faces[FRONT].grid[i][2];
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[RIGHT].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[FRONT].grid[i][2] = rubiks->faces[DOWN].grid[i][2];
        rubiks->faces[DOWN].grid[i][2] = rubiks->faces[BACK].grid[2-i][0];
        rubiks->faces[BACK].grid[2-i][0] = rubiks->faces[UP].grid[i][2];
        rubiks->faces[UP].grid[i][2] = tempGrid[3][i];
    }


    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'R';
    simplify_moves(rubiks);
}

void rotate_rightC(RUBIKS* rubiks) {

    rotate_right(rubiks);
    rotate_right(rubiks);
    rotate_right(rubiks);
}

void rotate_back(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3];

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[BACK].grid[i][j];
        tempGrid[3][i] = rubiks->faces[UP].grid[0][i];
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[BACK].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[UP].grid[0][i] = rubiks->faces[RIGHT].grid[i][2];
        rubiks->faces[RIGHT].grid[i][2] = rubiks->faces[DOWN].grid[2][2-i];
        rubiks->faces[DOWN].grid[2][2-i] = rubiks->faces[LEFT].grid[2-i][0];
        rubiks->faces[LEFT].grid[2-i][0] = tempGrid[3][i];
    }

    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'B';
    simplify_moves(rubiks);
}

void rotate_backC(RUBIKS* rubiks) {

    rotate_back(rubiks);
    rotate_back(rubiks);
    rotate_back(rubiks);
}

void rotate_down(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3];

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[DOWN].grid[i][j];
        tempGrid[3][i] = rubiks->faces[FRONT].grid[2][i];
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[DOWN].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[FRONT].grid[2][i] = rubiks->faces[LEFT].grid[2][i];
        rubiks->faces[LEFT].grid[2][i] = rubiks->faces[BACK].grid[2][i];
        rubiks->faces[BACK].grid[2][i] = rubiks->faces[RIGHT].grid[2][i];
        rubiks->faces[RIGHT].grid[2][i] = tempGrid[3][i];
    }

    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'D';
    simplify_moves(rubiks);
}

void rotate_downC(RUBIKS* rubiks) {

    rotate_down(rubiks);
    rotate_down(rubiks);
    rotate_down(rubiks);
}


/*
 * Function : simplify_moves
 * -----------------------------------------
 *
 * Simplifies rubiks->solve after each move.
 */

void simplify_moves(RUBIKS* rubiks) {

    int i, j;

    //if we do twice the same movement changes letter to '2'
    if (rubiks->move_nbr > 1 && (rubiks->solve[rubiks->move_nbr - 1] == rubiks->solve[rubiks->move_nbr - 2]))
        rubiks->solve[rubiks->move_nbr - 1] = '2';

    /*
     * if the move number is higher than two and the previous element is a two
     * and the previous previous element is the same than the last one
     * ---> If we have U2U
     * replace by U'.
     */
    if (rubiks->move_nbr > 2 && rubiks->solve[rubiks->move_nbr - 2] == '2' &&
        rubiks->solve[rubiks->move_nbr - 3] == rubiks->solve[rubiks->move_nbr - 1]) {
        rubiks->move_nbr--;
        rubiks->solve[rubiks->move_nbr - 1] = '\'';
    }

    /*
     * if the move number is higher than two and the previous element is a '
     * and the previous previous element is the same than the last one
     * ---> If we have U'U
     * remove the movement (same as before) by lowering move_nbr.
     */
    if (rubiks->move_nbr > 2 && rubiks->solve[rubiks->move_nbr - 2] == '\'' &&
        rubiks->solve[rubiks->move_nbr - 3] == rubiks->solve[rubiks->move_nbr - 1])
        rubiks->move_nbr = rubiks->move_nbr - 3;

}


/*
 * Function : front_r
 * -----------------------------------------
 *
 * Solving algorithm for second rank corners
 * when matching color needs to go right
 */

void front_r(RUBIKS* rubiks) {

    rotate_up(rubiks);
    rotate_right(rubiks);
    rotate_upC(rubiks);
    rotate_rightC(rubiks);
    rotate_upC(rubiks);
    rotate_frontC(rubiks);
    rotate_up(rubiks);
    rotate_front(rubiks);
}


/*
 * Functions : front_l
 * -----------------------------------------
 *
 * Solving algorithm for second rank corners
 * when matching color needs to go left
 *
 */

void front_l(RUBIKS* rubiks) {

    rotate_upC(rubiks);
    rotate_leftC(rubiks);
    rotate_up(rubiks);
    rotate_left(rubiks);
    rotate_up(rubiks);
    rotate_front(rubiks);
    rotate_upC(rubiks);
    rotate_frontC(rubiks);
}


/*
 * Functions : front_rC
 * -------------------------------
 *
 * Used when no squares are good,
 * putting a side square on front.
 * it is the Counter of front_r
 *
 */

void front_rC(RUBIKS* rubiks) {

    rotate_up(rubiks);
    rotate_right(rubiks);
    rotate_upC(rubiks);
    rotate_rightC(rubiks);
    rotate_upC(rubiks);
    rotate_frontC(rubiks);
    rotate_up(rubiks);
    rotate_front(rubiks);
}


/*
 * Function : solve_ycross
 * ------------------------------------------
 *
 * Solving algorithm for yellow cross
 * front_rC is used when no squares are good,
 * putting a side square on front.
 * it is the Counter of front_r
 *
 */

void solve_ycross(RUBIKS* rubiks) {

    rotate_front(rubiks);
    rotate_right(rubiks);
    rotate_up(rubiks);
    rotate_rightC(rubiks);
    rotate_upC(rubiks);
    rotate_frontC(rubiks);
}

void solve_perf_ycross(RUBIKS* rubiks) {

    rotate_right(rubiks);
    rotate_up(rubiks);
    rotate_rightC(rubiks);
    rotate_up(rubiks);
    rotate_right(rubiks);
    rotate_up(rubiks);
    rotate_up(rubiks);
    rotate_rightC(rubiks);
    rotate_up(rubiks);
}


void solve_corners(RUBIKS* rubiks) {

    rotate_up(rubiks);
    rotate_right(rubiks);
    rotate_upC(rubiks);
    rotate_leftC(rubiks);
    rotate_up(rubiks);
    rotate_rightC(rubiks);
    rotate_upC(rubiks);
    rotate_left(rubiks);
}


/*
 * Function : scramble_rubiks
 * --------------------------------------------------------------
 *
 * Scrambles the rubiks by doing random movements
 * First, rand() selects the face to rotate
 * Then, i%4+1 decides the amount of time to rotate it
 * This function then calls rotate_face with theses two arguments
 */

void scramble_rubiks(RUBIKS* rubiks) {

    int move_nbr = rand() % 10 + 20;
    int i;

    for (i = 0; i < move_nbr; i++)
        rotate_face(i%4+1, rand()%6, rubiks); // rotates i%4+1 times the face rand%6
}


/*
 * Function : rotate_rubiks_clockwise
 * --------------------------------------------------------------
 *
 * Rotates the rubiks clockwise :
 * If green was front and red was right, then
 * green is left and red is front
 */

void rotate_rubiks_clockwise(RUBIKS* rubiks) {

    T_COLOR tempGrid[3][3];
    int i, j;

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[UP].grid[i][j]; // Store temp grid up
    }
    // Rotating UP face
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[UP].grid[i][j] = tempGrid[2-j][i];
    }

    //storing / rotating 3 times down
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[DOWN].grid[i][j]; // Store temp grid down
    }
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[DOWN].grid[i][j] = tempGrid[2-j][i];
    }
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[DOWN].grid[i][j]; // Store temp grid down
    }
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[DOWN].grid[i][j] = tempGrid[2-j][i];
    }
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[DOWN].grid[i][j]; // Store temp grid down
    }
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[DOWN].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        for (j = 0; j < 3; j++)
            tempGrid[i][j] = rubiks->faces[RIGHT].grid[i][j]; // Store temp grid up
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            rubiks->faces[RIGHT].grid[i][j] = rubiks->faces[BACK].grid[i][j];
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            rubiks->faces[BACK].grid[i][j] = rubiks->faces[LEFT].grid[i][j];
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            rubiks->faces[LEFT].grid[i][j] = rubiks->faces[FRONT].grid[i][j];
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            rubiks->faces[FRONT].grid[i][j] = tempGrid[i][j];
    }

    //adds 1 to move_nbr && adds letter U (for up)
    rubiks->move_nbr++;
    rubiks->solve[rubiks->move_nbr-1] = 'y';
    simplify_moves(rubiks);

}


/*
 * Function : rotate_rubiks
 * --------------------------------------------------------------
 *
 * Rotates the rubiks up and down :
 * If green was front and yellow was down, then
 * green is top and yellow is front
 */

void rotate_rubiks(RUBIKS* rubiks) {

    T_COLOR tempGrid[3][3];
    int i, j;
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            tempGrid[i][j] = rubiks->faces[UP].grid[i][j]; // storing up face
        }
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[UP].grid[i][j] = rubiks->faces[FRONT].grid[i][j]; // swapping up/front
        }
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[FRONT].grid[i][j] = rubiks->faces[DOWN].grid[i][j]; // swapping front/down
        }
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[DOWN].grid[i][j] = rubiks->faces[BACK].grid[2-i][2-j]; // swapping down/back
        }
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[BACK].grid[2-i][2-j] = tempGrid[i][j]; // swapping back/up
        }
    }
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[RIGHT].grid[i][j]; // rotating right clockwise
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[RIGHT].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[LEFT].grid[i][j]; // rotating left counterclockwise
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[LEFT].grid[i][j] = tempGrid[j][2-i]; //
        }
    }

}

/*
 * =========
 * 4 SOLVING
 * =========
 */



/*
 * Function : choice_solve
 * ---------------------------------------------------------------------
 *
 * Let the user choose between step-by-step resolution or speedrun mode.
 */

void choice_solve(RUBIKS* rubiks) {

    int choice=0;
    printf("Please choose between step-by-step (1) or speedrun mode.(2) ");

    while(choice != 1 && choice != 2) {
        scanf("%d", &choice);
        if (choice == 1)
            solve_rubiks(rubiks);
        else if (choice == 2)
            speedrun_rubiks(rubiks);
        else
            printf("Please choose between 1 and 2. ");
    }
}


/*
 * Function : solve_rubiks
 * -------------------------------------------
 *
 * Pretty straight-explanatory.
 * Calls all the functions needed to solve it,
 * and wait for the user to go forward
 */

void solve_rubiks(RUBIKS* rubiks) {

    int good=0;
    //resets all the moves previously done
    rubiks->move_nbr=0;

    printf("\n-----------------------------\n"
           "===========SOLVE=============\n"
           "-----------------------------\n\n");


    while (rubiks->faces[UP].grid[1][1] != W && rubiks->faces[UP].grid[1][1] != G) {
        rotate_rubiks(rubiks);
        printf("?");
    }

    if (rubiks->faces[UP].grid[1][1] == W ) {
        while (rubiks->faces[FRONT].grid[1][1] != G)
            rotate_rubiks_clockwise(rubiks);
    }
    else {
        while (rubiks->faces[FRONT].grid[1][1] != W)
            rotate_rubiks_clockwise(rubiks);
        rotate_rubiks(rubiks);
        rotate_rubiks_clockwise(rubiks);
        rotate_rubiks_clockwise(rubiks);
    }

    while (good != 1) {
        printf("Please put the green face in front of you and the white face on top.\n"
                "Enter 1 when you are good.");
        scanf("%d", &good);

    }

    while (good != 1) {
        printf("White Cross\n");
        white_cross(rubiks);
        display_rubiks(rubiks);
        display_movements(rubiks);
        printf("Enter 1 when you are set. ");
        scanf("%d", &good);
    }
    good=0;

    while (good != 1) {
        printf("White Face\n");
        white_face(rubiks);
        display_rubiks(rubiks);
        display_movements(rubiks);
        printf("Enter 1 when you are set. ");
        scanf("%d", &good);
    }
    good=0;

    printf("Please rotate the cube upside down.\n");

    while (good != 1) {
        printf("Second Layer\n");
        second_layer(rubiks);
        display_rubiks(rubiks);
        display_movements(rubiks);
        printf("Enter 1 when you are set. ");
        scanf("%d", &good);
    }
    good=0;

    while (good != 1) {
        printf("Yellow Cross\n");
        yellow_cross(rubiks);
        display_rubiks(rubiks);
        display_movements(rubiks);
        printf("Enter 1 when you are set. ");
        scanf("%d", &good);
    }
    good=0;

    while (good != 1) {
        printf("Perfect Yellow Cross\n");
        perfect_yellow_cross(rubiks);
        display_rubiks(rubiks);
        display_movements(rubiks);
        printf("Enter 1 when you are set. ");
        scanf("%d", &good);
    }
    good=0;

    while (good != 1) {
        printf("Yellow Corners\n");
        yellow_corners(rubiks);
        display_rubiks(rubiks);
        display_movements(rubiks);
        printf("Enter 1 when you are set. ");
        scanf("%d", &good);
    }
    good=0;

    printf("Finished Cube\n");
    perfect_cube(rubiks);
    display_rubiks(rubiks);
    display_movements(rubiks);
    printf("Press enter when you are done. ");
    c_getch();

    printf("Well played !\n");
}

/*
 * Function : solve_fast
 * -----------------------------------------
 *
 * Computer solving rubiks cube.
 * Used to check if rubiks cube is solvable.
 */

int solve_fast(RUBIKS* rubiks) {

    return (white_cross(rubiks) || white_face(rubiks) || second_layer(rubiks) ||
    yellow_cross(rubiks) || perfect_yellow_cross(rubiks) || yellow_corners(rubiks) || perfect_cube(rubiks));
}

/*
 * Function : speedrun_rubiks
 * -------------------------------------
 *
 * Solves the rubiks as fast as possible
 * Displays time used to perform it.
 * Allows the user to record them time
 */

void speedrun_rubiks(RUBIKS* rubiks) {

    display_movements(rubiks);
    int good=0;
    clock_t start, stopC, stopP;
    do {
        printf("Enter 1 when you're ready.\n"
               "Then, press enter to end the timer !");
        scanf("%d", &good);
    }
    while (good != 1);
    start=clock();
    solve_fast(rubiks);
    stopC = clock();
    c_getch();

    stopP = clock();
    printf("It took me %f milliseconds to finish the cube :)\n"
           "It took you %f seconds.", (double)(stopC-start)/(double)CLOCKS_PER_SEC*1000,
           (double)(stopP-start)/(double)CLOCKS_PER_SEC);
}

/*
 * Function : middle_white
 * --------------------------------------
 *
 * returns : location of UP side location
 * starting from the bottom
 *
 * type    : T_SIDE
 */

T_SIDE middle_white(RUBIKS* rubiks) {

    int i;
    for (i = 5; i > 0; i--) {
        if (rubiks->faces[i].grid[0][1] == rubiks->faces[UP].grid[1][1]  ||
        rubiks->faces[i].grid[1][0] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[i].grid[1][2] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[i].grid[2][1] == rubiks->faces[UP].grid[1][1])
            return i;
    }
    return 0;
}


/*
 * Function : corner_white
 * ----------------------------------------
 *
 * returns : location of UP corner location
 * starting from the bottom
 *
 * type    : int
 */

T_SIDE corner_white(RUBIKS* rubiks)  {

    int i;
    for (i=5; i > 0;i--)
        if (rubiks->faces[i].grid[0][0] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[i].grid[0][2] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[i].grid[2][0] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[i].grid[2][2] == rubiks->faces[UP].grid[1][1])
            return i;

    return 0;
}


/*
 * Function : all_four_white
 * -------------------------------------------
 *
 * returns : 1 if all UP side faces are white.
 *
 * type    : int
 */

int all_four_white(RUBIKS* rubiks) {
    return rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1] &&
           rubiks->faces[UP].grid[1][0] == rubiks->faces[UP].grid[1][1] &&
           rubiks->faces[UP].grid[1][2] == rubiks->faces[UP].grid[1][1] &&
           rubiks->faces[UP].grid[2][1] == rubiks->faces[UP].grid[1][1];
}


/*
 * Function : perfect_cross
 * ---------------------------------------------------------
 *
 * returns : 1 if all UP side faces are white + well placed.
 *
 * type    : int
 */

int perfect_cross(RUBIKS* rubiks) {
    return all_four_white(rubiks) &&
    rubiks->faces[LEFT].grid[0][1] == rubiks->faces[LEFT].grid[1][1] &&
    rubiks->faces[FRONT].grid[0][1] == rubiks->faces[FRONT].grid[1][1] &&
    rubiks->faces[RIGHT].grid[0][1] == rubiks->faces[RIGHT].grid[1][1] &&
    rubiks->faces[BACK].grid[0][1] == rubiks->faces[BACK].grid[1][1];
}


/*
 * Function : white_cross
 * ------------------------------------------------------------------------------------------------------
 *
 * Creates a white cross on the rubiks cube.
 *
 * First step is to check if there is a white face where we are rotating
 * Then, we rotate the rubiks such as all faces are up even  if there are not facing the right direction.
 * Finally we make the right cross by rotating the faces accordingly.
 */

int white_cross(RUBIKS* rubiks) {

    int cpt = 0;
    T_SIDE location = middle_white(rubiks); // location stores face name + grid pos of white face

        while (location && cpt < 1000) { // while the white cross isn't there

            switch (location) {
                case DOWN :
                    while (rubiks->faces[DOWN].grid[1][2] != rubiks->faces[UP].grid[1][1]) // while it's not in [1][2]
                        rotate_down(rubiks);
                    while (rubiks->faces[UP].grid[1][2] ==
                           rubiks->faces[UP].grid[1][1]) // while there is white where u r rotating
                        rotate_up(rubiks);
                    rotate_right(rubiks);        // move face up
                    rotate_right(rubiks);        // to make it up
                    break;
                case BACK :
                    while (rubiks->faces[BACK].grid[1][2] != rubiks->faces[UP].grid[1][1])
                        rotate_back(rubiks);
                    while (rubiks->faces[UP].grid[1][0] == rubiks->faces[UP].grid[1][1])
                        rotate_up(rubiks);
                    rotate_left(rubiks);
                    break;
                case RIGHT :
                    while (rubiks->faces[RIGHT].grid[1][2] != rubiks->faces[UP].grid[1][1])
                        rotate_right(rubiks);
                    while (rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1])
                        rotate_up(rubiks);
                    rotate_back(rubiks);
                    break;
                case FRONT :
                    while (rubiks->faces[FRONT].grid[1][2] != rubiks->faces[UP].grid[1][1])
                        rotate_front(rubiks);
                    while (rubiks->faces[UP].grid[1][2] == rubiks->faces[UP].grid[1][1])
                        rotate_up(rubiks);
                    rotate_right(rubiks);
                    break;
                case LEFT :
                    while (rubiks->faces[LEFT].grid[1][2] != rubiks->faces[UP].grid[1][1])
                        rotate_left(rubiks);
                    while (rubiks->faces[UP].grid[2][1] == rubiks->faces[UP].grid[1][1])
                        rotate_up(rubiks);
                    rotate_front(rubiks);
                    break;
                default :
                    exit(EXIT_FAILURE);
            }
            location = middle_white(rubiks);

            cpt++;
        }

        while (rubiks->faces[FRONT].grid[0][1] != rubiks->faces[FRONT].grid[1][1]) { // green on top of front face
            rotate_up(rubiks);
            cpt++;
        }
        while (!(perfect_cross(rubiks)) && cpt < 1000) {
            if (rubiks->faces[LEFT].grid[0][1] == rubiks->faces[LEFT].grid[1][1] &&
                rubiks->faces[BACK].grid[0][1] != rubiks->faces[BACK].grid[1][1]) {
                rotate_right(rubiks);
                rotate_up(rubiks);
                rotate_rightC(rubiks);
                rotate_upC(rubiks);
                rotate_right(rubiks);

            }
            if (rubiks->faces[RIGHT].grid[0][1] == rubiks->faces[RIGHT].grid[1][1] &&
                rubiks->faces[BACK].grid[0][1] != rubiks->faces[BACK].grid[1][1]) {
                rotate_leftC(rubiks);
                rotate_upC(rubiks);
                rotate_left(rubiks);
                rotate_up(rubiks);
                rotate_leftC(rubiks);

            }
            if (rubiks->faces[RIGHT].grid[0][1] != rubiks->faces[RIGHT].grid[1][1] &&
                rubiks->faces[LEFT].grid[0][1] != rubiks->faces[LEFT].grid[1][1]) {
                rotate_right(rubiks);
                rotate_right(rubiks);
                rotate_left(rubiks);
                rotate_left(rubiks);
                rotate_down(rubiks);
                rotate_down(rubiks);
                rotate_right(rubiks);
                rotate_right(rubiks);
                rotate_left(rubiks);
                rotate_left(rubiks);

            }
            cpt++;
        }
    if (cpt==1000)
        return 1;
    return 0;
}


/*
 * Function : solve_back
 * ------------------------------------------------
 *
 * Solves the cube when white is in front position.
 */

void solve_back(RUBIKS* rubiks) {

    rotate_back(rubiks);
    rotate_down(rubiks);
    rotate_backC(rubiks);
}


/*
 * Function : solve_front
 * ------------------------------------------------
 *
 * Solves the cube when white is in front position.
 */

void solve_front(RUBIKS* rubiks) {

    rotate_front(rubiks);
    rotate_down(rubiks);
    rotate_frontC(rubiks);
}


/*
 * Function : solve_right
 * ------------------------------------------------
 *
 * Solves the cube when white is in front position.
 */

void solve_right(RUBIKS* rubiks) {

    rotate_right(rubiks);
    rotate_down(rubiks);
    rotate_rightC(rubiks);
}


/*
 * Function : solve_left
 * ------------------------------------------------
 *
 * Solves the cube when white is in front position.
 */

void solve_left(RUBIKS* rubiks) {

    rotate_left(rubiks);
    rotate_down(rubiks);
    rotate_leftC(rubiks);
}


/*
 * Function : white_face
 * ----------------------------------------------------------------------------------------
 *
 * Finishes the white face
 *
 * First step is to check if white sides are not well placed and remove them from top side
 * Then, for each location possible we put the face in 2-2
 * Finally we check what are the colors of the corner and put it in the right position
 */

int white_face(RUBIKS* rubiks) {

    int cpt = 0;
    T_SIDE location;

    //removing not well placed square from top layer
    if (rubiks->faces[UP].grid[0][0] == rubiks->faces[UP].grid[1][1] &&
        (rubiks->faces[LEFT].grid[0][0] != rubiks->faces[LEFT].grid[1][1] ||
         rubiks->faces[BACK].grid[0][2] != rubiks->faces[BACK].grid[1][1])) {
        rotate_leftC(rubiks);
        rotate_downC(rubiks);
        rotate_left(rubiks);
    }
    if (rubiks->faces[UP].grid[0][2] == rubiks->faces[UP].grid[1][1] &&
        (rubiks->faces[RIGHT].grid[0][2] != rubiks->faces[RIGHT].grid[1][1] ||
         rubiks->faces[BACK].grid[0][0] != rubiks->faces[BACK].grid[1][1])) {
        rotate_right(rubiks);
        rotate_downC(rubiks);
        rotate_rightC(rubiks);
    }
    if (rubiks->faces[UP].grid[2][0] == rubiks->faces[UP].grid[1][1] &&
        (rubiks->faces[LEFT].grid[0][2] != rubiks->faces[LEFT].grid[1][1] ||
         rubiks->faces[FRONT].grid[0][0] != rubiks->faces[FRONT].grid[1][1])) {
        rotate_left(rubiks);
        rotate_downC(rubiks);
        rotate_leftC(rubiks);
    }
    if (rubiks->faces[UP].grid[2][2] == rubiks->faces[UP].grid[1][1] &&
        (rubiks->faces[FRONT].grid[0][2] != rubiks->faces[FRONT].grid[1][1] ||
         rubiks->faces[RIGHT].grid[0][0] != rubiks->faces[RIGHT].grid[1][1])) {
        rotate_rightC(rubiks);
        rotate_downC(rubiks);
        rotate_right(rubiks);
    }

    location = corner_white(rubiks);

    while (location && cpt < 1000) { // while there is still a location

        // the main objective is to put all white corners in 2 2
        location = corner_white(rubiks);
        switch (location) {

            case DOWN :
                while (rubiks->faces[DOWN].grid[0][0] != rubiks->faces[UP].grid[1][1])
                    rotate_down(rubiks);

                if ((rubiks->faces[FRONT].grid[2][0] == rubiks->faces[RIGHT].grid[1][1] &&
                     rubiks->faces[LEFT].grid[2][2] == rubiks->faces[BACK].grid[1][1]) ||
                    (rubiks->faces[FRONT].grid[2][0] == rubiks->faces[BACK].grid[1][1] &&
                     rubiks->faces[LEFT].grid[2][2] == rubiks->faces[LEFT].grid[1][1])) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);

                    rotate_backC(rubiks);
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    rotate_back(rubiks);
                    rotate_down(rubiks);
                    rotate_backC(rubiks);
                    rotate_downC(rubiks);
                    rotate_back(rubiks);
                } else if ((rubiks->faces[FRONT].grid[2][0] == rubiks->faces[FRONT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][2] == rubiks->faces[RIGHT].grid[1][1]) ||
                           (rubiks->faces[FRONT].grid[2][0] == rubiks->faces[RIGHT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][2] == rubiks->faces[FRONT].grid[1][1])) {
                    rotate_down(rubiks);

                    rotate_rightC(rubiks);
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    rotate_right(rubiks);
                    rotate_down(rubiks);
                    rotate_rightC(rubiks);
                    rotate_downC(rubiks);
                    rotate_right(rubiks);
                } else if ((rubiks->faces[FRONT].grid[2][0] == rubiks->faces[BACK].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][2] == rubiks->faces[LEFT].grid[1][1]) ||
                           (rubiks->faces[FRONT].grid[2][0] == rubiks->faces[LEFT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][2] == rubiks->faces[BACK].grid[1][1])) {
                    rotate_downC(rubiks);

                    rotate_leftC(rubiks);
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    rotate_left(rubiks);
                    rotate_down(rubiks);
                    rotate_leftC(rubiks);
                    rotate_downC(rubiks);
                    rotate_left(rubiks);
                } else {
                    rotate_rightC(rubiks);
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    rotate_right(rubiks);
                    rotate_down(rubiks);
                    rotate_rightC(rubiks);
                    rotate_downC(rubiks);
                    rotate_right(rubiks);
                }
                break;

            case BACK :
                if (rubiks->faces[BACK].grid[2][2] != rubiks->faces[UP].grid[1][1]) {
                    if (rubiks->faces[BACK].grid[0][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_backC(rubiks);
                        rotate_downC(rubiks);
                        rotate_back(rubiks);
                        rotate_down(rubiks);
                    }//now it's bottom left so 2 0, not in 2 2
                    if (rubiks->faces[BACK].grid[0][2] == rubiks->faces[UP].grid[1][1]) {
                        rotate_back(rubiks);
                        rotate_down(rubiks);
                        rotate_backC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[BACK].grid[2][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_backC(rubiks);
                        rotate_down(rubiks);
                        rotate_back(rubiks);
                        rotate_downC(rubiks);
                    }
                } //here we have a white corner on 2 2

                if ((rubiks->faces[DOWN].grid[2][0] == rubiks->faces[RIGHT].grid[1][1] &&
                     rubiks->faces[LEFT].grid[2][0] == rubiks->faces[BACK].grid[1][1]) ||
                    (rubiks->faces[DOWN].grid[2][0] == rubiks->faces[BACK].grid[1][1] &&
                     rubiks->faces[LEFT].grid[2][0] == rubiks->faces[RIGHT].grid[1][1])) {
                    rotate_downC(rubiks);
                    solve_right(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][0] == rubiks->faces[FRONT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[RIGHT].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][0] == rubiks->faces[RIGHT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[FRONT].grid[1][1])) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_front(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][0] == rubiks->faces[FRONT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[LEFT].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][0] == rubiks->faces[LEFT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[GREEN].grid[1][1])) {
                    rotate_down(rubiks);
                    solve_left(rubiks);
                } else {
                    solve_back(rubiks);
                }
                break;

            case RIGHT :
                if (rubiks->faces[RIGHT].grid[2][2] != rubiks->faces[UP].grid[1][1]) {
                    if (rubiks->faces[RIGHT].grid[0][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_rightC(rubiks);
                        rotate_downC(rubiks);
                        rotate_right(rubiks);
                        rotate_down(rubiks);
                    }
                    if (rubiks->faces[RIGHT].grid[0][2] == rubiks->faces[UP].grid[1][1]) {
                        rotate_right(rubiks);
                        rotate_down(rubiks);
                        rotate_rightC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[RIGHT].grid[2][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_rightC(rubiks);
                        rotate_down(rubiks);
                        rotate_right(rubiks);
                        rotate_downC(rubiks);
                    }
                }

                if ((rubiks->faces[DOWN].grid[2][2] == rubiks->faces[LEFT].grid[1][1] &&
                     rubiks->faces[BACK].grid[2][0] == rubiks->faces[BACK].grid[1][1]) ||
                    (rubiks->faces[DOWN].grid[2][2] == rubiks->faces[BACK].grid[1][1] &&
                     rubiks->faces[BACK].grid[2][0] == rubiks->faces[LEFT].grid[1][1])) {
                    rotate_down(rubiks);
                    solve_back(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][2] == rubiks->faces[FRONT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[RIGHT].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][2] == rubiks->faces[RIGHT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[FRONT].grid[1][1])) {
                    rotate_downC(rubiks);
                    solve_front(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][2] == rubiks->faces[FRONT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[LEFT].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][2] == rubiks->faces[LEFT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[FRONT].grid[1][1])) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_left(rubiks);
                } else {
                    solve_right(rubiks);
                }
                break;

            case FRONT :

                if (rubiks->faces[FRONT].grid[2][2] != rubiks->faces[UP].grid[1][1]) {
                    if (rubiks->faces[FRONT].grid[0][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_frontC(rubiks);
                        rotate_downC(rubiks);
                        rotate_front(rubiks);
                        rotate_down(rubiks);
                    }
                    if (rubiks->faces[FRONT].grid[0][2] == rubiks->faces[UP].grid[1][1]) {
                        rotate_front(rubiks);
                        rotate_down(rubiks);
                        rotate_frontC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[FRONT].grid[2][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_frontC(rubiks);
                        rotate_down(rubiks);
                        rotate_front(rubiks);
                        rotate_downC(rubiks);
                    }
                }

                if ((rubiks->faces[DOWN].grid[2][2] == rubiks->faces[LEFT].grid[1][1] &&
                     rubiks->faces[BACK].grid[2][0] == rubiks->faces[BACK].grid[1][1]) ||
                    (rubiks->faces[DOWN].grid[2][2] == rubiks->faces[BACK].grid[1][1] &&
                     rubiks->faces[BACK].grid[2][0] == rubiks->faces[LEFT].grid[1][1])) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_back(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][0] == rubiks->faces[RIGHT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[BACK].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][0] == rubiks->faces[BACK].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[RIGHT].grid[1][1])) {
                    rotate_down(rubiks);
                    solve_right(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][2] == rubiks->faces[FRONT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[LEFT].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][2] == rubiks->faces[LEFT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[FRONT].grid[1][1])) {
                    rotate_downC(rubiks);
                    solve_left(rubiks);
                } else
                    solve_front(rubiks);
                break;

            case LEFT :
                if (rubiks->faces[LEFT].grid[2][2] != rubiks->faces[UP].grid[1][1]) {
                    if (rubiks->faces[LEFT].grid[0][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_leftC(rubiks);
                        rotate_downC(rubiks);
                        rotate_left(rubiks);
                        rotate_down(rubiks);
                    }
                    if (rubiks->faces[LEFT].grid[0][2] == rubiks->faces[UP].grid[1][1]) {
                        rotate_left(rubiks);
                        rotate_down(rubiks);
                        rotate_leftC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[LEFT].grid[2][0] == rubiks->faces[UP].grid[1][1]) {
                        rotate_leftC(rubiks);
                        rotate_down(rubiks);
                        rotate_left(rubiks);
                        rotate_downC(rubiks);
                    }
                }

                if ((rubiks->faces[DOWN].grid[2][2] == rubiks->faces[LEFT].grid[1][1] &&
                     rubiks->faces[BACK].grid[2][0] == rubiks->faces[BACK].grid[1][1]) ||
                    (rubiks->faces[DOWN].grid[2][2] == rubiks->faces[BACK].grid[1][1] &&
                     rubiks->faces[BACK].grid[2][0] == rubiks->faces[LEFT].grid[1][1])) {
                    rotate_downC(rubiks);
                    solve_back(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][0] == rubiks->faces[RIGHT].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[BACK].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][0] == rubiks->faces[BACK].grid[1][1] &&
                            rubiks->faces[LEFT].grid[2][0] == rubiks->faces[RIGHT].grid[1][1])) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_right(rubiks);
                } else if ((rubiks->faces[DOWN].grid[2][2] == rubiks->faces[FRONT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[RIGHT].grid[1][1]) ||
                           (rubiks->faces[DOWN].grid[2][2] == rubiks->faces[RIGHT].grid[1][1] &&
                            rubiks->faces[BACK].grid[2][0] == rubiks->faces[FRONT].grid[1][1])) {
                    rotate_down(rubiks);
                    solve_front(rubiks);
                } else {
                    solve_left(rubiks);
                }
                break;

            default :
                exit(EXIT_FAILURE);
        }
        location = corner_white(rubiks);
        cpt++;
    }
    if (cpt==1000)
        return 1;
    return 0;
}


/*
 * Function : second_layer
 * --------------------------------------------------
 *
 * Solves second layer.
 *
 *
 * We look for every side, then solve it accordingly.
 *
 */

int second_layer(RUBIKS* rubiks) {

    int cpt=0;

    if (rubiks->faces[UP].grid[1][1] != Y) {
        rotate_rubiks(rubiks);
        rotate_rubiks(rubiks);
    }

    while (!(rubiks->faces[BACK].grid[1][0] == rubiks->faces[BACK].grid[1][1] &&
             rubiks->faces[BACK].grid[1][2] == rubiks->faces[BACK].grid[1][1] &&
             rubiks->faces[RIGHT].grid[1][0] == rubiks->faces[RIGHT].grid[1][1] &&
             rubiks->faces[RIGHT].grid[1][2] == rubiks->faces[RIGHT].grid[1][1] &&
             rubiks->faces[FRONT].grid[1][0] == rubiks->faces[FRONT].grid[1][1] &&
             rubiks->faces[FRONT].grid[1][2] == rubiks->faces[FRONT].grid[1][1] &&
             rubiks->faces[LEFT].grid[1][0] == rubiks->faces[LEFT].grid[1][1] &&
             rubiks->faces[LEFT].grid[1][2] == rubiks->faces[LEFT].grid[1][1]) && cpt<1000) {
        // while the crown isn't finished

        if ((rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[BACK].grid[0][1] == rubiks->faces[UP].grid[1][1]) &&
            (rubiks->faces[UP].grid[1][0] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[LEFT].grid[0][1] == rubiks->faces[UP].grid[1][1]) &&
            (rubiks->faces[UP].grid[1][2] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][1] == rubiks->faces[UP].grid[1][1]) &&
            (rubiks->faces[UP].grid[2][1] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][1] == rubiks->faces[UP].grid[1][1])) {
            //if there are only yellows on top && top sides



            while ((rubiks->faces[FRONT].grid[1][2] == rubiks->faces[FRONT].grid[1][1]) &&
                   (rubiks->faces[RIGHT].grid[1][0] == rubiks->faces[RIGHT].grid[1][1]) && cpt<1000) {
                //while the face is good in order to not move it
                rotate_rubiks_clockwise(rubiks);
                cpt++;
            }
            //then, swap one of the yellows by the wrong place piece
            front_rC(rubiks);

        }
        //by the end a good square is running on top


        while (rubiks->faces[FRONT].grid[0][1] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[UP].grid[2][1] == rubiks->faces[UP].grid[1][1] && cpt<1000) {
            rotate_rubiks_clockwise(rubiks);
            cpt++;
        }
        //while there is not a valid piece to be placed


        while (rubiks->faces[FRONT].grid[0][1] != rubiks->faces[FRONT].grid[1][1] && cpt<1000) {
            rotate_upC(rubiks);
            rotate_rubiks_clockwise(rubiks);
            cpt++;
        }
        if (rubiks->faces[UP].grid[2][1] == rubiks->faces[RIGHT].grid[1][1])
            front_r(rubiks);
        else
            front_l(rubiks);
        cpt++;
    }

    //Putting green back front
    while (rubiks->faces[FRONT].grid[1][1] != G && cpt<1000) {
        rotate_rubiks_clockwise(rubiks);
        cpt++;
    }

    if (cpt==1000)
        return 1;
    return 0;
}


/*
 * Function : yellow_cross
 * --------------------------------------------------
 *
 * Realizes a yellow cross on the top face
 *
 *
 * We look for every side, then solve it accordingly.
 *
 */

int yellow_cross(RUBIKS* rubiks) {

    int cpt=0;
    while (!(rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[1][0] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[1][2] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[2][1] == rubiks->faces[UP].grid[1][1]) &&
            cpt<1000) {

        // Step1 : Nothing
        if (rubiks->faces[UP].grid[0][1] != rubiks->faces[UP].grid[1][1] &&
        rubiks->faces[UP].grid[1][0] != rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[1][2] != rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[2][1] != rubiks->faces[UP].grid[1][1])
            //if there are no blue faces
            solve_ycross(rubiks);

        // Step2 : L
        if (!((rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1] &&
        rubiks->faces[UP].grid[2][1] == rubiks->faces[UP].grid[1][1]) ||
                ((rubiks->faces[UP].grid[1][0] == rubiks->faces[UP].grid[1][1] &&
                rubiks->faces[UP].grid[1][2] == rubiks->faces[UP].grid[1][1])))) {
                //if we have a yellow L, then we want it top left
            while (!(rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[1][0] == rubiks->faces[UP].grid[1][1]) && cpt<1000) {
                rotate_up(rubiks);
                cpt++;
            }
            solve_ycross(rubiks);
        }
        // Step3 : Bar
        if (rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1] &&
        rubiks->faces[UP].grid[2][1] == rubiks->faces[UP].grid[1][1])
            // if the bar is vertical
            rotate_up(rubiks);
        solve_ycross(rubiks);
        cpt++;
    }

    if (cpt==1000)
        return 1;
    return 0;
}


/*
 * Function : perfect_yellow_cross
 * --------------------------------------------------
 *
 * Solves the perfect yellow cross
 * Look for every side, then solve it accordingly.
 *
 */

int perfect_yellow_cross(RUBIKS* rubiks) {

    int cpt=0;

    while ((rubiks->faces[LEFT].grid[0][1] != rubiks->faces[LEFT].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][1] != rubiks->faces[FRONT].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][1] != rubiks->faces[RIGHT].grid[1][1] ||
            rubiks->faces[BACK].grid[0][1] != rubiks->faces[BACK].grid[1][1]) && cpt<1000) {
        //while the squares aren't well placed

        while (rubiks->faces[BACK].grid[0][1] != rubiks->faces[BACK].grid[1][1]) {
            rotate_up(rubiks);
            cpt++;
        }
        //while the front top square isn't matching the front color

        if (rubiks->faces[LEFT].grid[0][1] == rubiks->faces[LEFT].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][1] == rubiks->faces[FRONT].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][1] == rubiks->faces[RIGHT].grid[1][1]) {
            //if we are in good case : at least 2 sides matching

            //while the front face isn't good

            if (rubiks->faces[LEFT].grid[0][1] == rubiks->faces[LEFT].grid[1][1])
                rotate_rubiks_clockwise(rubiks);

            if (rubiks->faces[RIGHT].grid[0][1] == rubiks->faces[RIGHT].grid[1][1])
                solve_perf_ycross(rubiks);

            //if left is not the same then solve
            else {
                rotate_up(rubiks);
                solve_perf_ycross(rubiks);
                rotate_rubiks_clockwise(rubiks);
                rotate_rubiks_clockwise(rubiks);
                solve_perf_ycross(rubiks);
            }
        }
        else
            //if we are not in a good case (only 1 solution)
            rotate_rubiks_clockwise(rubiks);
        cpt++;
    }

    if (cpt==1000)
        return 1;
    return 0;
}


/*
 * Function : corner_spot
 * ------------------------------------
 *
 * Places top corner in a good position
 *
 */

int corner_spot(RUBIKS* rubiks) {

    int i;
    for (i=1;i<5;i++) {
        if ((rubiks->faces[FRONT].grid[0][2] == rubiks->faces[FRONT].grid[1][1] ||
        rubiks->faces[FRONT].grid[0][2] == rubiks->faces[UP].grid[1][1] ||
        rubiks->faces[FRONT].grid[0][2] == rubiks->faces[RIGHT].grid[1][1]) &&
                (rubiks->faces[UP].grid[2][2] == rubiks->faces[FRONT].grid[1][1] ||
                 rubiks->faces[UP].grid[2][2] == rubiks->faces[UP].grid[1][1] ||
                 rubiks->faces[UP].grid[2][2] == rubiks->faces[RIGHT].grid[1][1]) &&
                        (rubiks->faces[RIGHT].grid[0][0] == rubiks->faces[FRONT].grid[1][1] ||
                         rubiks->faces[RIGHT].grid[0][0] == rubiks->faces[UP].grid[1][1] ||
                         rubiks->faces[RIGHT].grid[0][0] == rubiks->faces[RIGHT].grid[1][1]))
            return 1;
        else
            rotate_rubiks_clockwise(rubiks);
    }
    return 0;
}


/*
 * Function : yellow_corners
 * -----------------------------------
 *
 * Places yellow corners in good spot
 *
 */

int yellow_corners(RUBIKS* rubiks) {

    int cpt=0;
    while(!(((rubiks->faces[FRONT].grid[0][2] == rubiks->faces[FRONT].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][2] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][2] == rubiks->faces[RIGHT].grid[1][1]) &&
           (rubiks->faces[UP].grid[2][2] == rubiks->faces[FRONT].grid[1][1] ||
            rubiks->faces[UP].grid[2][2] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[UP].grid[2][2] == rubiks->faces[RIGHT].grid[1][1]) &&
           (rubiks->faces[RIGHT].grid[0][0] == rubiks->faces[FRONT].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][0] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][0] == rubiks->faces[RIGHT].grid[1][1]))

          &&

          ((rubiks->faces[RIGHT].grid[0][2] == rubiks->faces[RIGHT].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][2] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][2] == rubiks->faces[BACK].grid[1][1]) &&
           (rubiks->faces[UP].grid[1][2] == rubiks->faces[RIGHT].grid[1][1] ||
            rubiks->faces[UP].grid[1][2] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[UP].grid[1][2] == rubiks->faces[BACK].grid[1][1]) &&
           (rubiks->faces[BACK].grid[0][0] == rubiks->faces[RIGHT].grid[1][1] ||
            rubiks->faces[BACK].grid[0][0] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[BACK].grid[0][0] == rubiks->faces[BACK].grid[1][1]))

          &&

          ((rubiks->faces[BACK].grid[0][2] == rubiks->faces[BACK].grid[1][1] ||
            rubiks->faces[BACK].grid[0][2] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[BACK].grid[0][2] == rubiks->faces[LEFT].grid[1][1]) &&
           (rubiks->faces[UP].grid[0][1] == rubiks->faces[BACK].grid[1][1] ||
            rubiks->faces[UP].grid[0][1] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[UP].grid[0][1] == rubiks->faces[LEFT].grid[1][1]) &&
           (rubiks->faces[LEFT].grid[0][0] == rubiks->faces[BACK].grid[1][1] ||
            rubiks->faces[LEFT].grid[0][0] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[LEFT].grid[0][0] == rubiks->faces[LEFT].grid[1][1]))

          &&

          ((rubiks->faces[LEFT].grid[0][2] == rubiks->faces[LEFT].grid[1][1] ||
            rubiks->faces[LEFT].grid[0][2] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[LEFT].grid[0][2] == rubiks->faces[FRONT].grid[1][1]) &&
           (rubiks->faces[UP].grid[1][0] == rubiks->faces[LEFT].grid[1][1] ||
            rubiks->faces[UP].grid[1][0] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[UP].grid[1][0] == rubiks->faces[FRONT].grid[1][1]) &&
           (rubiks->faces[FRONT].grid[0][0] == rubiks->faces[LEFT].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][0] == rubiks->faces[UP].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][0] == rubiks->faces[FRONT].grid[1][1]))) && cpt<1000) {

        if (!(corner_spot(rubiks)))
            solve_corners(rubiks);
        //if no corners are good, do a blind algorithm

        corner_spot(rubiks);
        //put the right corner on top

        solve_corners(rubiks);
        //solve corners
        cpt++;
    }


    if (cpt==1000)
        return 1;
    return 0;
}


/*
 * Function : perfect_cube
 * -------------------------------
 *
 * Rotate non-good placed corners.
 *
 */

int perfect_cube(RUBIKS* rubiks) {

    int cpt=0;
    while (!(rubiks->faces[UP].grid[0][0] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[0][2] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[2][0] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[2][2] == rubiks->faces[UP].grid[1][1]) && cpt<1000) {

        while (rubiks->faces[UP].grid[2][2] != rubiks->faces[UP].grid[1][1] && cpt<1000) {
            rotate_rightC(rubiks);
            rotate_downC(rubiks);
            rotate_right(rubiks);
            rotate_down(rubiks);
            cpt++;
        }
        rotate_up(rubiks);
    }

    while (rubiks->faces[FRONT].grid[0][0] != rubiks->faces[FRONT].grid[1][1] && cpt<1000) {
        rotate_up(rubiks);
        cpt++;
    }
    cpt++;


    if (cpt==1000)
        return 1;
    return 0;
}


void test_movements(RUBIKS* rubiks) {

    display_rubiks(rubiks);

    rotate_up(rubiks);
    display_rubiks(rubiks);
    getchar();

    rotate_left(rubiks);
    display_rubiks(rubiks);
    getchar();

    rotate_front(rubiks);
    display_rubiks(rubiks);
    getchar();

    rotate_right(rubiks);
    display_rubiks(rubiks);
    getchar();

    rotate_back(rubiks);
    display_rubiks(rubiks);
    getchar();

    rotate_down(rubiks);
    display_rubiks(rubiks);
    getchar();


}