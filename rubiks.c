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
    }
}

/*
 * Function : side_to_color
 * ------------------------
 *
 * returns : matching color from default side name
 * Top color is White, Left one is Orange etc.
 * type    : T_COLOR
 */

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

    }
}

/*
 * Function : side_to_index
 * ------------------------
 *
 * returns : matching array index from side name
 * rubiks.faces[0] corresponds to the UP face
 * type    : int
 */



T_COLOR return_rand_color(int number) {
    return number;
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
        rubiks->faces[i].side = i;
        for (j=0;j<3;j++) {
            for (k=0;k<3;k++)
                rubiks->faces[i].grid[j][k] = side_to_color(rubiks->faces[i].side);
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
    };
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
};




void fill_rubiks(RUBIKS* rubiks) {
    int color_arr[] = {0,0,0,0,0,0}, i, j, k; /* store color recurrence*/
    int face, coord[2]; /* to printf - scanf */
    char color;
    for (i=0;i<6;i++) {
        for (j=0;j<3;j++) {
            for (k=0;k<3;k++)
                color_arr[rubiks->faces[i].grid[j][k]]++;
        }
    }
    printf("Please specify the face, the coordinates of the box and the color "
           "to be changed.");
    scanf("%d %d %d %c", face, coord[0], coord[1], color);
    rubiks->faces[face].grid[coord[0]][coord[1]] = color;
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
            case UP : rotate_up(rubiks); break;
            case LEFT : rotate_left(rubiks); break;
            case FRONT : rotate_front(rubiks); break;
            case RIGHT : rotate_right(rubiks); break;
            case BACK : rotate_back(rubiks); break;
            case DOWN : rotate_down(rubiks); break;
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
    //lmao that works too
    //fuck this project
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
    for (i=0;i<3;i++) {
        rubiks->faces[FRONT].grid[0][i] = rubiks->faces[RIGHT].grid[0][i];
        rubiks->faces[RIGHT].grid[0][i] = rubiks->faces[BACK].grid[0][i];
        rubiks->faces[BACK].grid[0][i] = rubiks->faces[LEFT].grid[0][i];
        rubiks->faces[LEFT].grid[0][i] = tempGrid[3][i];
    }
}

void rotate_upC(RUBIKS* rubiks) {

    rotate_up(rubiks);
    rotate_up(rubiks);
    rotate_up(rubiks);
}

void rotate_left(RUBIKS* rubiks) {
    //works









    //ffs stop reading BITCH

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
        rubiks->faces[UP].grid[i][0] = rubiks->faces[BACK].grid[2-i][2];
        rubiks->faces[BACK].grid[2-i][2] = rubiks->faces[DOWN].grid[i][0];
        rubiks->faces[DOWN].grid[i][0] = tempGrid[3][i];
    }
}

void rotate_leftC(RUBIKS* rubiks) {

    rotate_left(rubiks);
    rotate_left(rubiks);
    rotate_left(rubiks);
}

void rotate_front(RUBIKS* rubiks) {

    /*works omg
    //PLEASE DONT TOUCH
    //PLEASE FFS MAN
    //why am i putting '//' am i retarded ?*/
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
    for (i=0;i<3;i++) {
        rubiks->faces[UP].grid[2][i] = rubiks->faces[LEFT].grid[i][2];
        rubiks->faces[LEFT].grid[i][2] = rubiks->faces[DOWN].grid[0][i];
        rubiks->faces[DOWN].grid[0][i] = rubiks->faces[RIGHT].grid[i][0];
        rubiks->faces[RIGHT].grid[i][0] = tempGrid[3][i];
    }
}

void rotate_frontC(RUBIKS* rubiks) {

    rotate_front(rubiks);
    rotate_front(rubiks);
    rotate_front(rubiks);
}

void rotate_right(RUBIKS* rubiks) {
    //wip JK IT FUCKING WORKS

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

    for (i=0;i<3;i++) {
        rubiks->faces[UP].grid[0][i] = rubiks->faces[RIGHT].grid[i][2];
        rubiks->faces[RIGHT].grid[i][2] = rubiks->faces[DOWN].grid[2][i];
        rubiks->faces[DOWN].grid[2][i] = rubiks->faces[LEFT].grid[i][0];
        rubiks->faces[LEFT].grid[i][0] = tempGrid[3][i];
    }
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
 * This function then calls rotate_face with theses tho arguments
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
 * type    : int*
 */

int middle_white(RUBIKS* rubiks) {

    int i;
    for (i = 5; i > 0; i--) {
        if (rubiks->faces[i].grid[0][1] == W || rubiks->faces[i].grid[1][0] == W || rubiks->faces[i].grid[1][2] == W ||
            rubiks->faces[i].grid[2][1] == W)
            return i;
    }
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

    int location;

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
        };
    }
    while (rubiks->faces[FRONT].grid[0][1] != G) // green on top of front face
        rotate_up(rubiks);

    //omg that is gonna suck so much
    while (!(perfect_cross(rubiks))) { // while u don't suck my dick for ages
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


void white_face(RUBIKS* rubiks) {
    display_rubiks(rubiks);

    while (!perfect_white(rubiks)) {
        while (rubiks->faces[UP].grid[0][0] != W && rubiks->faces[LEFT].grid[0][0] != O) {
            rotate_leftC(rubiks);
            rotate_downC(rubiks);
            rotate_left(rubiks);
            rotate_down(rubiks);
            printf("up");
        }/*
        while (rubiks->faces[UP].grid[2][0] != W && rubiks->faces[FRONT].grid[0][0] != G) {
            rotate_frontC(rubiks);
            rotate_downC(rubiks);
            rotate_front(rubiks);
            rotate_down(rubiks);

        }*/
        while (rubiks->faces[UP].grid[2][2] != W && rubiks->faces[RIGHT].grid[0][0] != R) {
            rotate_rightC(rubiks);
            rotate_downC(rubiks);
            rotate_right(rubiks);
            rotate_down(rubiks);
        }
        while (rubiks->faces[UP].grid[0][2] != W && rubiks->faces[BACK].grid[0][0] != B) {
            rotate_backC(rubiks);
            rotate_downC(rubiks);
            rotate_back(rubiks);
            rotate_down(rubiks);
            printf("back");
        }
        display_rubiks(rubiks);
    }
    printf("wesh");
}