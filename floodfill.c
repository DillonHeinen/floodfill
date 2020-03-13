#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Prototypes:

// Preconditions: File exists and grid has been instantiated
// Postconditions: Fills grid with file contents
void buildGrid(char fname[], char *grid[], int *numRows, int *numCols, FILE *fptr);

// Preconditions: Grid has been filled with file contents
// Postconditions: Grid is printed to the screen
void showGrid(char *grid[], int numRows, int numCols);

// Precondtions: Stack has been initialized and grid is filled
// Postconditions: Similar characters are pushed to the stack
void checkNeighbors(int rowSelect, int colSelect, char colorSelect, char *grid[], int numRows, int numCols);

void checkHelper(int rowSelect, int colSelect, char colorSelect, char *grid[], int numRows, int numCols, char check);

// Preconditions: File has been read and grid has been printed to screen successfully
// Postconditions: User is prompted and responses are saved in select locations
void prompt(int *rowSelect, int *colSelect, char *colorSelect, char *grid[], int numRows, int numCols, char fname[], FILE *fptr);

// Definitions:

void buildGrid(char fname[], char *grid[], int *numRows, int *numCols, FILE *fptr) {


    if (fptr == NULL) {
        printf("File Error\n");
        exit(-1);
    }
    else {
        char buf[BUFSIZ];
        int rowCount = 0;

        while (fgets(buf, sizeof(buf), fptr)) {
            grid[rowCount] = (char*) malloc(strlen(buf) + 1);     // allocate space for row of characters
            strcpy(grid[rowCount], buf);
            rowCount++;
        }

        *numRows = rowCount;
        *numCols = strlen(buf);

    }
}

void showGrid(char *grid[], int numRows, int numCols) {
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void checkNeighbors(int rowSelect, int colSelect, char colorSelect, char *grid[], int numRows, int numCols) {      // evaluates similar characters and converts to stack entry
    char check = grid[rowSelect][colSelect];
    if((rowSelect > -1 && rowSelect < numRows) && (colSelect > -1 && colSelect < numCols)) {
        checkHelper(rowSelect, colSelect, colorSelect, grid, numRows, numCols, check);
    }
}

void checkHelper(int rowSelect, int colSelect, char colorSelect, char *grid[], int numRows, int numCols, char check){
    if((rowSelect > -1 && rowSelect < numRows) && (colSelect > -1 && colSelect < numCols) && (grid[rowSelect][colSelect] == check)) {
        grid[rowSelect][colSelect] = colorSelect;

        if((rowSelect - 1 > -1 && rowSelect - 1 < numRows) && (colSelect - 1 > -1 && colSelect - 1 < numCols) && (grid[rowSelect - 1][colSelect - 1] == check)) {       //northwest
            checkHelper(rowSelect - 1, colSelect - 1, colorSelect, grid, numRows, numCols, check);
        }
        if((rowSelect  - 1 > -1 && rowSelect - 1 < numRows) && (colSelect > -1 && colSelect < numCols) && (grid[rowSelect - 1][colSelect] == check)) {       //north
            checkHelper(rowSelect - 1, colSelect, colorSelect, grid, numRows, numCols, check);
        }
        if((rowSelect - 1 > -1 && rowSelect - 1 < numRows) && (colSelect + 1 > -1 && colSelect + 1 < numCols) && (grid[rowSelect - 1][colSelect + 1] == check)) {       //northeast
            checkHelper(rowSelect - 1, colSelect + 1, colorSelect, grid, numRows, numCols, check);
        }
        if((rowSelect > -1 && rowSelect < numRows) && (colSelect + 1 > -1 && colSelect + 1 < numCols) && (grid[rowSelect][colSelect + 1] == check)) {       //east
            checkHelper(rowSelect, colSelect + 1, colorSelect, grid, numRows, numCols, check);
        }
        if((rowSelect + 1 > -1 && rowSelect + 1 < numRows) && (colSelect + 1 > -1 && colSelect + 1 < numCols) && (grid[rowSelect + 1][colSelect + 1] == check)) {       //southeast
            checkHelper(rowSelect + 1, colSelect + 1, colorSelect, grid, numRows, numCols, check);
        }
        if((rowSelect + 1 > -1 && rowSelect + 1 < numRows) && (colSelect > -1 && colSelect < numCols) && (grid[rowSelect + 1][colSelect] == check)) {       //south
            checkHelper(rowSelect + 1, colSelect, colorSelect, grid, numRows, numCols, check);
        }
        if((rowSelect + 1 > -1 && rowSelect + 1 < numRows) && (colSelect - 1 > -1 && colSelect - 1 < numCols) && (grid[rowSelect + 1][colSelect - 1] == check)) {       //southwest
            checkHelper(rowSelect + 1, colSelect - 1, colorSelect, grid, numRows, numCols, check);
        }
        if((rowSelect > -1 && rowSelect < numRows) && (colSelect - 1 > -1 && colSelect - 1 < numCols) && (grid[rowSelect][colSelect - 1] == check)) {       //west
            checkHelper(rowSelect, colSelect - 1, colorSelect, grid, numRows, numCols, check);
        }
    }
}

void prompt(int *rowSelect, int *colSelect, char *colorSelect, char *grid[], int numRows, int numCols, char fname[], FILE *fptr) {     // Prompts the user for a row, column, and color
    printf("Enter a row:");
    scanf("%d", rowSelect);
    //*rowSelect = 0;
    if (*rowSelect > numRows - 1) {
        printf("That number was too high");
        exit(0);
    }
    if (*rowSelect == -1) {
        for(int i = 0; i < numRows; i++) {
            free(grid[i]);                // deallocate heap space
        }
        free(fname);
        fclose(fptr);
        exit(0);
    }

    printf("Enter a column:");
    scanf("%d", colSelect);
    //*colSelect = 5;
    if (*colSelect > numCols - 1) {
        printf("That number was too high");
        exit(0);
    }
    if (*colSelect == -1) {
        for(int i = 0; i < numRows; i++) {
            free(grid[i]);                // deallocate heap space
        }
        free(fname);
        fclose(fptr);
        exit(0);
    }

    printf("Enter a color:");
    scanf(" %c", colorSelect);
    //*colorSelect = 'r';
    printf("\n");
}

int main(int argc, char *argv[]) {
//    printf("Hello, World!\n");
//    return 0;

    char *fname = (char*) malloc(strlen(argv[1]) + 1);
    strcpy(fname, argv[1]);
//    char fname[] = "C:\\Users\\Dillon\\Desktop\\flood.txt";

    FILE *fptr;
    fptr = fopen(fname, "r");     // open file in read mode

    const int MAX_ROWS = 25;        // Constraint defined in assignment documents

    char *grid[MAX_ROWS];
    int numRows;
    int numCols;
    int rowSelect;
    int colSelect;
    char colorSelect;

    buildGrid(fname, grid, &numRows, &numCols, fptr);

    while(true) {
        showGrid(grid, numRows, numCols);        //print grid to the screen
        prompt(&rowSelect, &colSelect, &colorSelect, grid, numRows, numCols, fname, fptr);     //get selection from user
        checkNeighbors(rowSelect, colSelect, colorSelect, grid, numRows, numCols);       //enter recursion for floodfill
    }

}