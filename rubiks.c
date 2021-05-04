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
#include <C:\Users\Benji\OneDrive - Efrei\Documents\Travail\L1\S2\Informatique générale\C\PROJECT\rubiks.h>
#include <C:\Users\Benji\OneDrive - Efrei\Documents\Travail\L1\S2\Informatique générale\C\PROJECT\conio.h>


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
 * Function : select_letter
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
    /*Returns address of dynamically allocated cube*/
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
        rubiks->faces[i].side = i; /* */
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
            printf("%c ", select_letter(rubiks->faces[0].grid[i][j]));
        if (i<2)
            printf("\n        ");
    }
    printf("\n\n");
    for (i=0;i<3;i++) {
        for (j=1;j<5;j++) {
            for (k=0;k<3;k++)
                printf("%c ", select_letter(rubiks->faces[j].grid[i][k]));
            printf("  ");
        }
        printf("\n");
    };
    printf("\n        ");
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++)
            printf("%c ", select_letter(rubiks->faces[5].grid[i][j]));
        if (i<2)
            printf("\n        ");
    }
    printf("\n=============================\n\n");
}

/*
 * Function : fill_rubiks
 * ----------------------
 *
 *
 *
 */

void fill_rubiks(RUBIKS* rubiks) {
    int color_arr[] = {0,0,0,0,0,0}, i, j, k;
    int face, coord[2];
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

int main() {
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
