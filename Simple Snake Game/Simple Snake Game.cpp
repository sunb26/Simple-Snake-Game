
#include <iostream>
#include <string.h>
#include <conio.h> //Library for controlling console with keyboard
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20; // These two const terms are determining the dimensions of the game board
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //Array for tail
int nTail; //Specifies length of tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //Sets the direction variables
eDirection dir;




void Setup()
{
	gameOver = false;
	dir = STOP; //Snake starts frozen
	x = width / 2; // x, y = snake head positon. By dividing by 2, the snake head starts at center of board
	y = height / 2;
	fruitX = rand() % width; //Create a rand. number from 0 to (width -1)
	fruitY = rand() % height;
	score = 0;

}


void Draw()
{
	system("cls"); //system is used because we are creating the game in the console. By using the command "cls", it clears the screen/console window
	for (int i = 0; i < width + 2; i++) //These for-loop is to print out the top wall
	{
		cout << '#';
	}

	cout << '\n';

	for (int i = 0; i < height; i++) // This forloop is used to draw the rest of the map. SImilar to d
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) //This is the left border
				cout << '#';

			if (i == y && j == x) // THis prints out the head of the snake
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) //This prints out the fruit
			{
				cout << "F";
			}
			else //This prints out the blank spaces in the middle of the board
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{


					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";


			}
			if (j == width - 1) // This is the right border
			{
				cout << '#';
			}
		}
		cout << "\n";
	}



	for (int i = 0; i < width + 2; i++)//These for-loop is to print out the bottom wall
	{
		cout << '#';
	}

	cout << "\n";
	cout << "Score: " << score;
}


void Input()
{
	if (_kbhit()) // This function returns boolean value depending on if a button on the keyboard is pressed (returns 0 if nothing pressed)
	{
		switch (_getch()) // This fetches the ASCII value of the key that was pressed. Based on the key, we are making the controls
		{
		case 'a':
			dir = LEFT;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'w':
			dir = UP;
			break;

		case 'x':
			gameOver = true;
			break;
		}



	}
}


void Logic()
{
	//These variables are for printing of the snake tail
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x; //Setting the beginning of the tail to follow the head
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	/*if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}*/

	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score = score + 10;
		fruitX = rand() % width; //Create a rand. number from 0 to (width -1)
		fruitY = rand() % height;
		nTail++;

	}


}

int main() {

	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(20);
		//Sleep(10); sleep(10); The sleep function slows down the game. Optional implementation 
	}
	return 0;
}