/* ==================================================
 *                   C PROJECT
 *               "The Rubik's Cube"
 * ==================================================
 *
 *  Wrote by Benjamin ROSSIGNOL              L1 INT-5
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
 *   5   Main
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
 * -----------------------
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
 * ------------------------
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
 * Function : return_side
 * ------------------------
 *
 * returns : side corresponding to color
 * type    : char
 */

T_SIDE return_side(T_COLOR color) {

    switch(color) {
        case R : return RIGHT;
        case B : return BACK;
        case G : return FRONT;
        case W : return UP;
        case O : return LEFT;
        case Y : return DOWN;
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
 * ------------------------
 *
 * returns : dynamically allocated address of cube
 * type    : RUBIKS*
 */

RUBIKS* create_rubiks() {

    return (RUBIKS*)malloc(sizeof(RUBIKS));

}

/*
 * Function : init_rubiks
 * ----------------------
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
 *=================
 * 2 DISPLAY & FILL
 *=================
 */


/*
 * Function : blank_rubiks
 * -----------------------
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
 * Function : display_rubiks
 * -------------------------
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
 * ----------------------
 *
 * Frees the malloc-ated rubiks
 */

void free_rubiks(RUBIKS* rubiks) {
    free(rubiks);
}




void fill_rubiks(RUBIKS* rubiks) {
//TODO

}


/*
 * ===========
 * 3 ROTATIONS
 * ===========
 */

/*
 * Functions : rotate_face
 * ----------------------
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
 * Functions : {face_name}_clockwise
 * ----------------------
 *
 * Rotates a face in clockwise direction
 * For counterclockwise movements, this function is called three times
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
    // Rotating sides
    rubiks->faces[FRONT].grid[0][0] = rubiks->faces[RIGHT].grid[0][0];
    rubiks->faces[FRONT].grid[0][1] = rubiks->faces[RIGHT].grid[0][1];
    rubiks->faces[FRONT].grid[0][2] = rubiks->faces[RIGHT].grid[0][2];

    rubiks->faces[RIGHT].grid[0][0] = rubiks->faces[BACK].grid[0][0];
    rubiks->faces[RIGHT].grid[0][1] = rubiks->faces[BACK].grid[0][1];
    rubiks->faces[RIGHT].grid[0][2] = rubiks->faces[BACK].grid[0][2];

    rubiks->faces[BACK].grid[0][0] = rubiks->faces[LEFT].grid[0][0];
    rubiks->faces[BACK].grid[0][1] = rubiks->faces[LEFT].grid[0][1];
    rubiks->faces[BACK].grid[0][2] = rubiks->faces[LEFT].grid[0][2];

    rubiks->faces[LEFT].grid[0][0] = tempGrid[3][0];
    rubiks->faces[LEFT].grid[0][1] = tempGrid[3][1];
    rubiks->faces[LEFT].grid[0][2] = tempGrid[3][2];
}

void rotate_upC(RUBIKS* rubiks) {

    rotate_up(rubiks);
    rotate_up(rubiks);
    rotate_up(rubiks);
}

void rotate_left(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[LEFT].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[FRONT].grid[i][0]; // Stores temp FRONT side
    }
    // Rotates LEFT
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
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[FRONT].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[UP].grid[2][i]; // Stores temp UP side
    }

    // Rotating FRONT face
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[FRONT].grid[i][j] = tempGrid[2-j][i];
    }
    // Rotating sides
    rubiks->faces[UP].grid[2][0] = rubiks->faces[LEFT].grid[2][2];
    rubiks->faces[UP].grid[2][1] = rubiks->faces[LEFT].grid[1][2];
    rubiks->faces[UP].grid[2][2] = rubiks->faces[LEFT].grid[0][2];

    rubiks->faces[LEFT].grid[0][2] = rubiks->faces[DOWN].grid[0][0];
    rubiks->faces[LEFT].grid[1][2] = rubiks->faces[DOWN].grid[0][1];
    rubiks->faces[LEFT].grid[2][2] = rubiks->faces[DOWN].grid[0][2];

    rubiks->faces[DOWN].grid[0][0] = rubiks->faces[RIGHT].grid[2][0];
    rubiks->faces[DOWN].grid[0][1] = rubiks->faces[RIGHT].grid[1][0];
    rubiks->faces[DOWN].grid[0][2] = rubiks->faces[RIGHT].grid[0][0];

    rubiks->faces[RIGHT].grid[0][0] = tempGrid[3][0];
    rubiks->faces[RIGHT].grid[1][0] = tempGrid[3][1];
    rubiks->faces[RIGHT].grid[2][0] = tempGrid[3][2];

}

void rotate_frontC(RUBIKS* rubiks) {

    rotate_front(rubiks);
    rotate_front(rubiks);
    rotate_front(rubiks);
}

void rotate_right(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[RIGHT].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[FRONT].grid[i][2]; // Stores temp UP side
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
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[BACK].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[UP].grid[0][i]; // Stores temp UP side
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[BACK].grid[i][j] = tempGrid[2-j][i];
    }

    rubiks->faces[UP].grid[0][0] = rubiks->faces[RIGHT].grid[0][2];
    rubiks->faces[UP].grid[0][1] = rubiks->faces[RIGHT].grid[1][2];
    rubiks->faces[UP].grid[0][2] = rubiks->faces[RIGHT].grid[2][2];

    rubiks->faces[RIGHT].grid[0][2] = rubiks->faces[DOWN].grid[2][2];
    rubiks->faces[RIGHT].grid[1][2] = rubiks->faces[DOWN].grid[2][1];
    rubiks->faces[RIGHT].grid[2][2] = rubiks->faces[DOWN].grid[2][0];

    rubiks->faces[DOWN].grid[2][0] = rubiks->faces[LEFT].grid[0][0];
    rubiks->faces[DOWN].grid[2][1] = rubiks->faces[LEFT].grid[1][0];
    rubiks->faces[DOWN].grid[2][2] = rubiks->faces[LEFT].grid[2][0];

    rubiks->faces[LEFT].grid[0][0] = tempGrid[3][2];
    rubiks->faces[LEFT].grid[1][0] = tempGrid[3][1];
    rubiks->faces[LEFT].grid[2][0] = tempGrid[3][0];

}

void rotate_backC(RUBIKS* rubiks) {

    rotate_back(rubiks);
    rotate_back(rubiks);
    rotate_back(rubiks);
}

void rotate_down(RUBIKS* rubiks) {

    int i, j;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[DOWN].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[FRONT].grid[2][i]; // Stores temp UP side
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

    white_cross(rubiks);
    white_face(rubiks);

}

/*
 * Function : middle_white
 * ------------------------
 *
 * returns : location of white middle location
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
 * Function : perfect_white
 * ------------------------
 *
 * returns : 1 if full white face.
 *
 * type    : int
 */

int perfect_white(RUBIKS* rubiks) {

    int i, j;
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            if (rubiks->faces[UP].grid[i][j] != W)
                return 0;
        }
    }
    return 1;
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

    T_SIDE location;

    while (!(all_four_white(rubiks))) { // while the white cross isn't there
        location = middle_white(rubiks); // location stores face name + grid pos of white face

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

void white_face(RUBIKS* rubiks) {
    //TODO
    printf("start\n");
    T_SIDE location;
    T_COLOR color1, color2, tempCol; //stores colors next to white corner

    if (rubiks->faces[UP].grid[0][0] == W && (rubiks->faces[LEFT].grid[0][0] != O ||
                                              rubiks->faces[BACK].grid[0][2] != B)) {
        rotate_leftC(rubiks);
        rotate_downC(rubiks);
        rotate_left(rubiks);
    }
    if (rubiks->faces[UP].grid[0][2] == W && (rubiks->faces[RIGHT].grid[0][2] != R ||
                                              rubiks->faces[BACK].grid[0][0] != B)) {
        printf("c le k\n");
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
    while (!(perfect_white(rubiks))) { // while the white cross isn't there
        display_rubiks(rubiks);
//removing not well placed square from top layer

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
                    }//now it's bottom left
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
                } //here we have a white corner on 2 2

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
                    }//now it's bottom left
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
                } //here we have a white corner on 2 2

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
                    }//now it's bottom left
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
                } //here we have a white corner on 2 2

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

    }
}
