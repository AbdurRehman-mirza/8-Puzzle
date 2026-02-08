#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void playGame(char**, int);
void printBoard(char** arr, int n) //Tic-Tac-Toe printBoard
{
	cout << arr[0][0] << " | " << arr[0][1] << " | " << arr[0][2] << endl;
	cout << "---------" << endl;
	cout << arr[1][0] << " | " << arr[1][1] << " | " << arr[1][2] << endl;
	cout << "---------" << endl;
	cout << arr[2][0] << " | " << arr[2][1] << " | " << arr[2][2] << endl;

}
void winCondition()
{
	cout << 1 << " | " << 2 << " | " << 3 << endl;
	cout << "---------" << endl;
	cout << 4 << " | " << 5 << " | " << 6 << endl;
	cout << "---------" << endl;
	cout << 7 << " | " << 8 << " | " << "X" << endl;
}
bool isSolvable(char* tiles, int n) //checking if the puzzle is actually solvable or not. If the inversion count is even then it is solvable otherwise not.
{
	int total = n * n;
	int count = 0;
	for (int i = 0;i < total-1;i++)
	{
		for (int j = i + 1;j < total-1;j++)
		{
			if (tiles[i] > tiles[j])
			{
				count++;
			}
		}
	}
	if (count % 2 == 0)
		return true;
	else
		return false;
}
bool isAgain()
{
	char ch;
	cout << "Do you want to play again (y or n): " << endl;
	again:
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
		return true;
	else if (ch == 'N' || ch == 'n')
		return false;
	else
	{
		cout << "Enter just (y or n): " << endl;
		goto again;
	}
}

bool initgame(char** arr, int n) //Initilize the game from start i.e randomly place the digits in the grid
{
	srand(time(0));
	int k = 0;
	char tiles[8];
	for (int i = 0;i < 8;i++)
	{
		tiles[i] = i + '1';
	}

	int j;
	char temp;
	for (int i = 7;i > 0;i--)
	{
		j = rand() % (i + 1);

		temp = tiles[i];
		tiles[i] = tiles[j];
		tiles[j] = temp;
	}
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (i == 0 && j == 1)
				arr[i][j] = 'X';
			else
				arr[i][j] = tiles[k++];
		}
	}
	return (isSolvable(tiles, n));
}
bool isSolved(char** arr, int n)
{
	bool check = true;
	int k = 0;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (i == 2 && j == 2)
			{
				if (arr[i][j] != 'X')
					break;
			}
			else
			{
				if (arr[i][j] == k + '1')
					k++;
				else {
					check = false;
					break;
				}
			}

		}
	}
	return check;
}

void gameLoop(char** arr, int n)
{

	cout << "========== Let's Start ==========" << endl;
	int move = 0;
	char choice;
	int r1, r2, c1, c2;
	r1 = r2 = c1 = c2 = 0;
	while (true)
	{
		cout << "Enter your choice: " << endl;
		cin >> choice;
		if (choice == 'q')
		{
			cout << "OH! You have quit the game without solving the puzzle completely!!!" << endl;
			break;
		}
		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < n;j++)
			{
				if (arr[i][j] == choice)
				{
					r1 = i;
					c1 = j;
				}
				if (arr[i][j] == 'X')
				{
					r2 = i;
					c2 = j;
				}
			}
			
		}
		if (!((r2 == r1 && (c2 - 1 == c1 || c2 + 1 == c1)) || (r2 + 1 == r1 && c2 == c1) || (r2 - 1 == r1 && c2 == c1) || (r1 + 1 == r2 && c2 == c1) || (r1 - 1 == r2 && c2 == c1)))
		{
			cout << "Invalid swap!" << endl;
			continue;
		}
		
		char temp = arr[r1][c1];
		arr[r1][c1] = arr[r2][c2];
		arr[r2][c2] = temp;
		move++;
		
		printBoard(arr, n);
		cout << "Moves: " << move << endl;
		if (isSolved(arr, n))
		{
			cout << "Congratulations!!! you have solved the puzzle in " << move << " moves." << endl;
			break;
		}
	}
}
void showInstructions()
{
	cout << "================================== WELCOME TO 8-PUZZLE ===================================" << endl;
	cout << "==== INSTRUCTIONS ====" << endl;
	cout << "1. You have to solve the puzzle according to the given winning condition." << endl;
	cout << "2. You can quit anytime during the game (by choice q). " << endl;
	cout << "3. There are some configurations which ain't solvable and so, the game ends immediately, but if you want to play, keep entereing the choices y, when asked." << endl;
	cout << endl;

}
int main()
{
	int n = 3;
	char** arr = new char* [n];
	for (int i = 0;i < n;i++)
	{
		arr[i] = new char[n];

	}
	showInstructions();
	playGame(arr, n);
	
	return 0;
}

void playGame(char** arr, int n)
{
	cout << "========== Winning Condition ========= " << endl;
	winCondition();
	cout << endl << endl;
	bool check = true;
	if (!(initgame(arr, n)))
	{
		cout << "The following Configuration of the puzzle is not solvable!" << endl;
		printBoard(arr, n);
		
	}
	else
	{
		cout << "======== Initial State ========" << endl;
		printBoard(arr, n);
		gameLoop(arr, n);
	}
	if (isAgain()) {
		playGame(arr, n);

	}
	else
	{
		exit(0);
	}
}








