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
 *   3   Movements
 *   4   Solving Algorithms
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
}



/*
 * ================
 * 2 DISPLAY & FILL
 * ================
 */



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
 * Function : disp_main
 * -------------------------------------------
 *
 * Displays main
 */

void disp_main(RUBIKS* rubiks) {

    printf("--------------------------------------------------------------------------------\n"
           "Scramble : 1     Reset : 2     Blank : 3     Play : 4     Solve : 5     Exit : 6\n"
           "--------------------------------------------------------------------------------\n"
           "Action : ");

}


/*
 * Function : display_rubiks
 * -------------------------------------------
 *
 * Displays the rubiks with matching colors
 * Letters corresponds to colors of the rubiks
 */

void display_rubiks(RUBIKS* rubiks) {

    int i, j, k;

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
 * Function : free_rubiks
 * ----------------------------
 *
 * Frees the malloc-ated rubiks
 */

void free_rubiks(RUBIKS* rubiks) {
    free(rubiks);
}



/*
 * ===========
 * 3 ROTATIONS
 * ===========
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
 * --------------------------------------------------------------------
 *
 * Rotates a face in clockwise direction
 * For counterclockwise movements, this function is called three times.
 */

void rotate_up(RUBIKS* rubiks) {

    int i, j;

    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[UP].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[FRONT].grid[0][i]; // Stores temp FRONT side
    }

    // Rotating UP face
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[UP].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[FRONT].grid[0][i] = rubiks->faces[RIGHT].grid[0][i];
        rubiks->faces[RIGHT].grid[0][i] = rubiks->faces[BACK].grid[0][i];
        rubiks->faces[BACK].grid[0][i] = rubiks->faces[LEFT].grid[0][i];
        rubiks->faces[LEFT].grid[0][i] = tempGrid[3][i];
    }
    // Rotating sides
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
}

void rotate_downC(RUBIKS* rubiks) {

    rotate_down(rubiks);
    rotate_down(rubiks);
    rotate_down(rubiks);
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
 * ---------------------------------------------
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
 * ----------------------
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
}

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
            rubiks->faces[UP].grid[i][j] = rubiks->faces[DOWN].grid[2-i][2-j]; // swapping up/down
        }
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[DOWN].grid[2-i][2-j] = tempGrid[i][j]; // swapping down/up
        }
    }


    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            tempGrid[i][j] = rubiks->faces[RIGHT].grid[i][j];
        }
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[RIGHT].grid[i][j] = rubiks->faces[LEFT].grid[2-i][2-j];
        }
    }

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[LEFT].grid[2-i][2-j] = tempGrid[i][j];
        }
    }

    //rotating front
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            tempGrid[i][j] = rubiks->faces[FRONT].grid[i][j]; // storing up face
        }
    }
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[FRONT].grid[i][j] = tempGrid[2-i][2-j]; // storing up face
        }
    }

    //rotating back
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            tempGrid[i][j] = rubiks->faces[BACK].grid[i][j]; // storing up face
        }
    }
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            rubiks->faces[BACK].grid[i][j] = tempGrid[2-i][2-j]; // storing up face
        }
    }
}

/*
 * ====================
 * 4 SOLVING ALGORITHMS
 * ====================
 */

/*
 * Function : solve_rubiks
 * ------------------------
 *
 * Pretty straight-forward.
 */

void solve_rubiks(RUBIKS* rubiks) {

    display_rubiks(rubiks);

    printf("White Cross\n");
    white_cross(rubiks);
    display_rubiks(rubiks);

    printf("White Face\n");
    white_face(rubiks);
    display_rubiks(rubiks);

    rotate_rubiks(rubiks);
    printf("Second Layer\n");
    second_layer(rubiks);
    display_rubiks(rubiks);

    printf("Yellow Cross\n");
    yellow_cross(rubiks);
    display_rubiks(rubiks);

    printf("Perfect Yellow Cross\n");
    perfect_yellow_cross(rubiks);
    display_rubiks(rubiks);

    printf("Yellow Corners\n");
    yellow_corners(rubiks);
    display_rubiks(rubiks);

    printf("done\n");
    perfect_cube(rubiks);
    display_rubiks(rubiks);

}

/*
 * Function : middle_white
 * ------------------------
 *
 * returns : location of middle location
 * starting from the bottom
 * type    : T_SIDE
 */

T_SIDE middle_white(RUBIKS* rubiks) {

    int i;
    for (i = 5; i > 0; i--) {
        if (rubiks->faces[i].grid[0][1] == W || rubiks->faces[i].grid[1][0] == W || rubiks->faces[i].grid[1][2] == W ||
            rubiks->faces[i].grid[2][1] == W)
            return i;
    }
    return 0;
}

/*
 * Function : corner_white
 * ------------------------
 *
 * returns : location of white corner location
 * starting from the bottom
 * type    : int
 */

T_SIDE corner_white(RUBIKS* rubiks)  {

    int i;
    for (i=5; i > 0;i--)
        if (rubiks->faces[i].grid[0][0] == W || rubiks->faces[i].grid[0][2] == W || rubiks->faces[i].grid[2][0] == W ||
            rubiks->faces[i].grid[2][2] == W)
            return i;

    return 0;
}

/*
 * Function : crown_sides
 * ------------------------
 *
 * returns : location of crown_sides with 1 matching color
 * starting from the bottom
 * type    : int
 */

T_SIDE crown_sides(RUBIKS* rubiks, T_COLOR color)  {

    int i;
    for (i = 4 ; i > 0 ; i--) {
        if (rubiks->faces[i].grid[1][0] == color || rubiks->faces[i].grid[1][2] == color)
            return i;
    }
    if (rubiks->faces[UP].grid[0][0] == color || rubiks->faces[UP].grid[0][2] == color ||
    rubiks->faces[UP].grid[2][0] == color || rubiks->faces[UP].grid[2][2] == color)
        return UP;
    return -1;
}

/*
 * Function : all_four_white
 * ------------------------
 *
 * returns : 1 if all UP side faces are white.
 *
 * type    : int
 */

int all_four_white(RUBIKS* rubiks) {
    return (rubiks->faces[0].grid[0][1] == W && rubiks->faces[0].grid[1][0] == W && rubiks->faces[0].grid[1][2] == W &&
            rubiks->faces[0].grid[2][1] == W);
}

/*
 * Function : perfect_cross
 * ------------------------
 *
 * returns : 1 if all UP side faces are white + well placed.
 *
 * type    : int
 */

int perfect_cross(RUBIKS* rubiks) {
    return (all_four_white(rubiks) && rubiks->faces[LEFT].grid[0][1] == O && rubiks->faces[FRONT].grid[0][1] == G &&
    rubiks->faces[RIGHT].grid[0][1] == R && rubiks->faces[BACK].grid[0][1] == B);
}



/*
 * Function : white_cross
 * ----------------------
 *
 * Creates a white cross on the rubiks cube.
 *
 * First step is to check if there is a white face where we are rotating
 * Then, we rotate the rubiks such as all faces are up even  if there are not facing the right direction.
 * Finally we make the right cross by rotating the faces accordingly.
 */

void white_cross(RUBIKS* rubiks) {

    T_SIDE location = middle_white(rubiks); // location stores face name + grid pos of white face

    while (location) { // while the white cross isn't there

        switch(location) {
            case DOWN :
                while (rubiks->faces[DOWN].grid[1][2] != W) // while it's not in [1][2]
                    rotate_down(rubiks);
                while (rubiks->faces[UP].grid[1][2] == W) // while there is white where u r rotating
                    rotate_up(rubiks);
                rotate_right(rubiks);        // move face up
                rotate_right(rubiks);        // to make it up
                break;
            case BACK :
                while (rubiks->faces[BACK].grid[1][2] != W)
                    rotate_back(rubiks);
                while (rubiks->faces[UP].grid[1][0] == W)
                    rotate_up(rubiks);
                rotate_left(rubiks);
                break;
            case RIGHT :
                while (rubiks->faces[RIGHT].grid[1][2] != W)
                    rotate_right(rubiks);
                while (rubiks->faces[UP].grid[0][1] == W)
                    rotate_up(rubiks);
                rotate_back(rubiks);
                break;
            case FRONT :
                while (rubiks->faces[FRONT].grid[1][2] != W)
                    rotate_front(rubiks);
                while (rubiks->faces[UP].grid[1][2] == W)
                    rotate_up(rubiks);
                rotate_right(rubiks);
                break;
            case LEFT :
                while (rubiks->faces[LEFT].grid[1][2] != W)
                    rotate_left(rubiks);
                while (rubiks->faces[UP].grid[2][1] == W)
                    rotate_up(rubiks);
                rotate_front(rubiks);
                break;
            default :
                exit(EXIT_FAILURE);
        }
        location = middle_white(rubiks);
    }

    while (rubiks->faces[FRONT].grid[0][1] != G) // green on top of front face
        rotate_up(rubiks);

    while (!(perfect_cross(rubiks))) {
        if (rubiks->faces[LEFT].grid[0][1] == O && rubiks->faces[BACK].grid[0][1] != B) {
            rotate_right(rubiks);
            rotate_up(rubiks);
            rotate_rightC(rubiks);
            rotate_upC(rubiks);
            rotate_right(rubiks);

        }
        if (rubiks->faces[RIGHT].grid[0][1] == R && rubiks->faces[BACK].grid[0][1] != B) {
            rotate_leftC(rubiks);
            rotate_upC(rubiks);
            rotate_left(rubiks);
            rotate_up(rubiks);
            rotate_leftC(rubiks);

        }
        if (rubiks->faces[RIGHT].grid[0][1] != R && rubiks->faces[LEFT].grid[0][1] != O) {
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

    }
}


/*
 * Function : solve_back
 * ---------------------
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
 * ----------------------
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
 * ----------------------
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
 * ----------------------
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
 * ----------------------
 *
 * Finishes the white face
 *
 * First step is to check if white sides are not well placed and remove them from top side
 * Then, for each location possible we put the face in 2-2
 * Finally we check what are the colors of the corner and put it in the right position
 */

void white_face(RUBIKS* rubiks) {

    T_SIDE location;

    //removing not well placed square from top layer
    if (rubiks->faces[UP].grid[0][0] == W && (rubiks->faces[LEFT].grid[0][0] != O ||
                                              rubiks->faces[BACK].grid[0][2] != B)) {
        rotate_leftC(rubiks);
        rotate_downC(rubiks);
        rotate_left(rubiks);
    }
    if (rubiks->faces[UP].grid[0][2] == W && (rubiks->faces[RIGHT].grid[0][2] != R ||
                                              rubiks->faces[BACK].grid[0][0] != B)) {
        rotate_right(rubiks);
        rotate_downC(rubiks);
        rotate_rightC(rubiks);

    }
    if (rubiks->faces[UP].grid[2][0] == W && (rubiks->faces[LEFT].grid[0][2] != O ||
                                              rubiks->faces[FRONT].grid[0][0] != G)) {
        rotate_left(rubiks);
        rotate_downC(rubiks);
        rotate_leftC(rubiks);

    }
    if (rubiks->faces[UP].grid[2][2] == W && (rubiks->faces[FRONT].grid[0][2] != G ||
                                              rubiks->faces[RIGHT].grid[0][0] != R)) {
        rotate_rightC(rubiks);
        rotate_downC(rubiks);
        rotate_right(rubiks);
    }
    location = corner_white(rubiks);

    while (location) { // while there is still a location

        // the main objective is to put all white corners in 2 2
        location = corner_white(rubiks);
        switch (location) {

            case DOWN :
                while (rubiks->faces[DOWN].grid[0][0] != W)
                    rotate_down(rubiks);

                if ((rubiks->faces[FRONT].grid[2][0] == R && rubiks->faces[LEFT].grid[2][2] == B) ||
                        (rubiks->faces[FRONT].grid[2][0] == B && rubiks->faces[LEFT].grid[2][2] == R)) {
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
                }

                else if ((rubiks->faces[FRONT].grid[2][0] == G && rubiks->faces[LEFT].grid[2][2] == R) ||
                    (rubiks->faces[FRONT].grid[2][0] == R && rubiks->faces[LEFT].grid[2][2] == G)) {
                    rotate_down(rubiks);

                    rotate_rightC(rubiks);
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    rotate_right(rubiks);
                    rotate_down(rubiks);
                    rotate_rightC(rubiks);
                    rotate_downC(rubiks);
                    rotate_right(rubiks);
                }

                else if ((rubiks->faces[FRONT].grid[2][0] == B && rubiks->faces[LEFT].grid[2][2] == O) ||
                    (rubiks->faces[FRONT].grid[2][0] == O && rubiks->faces[LEFT].grid[2][2] == B)) {
                    rotate_downC(rubiks);

                    rotate_leftC(rubiks);
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    rotate_left(rubiks);
                    rotate_down(rubiks);
                    rotate_leftC(rubiks);
                    rotate_downC(rubiks);
                    rotate_left(rubiks);
                }

                else {
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
                if (rubiks->faces[BACK].grid[2][2] != W) {
                    if (rubiks->faces[BACK].grid[0][0] == W) {
                        rotate_backC(rubiks);
                        rotate_downC(rubiks);
                        rotate_back(rubiks);
                        rotate_down(rubiks);
                    }//now it's bottom left
                    if (rubiks->faces[BACK].grid[0][2] == W) {
                        rotate_back(rubiks);
                        rotate_down(rubiks);
                        rotate_backC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[BACK].grid[2][0] == W) {
                        rotate_backC(rubiks);
                        rotate_down(rubiks);
                        rotate_back(rubiks);
                        rotate_downC(rubiks);
                    }
                } //here we have a white corner on 2 2

                if ((rubiks->faces[DOWN].grid[2][0] == R && rubiks->faces[LEFT].grid[2][0] == B) ||
                    (rubiks->faces[DOWN].grid[2][0] == B && rubiks->faces[LEFT].grid[2][0] == R)) {
                    rotate_downC(rubiks);
                    solve_right(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[2][0] == G && rubiks->faces[LEFT].grid[2][0] == R) ||
                    (rubiks->faces[DOWN].grid[2][0] == R && rubiks->faces[LEFT].grid[2][0] == G)) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_front(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[2][0] == G && rubiks->faces[LEFT].grid[2][0] == O) ||
                    (rubiks->faces[DOWN].grid[2][0] == O && rubiks->faces[LEFT].grid[2][0] == G)) {
                    rotate_down(rubiks);
                    solve_left(rubiks);
                }

                else {
                    solve_back(rubiks);
                }
                break;

            case RIGHT :
                if (rubiks->faces[RIGHT].grid[2][2] != W) {
                    if (rubiks->faces[RIGHT].grid[0][0] == W) {
                        rotate_rightC(rubiks);
                        rotate_downC(rubiks);
                        rotate_right(rubiks);
                        rotate_down(rubiks);
                    }
                    if (rubiks->faces[RIGHT].grid[0][2] == W) {
                        rotate_right(rubiks);
                        rotate_down(rubiks);
                        rotate_rightC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[RIGHT].grid[2][0] == W) {
                        rotate_rightC(rubiks);
                        rotate_down(rubiks);
                        rotate_right(rubiks);
                        rotate_downC(rubiks);
                    }
                }

                if ((rubiks->faces[DOWN].grid[2][2] == O && rubiks->faces[BACK].grid[2][0] == B) ||
                    (rubiks->faces[DOWN].grid[2][2] == B && rubiks->faces[BACK].grid[2][0] == O)) {
                    rotate_down(rubiks);
                    solve_back(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[2][2] == G && rubiks->faces[BACK].grid[2][0] == R) ||
                    (rubiks->faces[DOWN].grid[2][2] == R && rubiks->faces[BACK].grid[2][0] == G)) {
                    rotate_downC(rubiks);
                    solve_front(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[2][2] == G && rubiks->faces[BACK].grid[2][0] == O) ||
                    (rubiks->faces[DOWN].grid[2][2] == O && rubiks->faces[BACK].grid[2][0] == G)) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_left(rubiks);
                }

                else {
                    solve_right(rubiks);
                }
                break;

            case FRONT :

                if (rubiks->faces[FRONT].grid[2][2] != W) {
                    if (rubiks->faces[FRONT].grid[0][0] == W) {
                        rotate_frontC(rubiks);
                        rotate_downC(rubiks);
                        rotate_front(rubiks);
                        rotate_down(rubiks);
                    }
                    if (rubiks->faces[FRONT].grid[0][2] == W) {
                        rotate_front(rubiks);
                        rotate_down(rubiks);
                        rotate_frontC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[FRONT].grid[2][0] == W) {
                        rotate_frontC(rubiks);
                        rotate_down(rubiks);
                        rotate_front(rubiks);
                        rotate_downC(rubiks);
                    }
                }

                if ((rubiks->faces[DOWN].grid[0][2] == O && rubiks->faces[RIGHT].grid[2][0] == B) ||
                    (rubiks->faces[DOWN].grid[0][2] == B && rubiks->faces[RIGHT].grid[2][0] == O)) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_back(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[0][2] == B && rubiks->faces[RIGHT].grid[2][0] == R) ||
                         (rubiks->faces[DOWN].grid[0][2] == R && rubiks->faces[RIGHT].grid[2][0] == B)) {
                    rotate_down(rubiks);
                    solve_right(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[0][2] == G && rubiks->faces[RIGHT].grid[2][0] == O) ||
                         (rubiks->faces[DOWN].grid[0][2] == O && rubiks->faces[RIGHT].grid[2][0] == G)) {
                    rotate_downC(rubiks);
                    solve_left(rubiks);
                }

                else
                    solve_front(rubiks);
                break;

            case LEFT :
                if (rubiks->faces[LEFT].grid[2][2] != W) {
                    if (rubiks->faces[LEFT].grid[0][0] == W) {
                        rotate_leftC(rubiks);
                        rotate_downC(rubiks);
                        rotate_left(rubiks);
                        rotate_down(rubiks);
                    }
                    if (rubiks->faces[LEFT].grid[0][2] == W) {
                        rotate_left(rubiks);
                        rotate_down(rubiks);
                        rotate_leftC(rubiks);
                        rotate_downC(rubiks);
                    }
                    if (rubiks->faces[LEFT].grid[2][0] == W) {
                        rotate_leftC(rubiks);
                        rotate_down(rubiks);
                        rotate_left(rubiks);
                        rotate_downC(rubiks);
                    }
                }

                if ((rubiks->faces[DOWN].grid[0][0] == O && rubiks->faces[FRONT].grid[2][0] == B) ||
                    (rubiks->faces[DOWN].grid[0][0] == B && rubiks->faces[FRONT].grid[2][0] == O)) {
                    rotate_downC(rubiks);
                    solve_back(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[0][0] == B && rubiks->faces[FRONT].grid[2][0] == R) ||
                         (rubiks->faces[DOWN].grid[0][0] == R && rubiks->faces[FRONT].grid[2][0] == B)) {
                    rotate_down(rubiks);
                    rotate_down(rubiks);
                    solve_right(rubiks);
                }

                else if ((rubiks->faces[DOWN].grid[0][0] == G && rubiks->faces[FRONT].grid[2][0] == R) ||
                         (rubiks->faces[DOWN].grid[0][0] == R && rubiks->faces[FRONT].grid[2][0] == G)) {
                    rotate_down(rubiks);
                    solve_front(rubiks);
                }

                else {
                    solve_left(rubiks);
                }
                break;

            default :
                exit(EXIT_FAILURE);
        }
        location = corner_white(rubiks);
    }
}

/*
 * Function : second_layer
 * -----------------------
 *
 * Solves second layer.
 *
 *
 * We look for every side, then solve it accordingly.
 *
 */

void second_layer(RUBIKS* rubiks) {

    while (!(rubiks->faces[BACK].grid[1][0] == rubiks->faces[BACK].grid[1][1] &&
             rubiks->faces[BACK].grid[1][2] == rubiks->faces[BACK].grid[1][1] &&
             rubiks->faces[RIGHT].grid[1][0] == rubiks->faces[RIGHT].grid[1][1] &&
             rubiks->faces[RIGHT].grid[1][2] == rubiks->faces[RIGHT].grid[1][1] &&
             rubiks->faces[FRONT].grid[1][0] == rubiks->faces[FRONT].grid[1][1] &&
             rubiks->faces[FRONT].grid[1][2] == rubiks->faces[FRONT].grid[1][1] &&
             rubiks->faces[LEFT].grid[1][0] == rubiks->faces[LEFT].grid[1][1] &&
             rubiks->faces[LEFT].grid[1][2] == rubiks->faces[LEFT].grid[1][1])) {
        // while the crown isn't finished

        if ((rubiks->faces[UP].grid[0][1] == Y || rubiks->faces[BACK].grid[0][1] == Y) &&
            (rubiks->faces[UP].grid[1][0] == Y || rubiks->faces[LEFT].grid[0][1] == Y) &&
            (rubiks->faces[UP].grid[1][2] == Y || rubiks->faces[RIGHT].grid[0][1] == Y) &&
            (rubiks->faces[UP].grid[2][1] == Y || rubiks->faces[FRONT].grid[0][1] == Y)) {
            //if there are only yellows on top && top sides



            while ((rubiks->faces[FRONT].grid[1][2] == rubiks->faces[FRONT].grid[1][1]) &&
                   (rubiks->faces[RIGHT].grid[1][0] == rubiks->faces[RIGHT].grid[1][1]))
                //while the face is good in order to not move it
                rotate_rubiks_clockwise(rubiks);
            //then, swap one of the yellows by the wrong place piece
            front_rC(rubiks);


        }
        //by the end a good square is running on top


        while (rubiks->faces[FRONT].grid[0][1] == Y || rubiks->faces[UP].grid[2][1] == Y)
            rotate_rubiks_clockwise(rubiks);
        //while there is not a valid piece to be placed


        while (rubiks->faces[FRONT].grid[0][1] != rubiks->faces[FRONT].grid[1][1]) {
            rotate_upC(rubiks);
            rotate_rubiks_clockwise(rubiks);
        }
        if (rubiks->faces[UP].grid[2][1] == (rubiks->faces[RIGHT].grid[1][1]))
            front_r(rubiks);
        else
            front_l(rubiks);
    }
}

/*
 * Function : yellow_cross
 * -----------------------
 *
 * Realizes a yellow cross on the top face
 *
 *
 * We look for every side, then solve it accordingly.
 *
 */

void yellow_cross(RUBIKS* rubiks) {

    if (!(rubiks->faces[UP].grid[0][1] == Y && rubiks->faces[UP].grid[1][0] == Y &&
            rubiks->faces[UP].grid[1][2] == Y && rubiks->faces[UP].grid[2][1] == Y)) {

        // Step1 : Nothing
        if (rubiks->faces[UP].grid[0][1] != Y && rubiks->faces[UP].grid[1][0] != Y &&
            rubiks->faces[UP].grid[1][2] != Y && rubiks->faces[UP].grid[2][1] != Y)
            //if there are no blue faces
            solve_ycross(rubiks);

        // Step2 : L
        if (!((rubiks->faces[UP].grid[0][1] == Y && rubiks->faces[UP].grid[2][1] == Y) ||
                ((rubiks->faces[UP].grid[1][0] == Y && rubiks->faces[UP].grid[1][2] == Y)))) {
                //if we have a yellow L
            while (!(rubiks->faces[UP].grid[0][1] == Y && rubiks->faces[UP].grid[1][0] == Y))
                rotate_up(rubiks);
            solve_ycross(rubiks);
        }
        // Step3 : Bar
        if (rubiks->faces[UP].grid[0][1] == Y && rubiks->faces[UP].grid[2][1] == Y)
            // if the bar is vertical
            rotate_up(rubiks);
        solve_ycross(rubiks);
    }
}
int is_cross_line(RUBIKS* rubiks) {
    //todo
    //returns if we are in a good position to algorithm :
    // if there is a line unfinished, right and left
    // if there is a L unfinished, front and left.
    return (1);
}

void perfect_yellow_cross(RUBIKS* rubiks) {

    while (rubiks->faces[LEFT].grid[0][1] != rubiks->faces[LEFT].grid[1][1] ||
            rubiks->faces[FRONT].grid[0][1] != rubiks->faces[FRONT].grid[1][1] ||
            rubiks->faces[RIGHT].grid[0][1] != rubiks->faces[RIGHT].grid[1][1] ||
            rubiks->faces[BACK].grid[0][1] != rubiks->faces[BACK].grid[1][1]) {
        //while the squares aren't well placed

        while (rubiks->faces[BACK].grid[0][1] != rubiks->faces[BACK].grid[1][1])
            rotate_up(rubiks);
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
    }
}

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

void yellow_corners(RUBIKS* rubiks) {

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
            rubiks->faces[FRONT].grid[0][0] == rubiks->faces[FRONT].grid[1][1])))) {

        if (!(corner_spot(rubiks)))
            solve_corners(rubiks);
        //if no corners are good, do a blind algorithm

        corner_spot(rubiks);
        //put the right corner on top

        solve_corners(rubiks);
        //solve corners

    }
}

void perfect_cube(RUBIKS* rubiks) {

    while (!(rubiks->faces[UP].grid[0][0] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[0][2] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[2][0] == rubiks->faces[UP].grid[1][1] &&
            rubiks->faces[UP].grid[2][2] == rubiks->faces[UP].grid[1][1])) {

        while (rubiks->faces[UP].grid[2][2] != rubiks->faces[UP].grid[1][1]) {
            rotate_rightC(rubiks);
            rotate_downC(rubiks);
            rotate_right(rubiks);
            rotate_down(rubiks);
        }
        rotate_up(rubiks);
    }

    while (rubiks->faces[FRONT].grid[0][0] != rubiks->faces[FRONT].grid[1][1])
        rotate_up(rubiks);
}