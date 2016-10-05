#include <iostream>
using namespace std;

/*
 * These 4 functions correspond to the 4 algorithm steps.
 * They are executed inside insertX() for every move.
 *
 **************
 * Pseudocode
 **************
 * 1. Check if there's a winnable path
 * 2. Check if I can prevent against a winning opponent path
 * 3. Check if I can set up a winning path for the next move
 * 4. Default to anywhere in an empty path
 * (For 3. & 4., give preference to corners)
 */
bool checkForTwoX(char (&TTTarray)[3][3]);
bool checkForTwoO(char (&TTTarray)[3][3]);
bool checkForOneX(char (&TTTarray)[3][3]);
bool checkForEmpty(char (&TTTarray)[3][3]);


/*
 * General functions for scanning through the Tic-Tac-Toe board.
 * target refers to either 'X' or 'O'
 * num refers to the number of targets we are looking for
 */
bool scanVertical(char (&TTTarray)[3][3], char target, int num);
bool scanHorizontal(char (&TTTarray)[3][3], char target, int num);
bool scanDiagonal(char (&TTTarray)[3][3], char target, int num);


/* For move-making */
void insertX(char (&TTTarray)[3][3]);
void printTTT(char (&TTTarray)[3][3]);

/* Unused */
void insertO(char (&TTTarray)[3][3]);
void checkForWin(char (&TTTarray)[3][3]); 

int main() {

    char TTTarray[3][3] = { {'-','-','-'},
                            {'-','-','-'},
                            {'-','-','-'}};

    // char TTTarray[3][3] = { {'X','O','-'},
    //                         {'-','-','-'},
    //                         {'O','-','-'}};

    // char TTTarray[3][3] = { {'-','O','X'},
    //                         {'-','-','O'},
    //                         {'-','-','-'}};

    // char TTTarray[3][3] = { {'-','-','-'},
    //                         {'-','-','O'},
    //                         {'-','X','O'}};

    //char TTTarray[3][3] = { {'-','-','-'},
    //                        {'-','X','-'},
    //                        {'-','O','-'}};

    //char TTTarray[3][3] = { {'X','-','X'},
    //                        {'-','-','-'},
    //                        {'O','-','-'}};

    // char TTTarray[3][3] = { {'O','O','-'},
    //                        {'-','-','-'},
    //                        {'X','X','-'}};

    // char TTTarray[3][3] = { {'X','-','X'},
    //                        {'O','X','-'},
    //                        {'O','-','O'}};

    // Loop just for testing
    for (int i = 0; i < 9; i++) {
        printTTT(TTTarray);

        insertX(TTTarray);

        printTTT(TTTarray);

        insertO(TTTarray); 
    }
                            
    return 0;   
}

// Return to main as soon as we hit a met criteria
void insertX(char (&TTTarray)[3][3]) {
    if (checkForTwoX(TTTarray)) return;
    if (checkForTwoO(TTTarray)) return;
    if (checkForOneX(TTTarray)) return;
    if (checkForEmpty(TTTarray)) return;
    return;
}

// For checking own winning path
bool checkForTwoX(char (&TTTarray)[3][3]) {
    if (scanVertical(TTTarray, 'X', 2)) return true;
    if (scanHorizontal(TTTarray, 'X', 2)) return true;
    if (scanDiagonal(TTTarray, 'X', 2)) return true;
    return false;
}

// For defending opponent winning path
bool checkForTwoO(char (&TTTarray)[3][3]) {
    if (scanVertical(TTTarray, 'O', 2)) return true;
    if (scanHorizontal(TTTarray, 'O', 2)) return true;
    if (scanDiagonal(TTTarray, 'O', 2)) return true;
    return false;
}

// For adding to path with one X and zero O's
bool checkForOneX(char (&TTTarray)[3][3]) {
    if (scanVertical(TTTarray, 'X', 1)) return true;
    if (scanHorizontal(TTTarray, 'X', 1)) return true;
    if (scanDiagonal(TTTarray, 'X', 1)) return true;
    return false;
}

// For adding to an empty path
bool checkForEmpty(char (&TTTarray)[3][3]) {
    if (scanVertical(TTTarray, 'X', 0)) return true;
    if (scanHorizontal(TTTarray, 'X', 0)) return true;
    if (scanDiagonal(TTTarray, 'X', 0)) return true;
    return false;
}

bool scanVertical(char (&TTTarray)[3][3], char target, int num) {
    int count = 0,  // Counts occurences of the target letter
        countO = 0; // Always counts O's
    
    /*
     * For each column, count the occurences of the target letter.
     * If this count reaches our EXACT target frequency, place the 
     * next letter inside the open space in that path.
     */
    for (int column = 0; column < 3; column++) {
        for (int row = 0; row < 3; row++) {
            if (TTTarray[row][column] == target) {
                count++;
            } else
            if (TTTarray[row][column] == 'O') {
                countO++;
            }
        }
        // If we hit our target frequency...
        if (count == num) { 
            // If we're one-away, just move to the open space.
            if (num == 2) {
                for (int row = 0; row < 3; row++) {
                    if (TTTarray[row][column] == '-'){
                        TTTarray[row][column] = 'X';
                        return true;
                    }
                }
            } else 
           /*
             * The compound condition on 'num == 1' ensures that we 
             * don't waste a move on a path that already has an O
             * blocking it. 
             * Give X preference to corners
             */
            if ((num == 1 && countO == 0) || num == 0) {
                if (TTTarray[0][column] == '-') {
                    TTTarray[0][column] = 'X';
                    return true;
                } else 
                if (TTTarray[2][column] == '-') {
                    TTTarray[2][column] = 'X';
                    return true;
                } else
                if (TTTarray[1][column] == '-') {
                    TTTarray[1][column] = 'X';
                    return true;
                } 
            }
        }
        // Reset the counters on each iteration
        count = 0;
        countO = 0;
    } 
    return false; 
}

bool scanHorizontal(char (&TTTarray)[3][3], char target, int num) {
    int count = 0,  // Counts occurences of the target letter
        countO = 0; // Always counts O's

    /*
     * For each row, count the occurences of the target letter.
     * If this count reaches our EXACT target frequency, place the 
     * next letter inside the open space in that path.
     */
    for (int row = 0; row < 3; row++) {

        for (int column = 0; column < 3; column++) {
            if (TTTarray[row][column] == target) {
                count++;
            } else 
            if (TTTarray[row][column] == 'O') {
                countO++;
            } 
        }
        // If we hit our target frequency...
        if (count == num) {
            // If we're one-away, just move to the open space.
            if (num == 2) {
                for (int column = 0; column < 3; column++) {
                    if (TTTarray[row][column] == '-') {
                        TTTarray[row][column] = 'X';
                        return true;
                    }
                }
            } else 
            /*
             * The compound condition on 'num == 1' ensures that we 
             * don't waste a move on a path that already has an O
             * blocking it. 
             * Give X preference to corners.
             */
            if ((num == 1 && countO == 0) || num == 0) {
                if (TTTarray[row][0] == '-') {
                    TTTarray[row][0] = 'X';
                    return true;
                } else 
                if (TTTarray[row][2] == '-') {
                    TTTarray[row][2] = 'X';
                    return true;
                } else
                if (TTTarray[row][1] == '-') {
                    TTTarray[row][1] = 'X';
                    return true;
                } 
            }
        }
        // Reset the counts for each iteration
        count = 0;
        countO = 0;
    }
    return false;
}

bool scanDiagonal(char (&TTTarray)[3][3], char target, int num) {
    
    int count = 0,
        countO = 0,
        startRow = 0; // The diagonal's row in the 1st column

    // Scan '\' diagonal 
    for (int column = 0; column < 3; column++) {
        if (TTTarray[(startRow+column)][column] == target) {
            count++;
        } else 
        if (TTTarray[(startRow+column)][column] == 'O') {
            countO++;
        } 
        // If target frequency is hit
        if (count == num) {
            /*
             * Weight all target numbers the same since we 
             * already parsed all the corners.
             * For all cases, just move to whatever's open.
             */
            if (num == 2 || (num == 1 && countO == 0) || num == 0) {
                for (int column = 0; column < 3; column++) {
                    if (TTTarray[(startRow+column)][column] == '-') {
                        TTTarray[(startRow+column)][column] = 'X';
                        return true;
                    }
                }
            } 
        } 
    }

    count = 0;
    countO = 0;
    startRow = 2;   // The diagonal's row in the 1st column

    // Scan '/' diagonal 
    for (int column = 0; column < 3; column++) {
        if (TTTarray[(startRow-column)][column] == target) {
            count++;
        } else
        if (TTTarray[(startRow-column)][column] == 'O') {
            countO++;
        } 
        // If target frequency is hit
        if (count == num) {
            /*
             * Weight all target numbers the same since we 
             * already parsed all the corners.
             * For all cases, just move to whatever's open.
             */
            if (num == 2 || (num == 1 && countO == 0) || num == 0) {
                for (int column = 0; column < 3; column++) {
                    if (TTTarray[(startRow-column)][column] == '-') {
                        TTTarray[(startRow-column)][column] = 'X';
                        return true;
                    }
                }
            } 
        } 
    }
    return false;
}

void printTTT(char (&TTTarray)[3][3]) {
    cout << endl;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            cout << TTTarray[row][column];
        }
        cout << endl;
    }
}

// For testing X-placement
void insertO(char (&TTTarray)[3][3]) {
    int move;
    cout << "Enter move: ";
    cin >> move;
    switch(move) {
        case 1: TTTarray[0][0] = 'O';
            break;
        case 2: TTTarray[0][1] = 'O';
            break;
        case 3: TTTarray[0][2] = 'O';
            break;
        case 4: TTTarray[1][0] = 'O';
            break;
        case 5: TTTarray[1][1] = 'O';
            break;
        case 6: TTTarray[1][2] = 'O';
            break;
        case 7: TTTarray[2][0] = 'O';
            break;
        case 8: TTTarray[2][1] = 'O';
            break;
        case 9: TTTarray[2][2] = 'O';
            break;
    }
}



