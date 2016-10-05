/******************************************
*   Template by Aaron Carpenter
*   ELEC 3150 - OOPs
*   EET Dept., WIT
*   Tic-Tac-Toe Lab (#6)
******************************************/

#include <iostream>
using namespace std;

void printTTT(char (&array)[3][3]);
void insertO(char (&array)[3][3]);
bool checkForWin(char (&array)[3][3]);
bool isFirstMoveForO(char (&array)[3][3]);
bool checkForTwo(char (&array)[3][3], char sign);
bool checkRowsAndColumns(char (&array)[3][3], char sign);
bool checkDiagonalLines(char (&array)[3][3], char sign);
void takeFirstAvailable(char (&array)[3][3]);
void nonPotentialMove(char (&array)[3][3]);
bool checkRows(char (&array)[3][3], char sign);
bool checkColumns(char (&array)[3][3], char sign);
bool checkDiagonalLines(char (&array)[3][3], char sign);


/* For X move-making */
void insertX(char (&TTTarray)[3][3]);

/* 1. Check if there's a winnable path
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

int main( ){

    char TTTarray[3][3] = { {'-','-','-'},
                            {'-','-','-'},
                            {'-','-','-'}};

    for(int i =0;i<8;i++)
    {
        insertX(TTTarray);
        //OR
        insertO(TTTarray);

        printTTT(TTTarray);
        cout<<endl;;
        cout<<endl;;
		if(checkForWin(TTTarray))
		{
			return 0;
		}
    }
	cout<<"Tie \n";

    /*****************
    I have included the declaratoin of the array, initialized to - for each spot.
    The '-' represents an empty position.  You should fill it with either a 
    capital 'O' or a capital 'X'. I have also included a number of initialized arrays 
    to test; just comment out the ones you don't want for that moment
    *****************/
    return 0;   
}

void printTTT(char (&array)[3][3])
{
    for(int i =0;i < 3; i++)
	{
		for(int j =0;j < 3; j++)
		{
			cout<<array[i][j];
		}
		cout<<endl;
	}
}

//Insert an O character to the board according to the algorithm
void insertO(char (&array)[3][3])
{
	
	if(isFirstMoveForO(array))
	{
		//Early block 
		if(array[0][1] == 'X' || array[1][0] == 'X')
		{
			array[0][0] = 'O';
		}
		else if(array[2][1] == 'X' || array[1][2] == 'X')
		{
			array[0][2] = 'O';
		}
		//Take the center spot if it's still there
		else if(array[1][1] == '-')
		{
			array[1][1] = 'O';
		}
		else
		{
			nonPotentialMove(array);
		}
	}
	else
	{
		//After first move tatics
		if(checkForTwo(array, 'O'))
		{
			return;
		}
		else if(checkForTwo(array, 'X'))
		{
			return;
		}
		else
		{
			nonPotentialMove(array);
		}
	}
	return;
}

//Check to see this is O first move by counting the number of X on the board
bool isFirstMoveForO(char (&array)[3][3])
{
	int count = 0;
	for(int i =0;i < 3; i++)
	{
		for(int j =0;j < 3; j++)
		{
			if(array[i][j] == 'X')
			{
				count++;
			}
			if(count > 1)
			{
				return false;
			}
		}
	}
	return true;
}

//Moves for cases when there're no potential winning or losing
void nonPotentialMove(char (&array)[3][3])
{
	if(array[2][2] == '-')
	{
		array[2][2] = 'O';	
	}
	//Take one the two adjacent point to the lower right point if possible
	else if(array[2][1] == '-' && array[2][2] == 'O')
	{
		array[2][1] = 'O';
	}
	else if(array[1][2] == '-' && array[2][2] == 'O')
	{
		array[1][2] = 'O';
	}
	else
	{
		takeFirstAvailable(array);
	}
}

//Check if there's any potential winning/losing slot and take/block it. To check for potential win pass in sign = 'O'. Potential loss sign = 'X' return true if found.
//Basically check if any row,column or diagonal line has 2 of either X or O depending on the second parameter. And then make move accordingly
bool checkForTwo(char (&array)[3][3], char sign)
{
	
	if(checkRows(array, sign) || checkColumns(array, sign) || checkDiagonalLines(array, sign) )
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//Check if any row has 2 of either X or  and then make move accordingly return true if there's.
bool checkRows(char (&array)[3][3], char sign)
{
	//Check for rows 
	for(int i=0; i < 3;i++)
	{
		int count = 0;
		bool empty = false;
		int position;
		for(int j =0;j < 3; j++)
		{
			if(array[i][j] == sign)
			{
				count++;
			}
			else if(array[i][j] == '-')
			{
				empty = true;
				position = j;
			}
		}
		//Take it
		if(count >1 && empty)
		{
			array[i][position] = 'O';
			return true;
		}
	}
	return false;
}

//Check if any column has 2 of either X or  and then make move accordingly return true if there's.
bool checkColumns(char (&array)[3][3], char sign)
{
	//Check for columns
	for(int j=0; j < 3;j++)
	{
		int count = 0;
		bool empty = false;
		int position;
		for(int i =0;i < 3; i++)
		{
			if(array[i][j] == sign)
			{
				count++;
			}
			else if(array[i][j] == '-')
			{
				empty = true;
				position = i;
			}
		}
		//Take it
		if(count >1 && empty)
		{
			array[position][j] = 'O';
			return true;
		}
	}
	return false;
}

//Check if any diagonal lines has 2 of either X or  and then make move accordingly return true if there's. 
bool checkDiagonalLines(char (&array)[3][3], char sign)
{
	//Check the two diagonal lines
	int count1 = 0;//how many X or O found for the first diagonal line
	int count2 = 0;//how many X or O found for the second diagonal line
	bool empty1 = false;//if the spot is empty
	bool empty2 = false;//if the spot id empty
	int position1[2], position2[2] ;
	//We need to check [0][0], [1][1], [2][2] AND [0][2], [1][1], [2][0]
	for(int i =0; i < 3; i++)
	{
		//Check [0][0], [1][1], [2][2]
		if(array[i][i] == sign)
		{
			count1++;
		}
		else if(array[i][i] == '-')
		{
			empty1 = true;
			position1[0] = i;
			position1[1] = i;
		}
		
		//Check [0][2], [1][1], [2][0]
		if(array[0+i][2-i] == sign)
		{
			count2++;
		}
		else if(array[0+i][2-i] == '-')
		{
			empty2 = true;
			position2[0] = 0+i;
			position2[1] = 2-i;
		}
	}
	//Take it
	if(count1 >1 && empty1)
	{
		array[position1[0]][position1[1]] = 'O';
		return true;
	}
	else if(count2 >1 && empty2)
	{
		array[position2[0]][position2[1]] = 'O';
		return true;
	}
	return false;
}

//Just make a move on the first available spot, this probably not gonna be use, it's more like a backup plan in case there's a hole in the algorithm
void takeFirstAvailable(char (&array)[3][3])
{
	for(int i =0;i < 3; i++)
	{
		for(int j =0;j < 3; j++)
		{
			if(array[i][j] == '-')
			{
				array[i][j] = 'O';
			}
		}
	}
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

bool scanVertical(char (&TTTarray)[3][3], char target, int num) 
{
    int count = 0,  // Counts occurences of the target letter
        countO = 0; // Always counts O's
    
    /*
     * For each column, count the occurences of the target letter.
     * If this count reaches our EXACT target frequency, place the 
     * next letter inside the open space in that path.
     */
    for (int column = 0; column < 3; column++) 
    {
        for (int row = 0; row < 3; row++) 
        {
            if (TTTarray[row][column] == target) 
            {
                count++;
            } else if (TTTarray[row][column] == 'O') 
            {
                countO++;
            }
        }
        // If we hit our target frequency...
        if (count == num) 
        { 
            // If we're one-away, just move to the open space.
            if (num == 2) 
            {
                for (int row = 0; row < 3; row++) 
                {
                    if (TTTarray[row][column] == '-')
                    {
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
            if ((num == 1 && countO == 0) || num == 0) 
            {
                if (TTTarray[0][column] == '-') 
                {
                    TTTarray[0][column] = 'X';
                    return true;
                } else if (TTTarray[2][column] == '-') 
                {
                    TTTarray[2][column] = 'X';
                    return true;
                } else if (TTTarray[1][column] == '-') 
                {
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

bool scanHorizontal(char (&TTTarray)[3][3], char target, int num) 
{
    int count = 0,  // Counts occurences of the target letter
        countO = 0; // Always counts O's

    /*
     * For each row, count the occurences of the target letter.
     * If this count reaches our EXACT target frequency, place the 
     * next letter inside the open space in that path.
     */
    for (int row = 0; row < 3; row++) 
    {
        for (int column = 0; column < 3; column++) 
        {
            if (TTTarray[row][column] == target) 
            {
                count++;
            } else if (TTTarray[row][column] == 'O') 
            {
                countO++;
            } 
        }
        // If we hit our target frequency...
        if (count == num) 
        {
            // If we're one-away, just move to the open space.
            if (num == 2) 
            {
                for (int column = 0; column < 3; column++) 
                {
                    if (TTTarray[row][column] == '-') 
                    {
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
            if ((num == 1 && countO == 0) || num == 0) 
            {
                if (TTTarray[row][0] == '-') 
                {
                    TTTarray[row][0] = 'X';
                    return true;
                } else if (TTTarray[row][2] == '-') 
                {
                    TTTarray[row][2] = 'X';
                    return true;
                } else if (TTTarray[row][1] == '-') 
                {
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

bool scanDiagonal(char (&TTTarray)[3][3], char target, int num) 
{
    
    int count = 0,
        countO = 0,
        startRow = 0; // The diagonal's row in the 1st column

    // Scan '\' diagonal 
    for (int column = 0; column < 3; column++) 
    {
        if (TTTarray[(startRow+column)][column] == target) 
        {
            count++;
        } else if (TTTarray[(startRow+column)][column] == 'O') 
        {
            countO++;
        } 
        // If target frequency is hit
        if (count == num) 
        {
            /*
             * Weight all target numbers the same since we 
             * already parsed all the corners.
             * For all cases, just move to whatever's open.
             */
            if (num == 2 || (num == 1 && countO == 0) || num == 0) 
            {
                for (int column = 0; column < 3; column++) 
                {
                    if (TTTarray[(startRow+column)][column] == '-') 
                    {
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
    for (int column = 0; column < 3; column++) 
    {
        if (TTTarray[(startRow-column)][column] == target) 
        {
            count++;
        } else if (TTTarray[(startRow-column)][column] == 'O') 
        {
            countO++;
        } 
        // If target frequency is hit
        if (count == num) 
        {
            /*
             * Weight all target numbers the same since we 
             * already parsed all the corners.
             * For all cases, just move to whatever's open.
             */
            if (num == 2 || (num == 1 && countO == 0) || num == 0) 
            {
                for (int column = 0; column < 3; column++) 
                {
                    if (TTTarray[(startRow-column)][column] == '-') 
                    {
                        TTTarray[(startRow-column)][column] = 'X';
                        return true;
                    }
                }
            } 
        } 
    }
    return false;
}

bool checkForWin(char (&array)[3][3])
{
	int countX, countO;
	for(int i =0;i<3;i++)
	{
		//Row
		if( (*(&array[0][0]+i)) == 'X')
		{
			countX++;
		}
		if(countX ==3)
		{
			cout<<"X won \n";
			return true;
		}
		
		if( (*(&array[0][0]+i)) == 'O')
		{
			countO++;
		}
		if(countO ==3)
		{
			cout<<"O won \n";
			return true;
		}
		
		//Column
		if( (*(&array[0][0]+3+i)) == 'X')
		{
			countX++;
		}
		if(countX ==3)
		{
			cout<<"X won \n";
			return true;
		}
		
		if( (*(&array[0][0]+3+i)) == 'O')
		{
			countO++;
		}
		if(countO ==3)
		{
			cout<<"O won \n";
			return true;
		}
	}	
	//Diagonal lines
	int count1X, count2X, count1O, count2O;
	//We need to check [0][0], [1][1], [2][2] AND [0][2], [1][1], [2][0]
	for(int i =0; i < 3; i++)
	{
		//Check [0][0], [1][1], [2][2]
		if(array[i][i] == 'X')
		{
			count1X++;
		}
		
		//Check [0][2], [1][1], [2][0]
		if(array[0+i][2-i] == 'X')
		{
			count2X++;
		}
		
		//Check [0][0], [1][1], [2][2]
		if(array[i][i] == 'O')
		{
			count1X++;
		}
		
		//Check [0][2], [1][1], [2][0]
		if(array[0+i][2-i] == 'O')
		{
			count2X++;
		}
		
	}
	if(count1X ==3 || count2X == 3)
	{
		cout<<"X won \n";
		return true;
	}
	
	if(count1O ==3 || count2O == 3)
	{
		cout<<"O won \n";
		return true;
	}
	return false;
	
}