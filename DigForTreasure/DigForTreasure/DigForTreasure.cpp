// DigForTreasure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// declare all of the functions.  This could be moved to a separate header file and should be made a class for OO correctness.
void InitMatrix();
void PlaceTreasure();
void PrintPublicMatrix();
void PrintSecretMatrix();
bool GetUserGuess();
bool ProcessGuess(int x, int y);
void addTopOrBottomLine();

#define MATRIX_SIZE 5 // X by X matrix (in this case, 5 x 5)

char matrix[MATRIX_SIZE][MATRIX_SIZE];
int guesses = 10;


/*****************************
 * Main program entry point
 *
 *
 *****************************/
int main()
{
	// initialize the matrix with all ~
	InitMatrix();

	// place the X at some random location
	PlaceTreasure();

	PrintPublicMatrix();

	// keep asking for user input until they win or loose
	while (GetUserGuess())
	{
		PrintPublicMatrix();
	}


	cout << "Press any key to exit";
	_getch();


    return 0;
}

/*****************************
* Set up the matrix and fill
* it with all ~s
*
*****************************/
void InitMatrix()
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] = '~';
		}
	}
}

/*****************************
* Pick a random place in the  
* matrix to hide the treasure
*
*****************************/
void PlaceTreasure()
{

	srand((unsigned)time(NULL));

	double tmp = rand();

	// rand will return a number >= 0 and < RAND_MAX, so we need to convert it so it fits our matrix range.
	unsigned int x = (double)rand() / (RAND_MAX + 1) * (MATRIX_SIZE);
	//	unsigned int x = (double)rand() / (MATRIX_SIZE + 1) * (MATRIX_SIZE);

	unsigned int y = (double)rand() / (RAND_MAX + 1) * (MATRIX_SIZE);

	matrix[x][y] = 'X';

}

/*****************************
* Print the current state of 
* the treasure map with the 
* treasure hidden
*****************************/
void PrintPublicMatrix()
{
	// make sure we are on a new line
	cout << endl << endl;
	cout << "You have " << guesses << " guesses left." << endl;

	addTopOrBottomLine();

	// loop through the matrix to print it out.
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		cout << "|";
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (matrix[i][j] == 'X')
			{
				cout << '~';
			}
			else
			{
				cout << matrix[i][j];
			}
		}
		cout << "|" << endl;
	}
	addTopOrBottomLine();

}

/*****************************
* Print the current state of 
* the treasure map and show
* the location of the treasure
*****************************/
void PrintSecretMatrix()
{
	// make sure we are on a new line
	cout << endl << endl;

	addTopOrBottomLine();
	// loop through the matrix to print it out.
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		cout << "|";
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			cout << matrix[i][j];
		}
		cout << "|" << endl;
	}
	addTopOrBottomLine();

}

/*****************************
* Get the user input and make 
* sure it is two valid numbers
* 
*****************************/
bool GetUserGuess()
{
	cout << endl << endl << "Please enter where you'd like to search in the format X, Y (between 1 and " << MATRIX_SIZE << ")" << endl;
	
	string mystr;
	int x, y;
	bool ret = true;

	// read the entire line from standard input
	getline(cin, mystr);

	// extract X and Y
	if (sscanf_s(mystr.c_str(), "%d, %d", &x, &y) != 2)
	{
		// we didn't get 2 valid numbers
		cout << "Bad input.  Please try again" << endl;
	}
	else
	{
		// we got 2 numbers.  Check to make sure they are between 1 and MATRIX SIZE 
		bool badInput = false;

		// validate the input
		if (x < 1 || x > MATRIX_SIZE)
		{
			cout << "Your X value is out of bounds";
			badInput = true;
		}

		if (y < 1 || y > MATRIX_SIZE)
		{
			cout << "Your Y value is out of bounds";
			badInput = true;
		}

		// check to see if they found the treasure
		if (!badInput)
		{
			ret = ProcessGuess(x, y);
		}
	}
	return ret;
}

/*****************************
* Check to see if they guessed 
* right and update the map
*
*****************************/
bool ProcessGuess(int x, int y)
{
	bool ret = true;

	// the -1 because people are 1 based and C++ is 0 based.
	if (matrix[x-1][y-1] == 'X')
	{
		// they guessed correctly.  End the game and show then the secret map
		cout << "You found the treasure!  Congratulations.  You had " << guesses << " guesses remaining." << endl;
		PrintSecretMatrix();
		ret = false;

	}
	else
	{
		matrix[x-1][y-1] = 'O';
		guesses--;

		if (guesses <= 0)
		{
			cout << "You ran out of guesses.  You lose." << endl << "Here was the hidden treasure" << endl;
			PrintSecretMatrix();
			ret = false;
		}
		else
		{
			cout << "You didn't find it.  Please guess again.  You have " << guesses << " remaining" << endl;
		}

	}
	return ret;


}

void addTopOrBottomLine()
{
	// print size +2 dashes to account for the vertical lines
	for(int i = 0; i < MATRIX_SIZE+2; i++)
	{
		cout << "-";
	}
	cout << endl;

}
