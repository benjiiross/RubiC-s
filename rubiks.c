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
#include <time.h>

/*
 * =========
 * 0.5 LOGIC
 * =========
 */


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! USELESS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Function : select_color
 * -----------------------
 *
 * returns : color in whole letter to print in color in console
 * type    : int
 */

/*
int select_color(T_COLOR color) {

    switch(color) {
        case R : return RED;
        case B : return BLUE;
        case G : return GREEN;
        case W : return WHITE;
        case O : return LIGHTRED;
        case Y : return YELLOW;
        case LG :return LIGHTGRAY;
    }
}
*/
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
                rubiks->faces[side_to_index(i)].grid[j][k] = side_to_color(rubiks->faces[i].side);
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
        for (j=0;j<3;j++)
            printf("%c ", select_letter(rubiks->faces[0].grid[i][j])); /* TOP FACE */
        if (i<2)
            printf("\n        ");
    }
    printf("\n\n");
    for (i=0;i<3;i++) {
        for (j=1;j<5;j++) {
            for (k=0;k<3;k++)
                printf("%c ", select_letter(rubiks->faces[j].grid[i][k])); /* MID FACES (Lines faces)*/
            printf("  ");
        }
        printf("\n");
    };
    printf("\n        ");
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            printf("%c ", select_letter(rubiks->faces[5].grid[i][j])); /* BOTTOM FACE*/
        if (i<2)
            printf("\n        ");
    }
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

void up_clockwise(RUBIKS* rubiks) {
    //lmao that works too
    //fuck this project
    int i, j, k;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[side_to_index(UP)].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[side_to_index(FRONT)].grid[0][i]; // Stores temp FRONT side
    }

    // Rotating UP face
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[side_to_index(UP)].grid[i][j] = tempGrid[2-j][i];
    }
    // Rotating sides
    for (i=0;i<3;i++) {
        rubiks->faces[side_to_index(FRONT)].grid[0][i] = rubiks->faces[side_to_index(RIGHT)].grid[0][i];
        rubiks->faces[side_to_index(RIGHT)].grid[0][i] = rubiks->faces[side_to_index(BACK)].grid[0][i];
        rubiks->faces[side_to_index(BACK)].grid[0][i] = rubiks->faces[side_to_index(LEFT)].grid[0][i];
        rubiks->faces[side_to_index(LEFT)].grid[0][i] = tempGrid[3][i];
    }
}

void left_clockwise(RUBIKS* rubiks) {
    //works









    //ffs stop reading BITCH

    int i, j, k;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[side_to_index(LEFT)].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[side_to_index(FRONT)].grid[i][0]; // Stores temp FRONT side
    }
    // Rotates LEFT
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[side_to_index(LEFT)].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[side_to_index(FRONT)].grid[i][0] = rubiks->faces[side_to_index(UP)].grid[i][0];
        rubiks->faces[side_to_index(UP)].grid[i][0] = rubiks->faces[side_to_index(BACK)].grid[2-i][2];
        rubiks->faces[side_to_index(BACK)].grid[2-i][2] = rubiks->faces[side_to_index(DOWN)].grid[i][0];
        rubiks->faces[side_to_index(DOWN)].grid[i][0] = tempGrid[3][i];
    }
}

void front_clockwise(RUBIKS* rubiks) {

    /*works omg
    //PLEASE DONT TOUCH
    //PLEASE FFS MAN
    //why am i putting '//' am i retarded ?*/
    int i, j, k;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[side_to_index(FRONT)].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[side_to_index(UP)].grid[2][i]; // Stores temp UP side
    }

    // Rotating FRONT face
    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[side_to_index(FRONT)].grid[i][j] = tempGrid[2-j][i];
    }
    // Rotating sides
    for (i=0;i<3;i++) {
        rubiks->faces[side_to_index(UP)].grid[2][i] = rubiks->faces[side_to_index(LEFT)].grid[i][2];
        rubiks->faces[side_to_index(LEFT)].grid[i][2] = rubiks->faces[side_to_index(DOWN)].grid[0][i];
        rubiks->faces[side_to_index(DOWN)].grid[0][i] = rubiks->faces[side_to_index(RIGHT)].grid[i][0];
        rubiks->faces[side_to_index(RIGHT)].grid[i][0] = tempGrid[3][i];
    }
}

void right_clockwise(RUBIKS* rubiks) {
    //wip JK IT FUCKING WORKS

    int i, j, k;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[side_to_index(RIGHT)].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[side_to_index(FRONT)].grid[i][2]; // Stores temp UP side
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[side_to_index(RIGHT)].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[side_to_index(FRONT)].grid[i][2] = rubiks->faces[side_to_index(DOWN)].grid[i][2];
        rubiks->faces[side_to_index(DOWN)].grid[i][2] = rubiks->faces[side_to_index(BACK)].grid[2-i][0];
        rubiks->faces[side_to_index(BACK)].grid[2-i][0] = rubiks->faces[side_to_index(UP)].grid[i][2];
        rubiks->faces[side_to_index(UP)].grid[i][2] = tempGrid[3][i];
    }

}

void back_clockwise(RUBIKS* rubiks) {


    int i, j, k;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[side_to_index(BACK)].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[side_to_index(UP)].grid[0][i]; // Stores temp UP side
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[side_to_index(BACK)].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[side_to_index(UP)].grid[0][i] = rubiks->faces[side_to_index(RIGHT)].grid[i][2];
        rubiks->faces[side_to_index(RIGHT)].grid[i][2] = rubiks->faces[side_to_index(DOWN)].grid[2][i];
        rubiks->faces[side_to_index(DOWN)].grid[2][i] = rubiks->faces[side_to_index(LEFT)].grid[i][0];
        rubiks->faces[side_to_index(LEFT)].grid[i][0] = tempGrid[3][i];
    }
}

void down_clockwise(RUBIKS* rubiks) {

    int i, j, k;
    T_COLOR tempGrid[4][3]; // 3 sides of square + 1 temp side

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            tempGrid[i][j] = rubiks->faces[side_to_index(DOWN)].grid[i][j]; // Store temp grid
        tempGrid[3][i] = rubiks->faces[side_to_index(FRONT)].grid[2][i]; // Stores temp UP side
    }

    for (i=0;i<3;i++) {
        for(j=0;j<3;j++)
            rubiks->faces[side_to_index(DOWN)].grid[i][j] = tempGrid[2-j][i];
    }

    for (i=0;i<3;i++) {
        rubiks->faces[side_to_index(FRONT)].grid[2][i] = rubiks->faces[side_to_index(LEFT)].grid[2][i];
        rubiks->faces[side_to_index(LEFT)].grid[2][i] = rubiks->faces[side_to_index(BACK)].grid[2][i];
        rubiks->faces[side_to_index(BACK)].grid[2][i] = rubiks->faces[side_to_index(RIGHT)].grid[2][i];
        rubiks->faces[side_to_index(RIGHT)].grid[2][i] = tempGrid[3][i];
    }
}

/*
 * Function : scramble_rubiks
 * ----------------------
 *  !!!!! TO CHANGE !!!!!!
 * scrambles the rubiks by doing random movements
 */

void scramble_rubiks(RUBIKS* rubiks) {

    int i, j, k;
    int colors[2] = {8, 8};
    srand(time(NULL));
    for (i=0;i<6;i++) {
        for (j=0;j<3;j++) {
            for (k=0;k<3;k++)
                rubiks->faces[i].grid[j][k] = rand()%6;
        }

    }
    rubiks->faces[side_to_index(FRONT)].grid[1][1] = side_to_color(rubiks->faces[FRONT].side);
    rubiks->faces[side_to_index(UP)].grid[1][1] = side_to_color(rubiks->faces[UP].side);
    rubiks->faces[side_to_index(LEFT)].grid[1][1] = side_to_color(rubiks->faces[LEFT].side);
    rubiks->faces[side_to_index(RIGHT)].grid[1][1] = side_to_color(rubiks->faces[RIGHT].side);
    rubiks->faces[side_to_index(BACK)].grid[1][1] = side_to_color(rubiks->faces[BACK].side);
    rubiks->faces[side_to_index(DOWN)].grid[1][1] = side_to_color(rubiks->faces[DOWN].side);
}

int main() {
    RUBIKS *rubiks;

    rubiks = create_rubiks(); /* malloc */
    init_rubiks(rubiks);
    blank_rubiks(rubiks);
    scramble_rubiks(rubiks);
    display_rubiks(rubiks);


    blank_rubiks(rubiks);
    free_rubiks(rubiks);
    return 0;
}
