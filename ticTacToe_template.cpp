/******************************************
*   Template by Aaron Carpenter
*   ELEC 3150 - OOPs
*   EET Dept., WIT
*   Tic-Tac-Toe Lab (#6)
******************************************/

#include <iostream>
using namespace std;

void printTTT(char (&array)[3][3]);
void insertX(char (&array)[3][3]);
void insertO(char (&array)[3][3]);
void checkForWin(/*PASS BY REFERENCE*/); // IGNORE THIS FOR NOW
bool isFirstMoveForO(char (&array)[3][3]);
bool checkForTwo(char (&array)[3][3], char sign);
bool checkRowsAndColumns(char (&array)[3][3], char sign);
bool checkDiagonalLines(char (&array)[3][3], char sign);
void takeFirstAvailable(char (&array)[3][3]);
void nonPotentialMove(char (&array)[3][3]);

int main( ){

    char TTTarray[3][3] = { {'-','-','-'},
                            {'-','-','-'},
                            {'-','-','-'}};

    //char TTTarray[3][3] = { {'-','X','-'},
    //                        {'-','X','-'},
    //                        {'-','-','O'}};

    //char TTTarray[3][3] = { {'-','-','-'},
    //                        {'-','X','-'},
    //                        {'-','O','-'}};

    //char TTTarray[3][3] = { {'X','-','X'},
    //                        {'-','-','-'},
    //                        {'O','-','-'}};

    //char TTTarray[3][3] = { {'X','-','X'},
    //                        {'O','X','-'},
    //                        {'O','-','O'}};


    for(int i =0;i<8;i++)
    {
        insertX(TTTarray);
        //OR
        insertO(TTTarray);

        printTTT(TTTarray);
        cout<<endl;;
        cout<<endl;;
    }

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

void insertX(char (&array)[3][3])
{
	int i,j;
	cout<<"Enter i, then j\n";
	cin>>i>>j;
	array[i][j] = 'X';
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
	
	if(checkRowsAndColumns(array, sign) || checkDiagonalLines(array, sign) )
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//Check if any row or column has 2 of either X or  and then make move accordingly return true if there's.
bool checkRowsAndColumns(char (&array)[3][3], char sign)
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
