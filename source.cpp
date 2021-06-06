#include<iostream>
#include<conio.h>
#include<fstream>
#include<time.h>
#include "help.h"
using namespace std;
void myTriangle(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	int mid = (x1 + x2) / 2;
	MoveToEx(device_context, mid, y1, NULL);
	LineTo(device_context, x2, y2);
	LineTo(device_context, x1, y2);
	LineTo(device_context, mid + 1, y1);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB));  //Fill color is black
	SelectObject(device_context, brush);
	FloodFill(device_context, mid, (y1 + y2) / 2, RGB(R, G, B));
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);

}
bool checkvalid(int srow1, int scol1, int srow2, int scol2)  //Check whether the swapping is for valid positions.
{
	if ((srow1 == srow2 && (scol2 == scol1 + 1 || scol2 == scol1 - 1)) || (scol1 == scol2 && (srow2 == srow1 + 1 || srow2 == srow1 - 1)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void GemCombo(int arr[][8])     //If similar gems come together , they are replaced by random numbers,
{                               //both horizontally and vertically.
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (arr[row][col] == arr[row + 1][col] && arr[row][col] == arr[row + 2][col] && row < 6)
			{
				arr[row][col] = (rand() % 5) + 1;
				arr[row + 1][col] = (rand() % 5) + 1;
				arr[row + 2][col] = (rand() % 5) + 1;
			}
			if (arr[row][col] == arr[row - 1][col] && arr[row][col] == arr[row - 2][col] && row > 1)
			{
				arr[row][col] = (rand() % 5) + 1;
				arr[row - 1][col] = (rand() % 5) + 1;
				arr[row - 2][col] = (rand() % 5) + 1;
			}

			if (arr[row][col] == arr[row][col + 1] && arr[row][col] == arr[row][col + 2] && col < 6)
			{
				arr[row][col] = (rand() % 5) + 1;
				arr[row][col + 1] = (rand() % 5) + 1;
				arr[row][col + 2] = (rand() % 5) + 1;
			}
			if (arr[row][col] == arr[row][col + 1] && arr[row][col] == arr[row][col - 1] && col > 0 && col < 7)
			{
				arr[row][col] = (rand() % 5) + 1;
				arr[row][col + 1] = (rand() % 5) + 1;
				arr[row][col - 1] = (rand() % 5) + 1;
			}

			if (arr[row][col] == arr[row][col - 1] && arr[row][col] == arr[row][col - 2] && col > 1)
			{
				arr[row][col] = (rand() % 5) + 1;
				arr[row][col - 1] = (rand() % 5) + 1;
				arr[row][col - 2] = (rand() % 5) + 1;
			}
		}
	}
}

void myCircle2(int x1, int y1)       //Contracted function of the circle shape.
{
	myEllipse(x1, y1, x1 + 40, y1 + 40, 255, 255, 0, 255, 255, 0);
}
void myTriangle2(int x1, int y1)      //Contracted function of the triangle shape.
{
	myTriangle(x1, y1, x1 + 40, y1 + 40, 0, 255, 0, 0, 255, 0);
}
void mySquare1(int x1, int y1)      //Contracted function of square shape.
{
	myRect(x1, y1, x1 + 30, y1 + 30, 255, 0, 0, 255, 0, 0);
}
void myDiamond1(int x1, int y1)    //Function to make diamond by using consecutive slanted lines.
{
	myLine(x1 + 1, y1, x1 + 17, y1 + 20, 255);
	myLine(x1 + 17, y1 + 20, x1, y1 + 40, 255);
	myLine(x1 - 17, y1 + 20, x1, y1 + 40, 255);
	myLine(x1 + 1, y1, x1 - 17, y1 + 20, 255);
}
void myHexa(int x1, int y1)     //Function to make hexagon by using consecutive lines.
{
	myLine(x1 + 1, y1, x1 + 16, y1 + 15, 255);
	myLine(x1 + 16, y1 + 15, x1 + 16, y1 + 30, 255);
	myLine(x1 + 16, y1 + 30, x1 + 1, y1 + 45, 255);
	myLine(x1 + 1, y1 + 45, x1 - 14, y1 + 30, 255);
	myLine(x1 - 14, y1 + 30, x1 - 14, y1 + 15, 255);
	myLine(x1 - 14, y1 + 15, x1 + 1, y1, 255);
}
bool ProperSwap(int arr[][8], int srow1, int scol1, int srow2, int scol2) //A function that makes sure that invalid swapping is prevented and only valid swap is performed.

{   //returns true if swapping is valid , else returns false.
	int flag = 0;
	if (srow1 == srow2)
	{
		if (scol1>scol2)
		{
			if (arr[srow2][scol2] == arr[srow2][scol2 + 2] && arr[srow2][scol2] == arr[srow2][scol2 + 3])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1][scol1 - 2] && arr[srow1][scol1] == arr[srow1][scol1 - 3])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 - 1][scol2 + 1] && arr[srow2][scol2] == arr[srow2 - 2][scol2 + 1])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 + 1][scol2 + 1] && arr[srow2][scol2] == arr[srow2 + 2][scol2 + 1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 1][scol1 - 1] && arr[srow1][scol1] == arr[srow1 - 2][scol1 - 1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 + 1][scol1 - 1] && arr[srow1][scol1] == arr[srow1 + 2][scol1 - 1])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 - 1][scol2 + 1] && arr[srow2][scol2] == arr[srow2 + 1][scol2 + 1])
				flag = true;
			else if (arr[srow1][scol2] == arr[srow1 - 1][scol1 - 1] && arr[srow1][scol1] == arr[srow1 + 1][scol1 - 1])
				flag = true;
			else
				flag = false;
		}
		if (scol2>scol1)
		{

			if (arr[srow2][scol2] == arr[srow2][scol2 - 2] && arr[srow2][scol2] == arr[srow2][scol2 - 3])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1][scol1 + 2] && arr[srow1][scol1] == arr[srow1][scol1 + 3])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 1][scol1 + 1] && arr[srow1][scol1] == arr[srow1 - 2][scol1 + 1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 + 1][scol1 + 1] && arr[srow1][scol1] == arr[srow1 + 2][scol1 + 1])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 - 1][scol2 - 1] && arr[srow2][scol2] == arr[srow2 - 2][scol2 - 1])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 + 1][scol2 - 1] && arr[srow2][scol2] == arr[srow2 + 2][scol2 - 1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 1][scol1 + 1] && arr[srow1][scol1] == arr[srow1 + 1][scol1 + 1])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 - 1][scol2 - 1] && arr[srow2][scol2] == arr[srow2 + 1][scol2 - 1])
				flag = true;
			else if (arr[srow1][scol2] == arr[srow1][scol2 - 2] && arr[srow1][scol2] == arr[srow1][scol2 - 3])
				flag = true;
			else if (arr[srow1][scol2] == arr[srow1 - 1][scol2 - 1] && arr[srow1][scol2] == arr[srow1 + 1][scol2 + 1])
				flag = true;
			else
				flag = false;
		}

	}
	if (scol1 == scol2)
	{
		if (srow1<srow2)
		{
			if (arr[srow2][scol2] == arr[srow2 - 2][scol2] && arr[srow2][scol2] == arr[srow2 - 3][scol2])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 + 2][scol1] && arr[srow1][scol1] == arr[srow1 + 3][scol1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 + 1][scol1 + 1] && arr[srow1][scol1] == arr[srow1 + 1][scol1 + 2])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 + 1][scol1 - 1] && arr[srow1][scol1] == arr[srow1 + 1][scol1 - 2])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 + 1][scol1 - 1] && arr[srow1][scol1] == arr[srow1 + 1][scol1 + 1])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 - 1][scol2 - 1] && arr[srow1][scol1] == arr[srow2 - 1][scol2 + 1])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 - 1][scol2 + 1] && arr[srow2][scol2] == arr[srow2 - 1][scol2 + 2])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 - 1][scol2 - 1] && arr[srow2][scol2] == arr[srow2 - 1][scol2 - 2])
				flag = true;
			else
				flag = false;
		}
		if (srow1>srow2)
		{
			if (arr[srow2][scol2] == arr[srow2 + 2][scol2] && arr[srow2][scol2] == arr[srow2 + 3][scol2])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 + 1][scol2 + 1] && arr[srow2][scol2] == arr[srow2 + 1][scol2 + 2])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 + 1][scol2 - 1] && arr[srow2][scol2] == arr[srow2 + 1][scol2 - 2])
				flag = true;
			else if (arr[srow2][scol2] == arr[srow2 + 1][scol2 + 1] && arr[srow2][scol2] == arr[srow2 + 1][scol2 - 1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 2][scol1] && arr[srow1][scol1] == arr[srow1 - 3][scol1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 1][scol1 + 1] && arr[srow1][scol1] == arr[srow1 - 1][scol1 - 1])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 1][scol1 + 1] && arr[srow1][scol1] == arr[srow1 - 1][scol1 + 2])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 1][scol1 - 1] && arr[srow1][scol1] == arr[srow1 - 1][scol1 - 2])
				flag = true;
			else if (arr[srow1][scol1] == arr[srow1 - 1][scol1 - 1] && arr[srow1][scol1] == arr[srow1 - 1][scol1 + 1])
				flag = true;
			else
				flag = false;

		}
	}
	return flag;
}
void printboard(int arr[][8], int R)  //Prints random shapes on random numbers.
{
	srand(time(0));
	int num;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<8; j++)
		{
			arr[i][j] = rand() % 5 + 1;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arr[i][j] == 1)
			{
				myCircle2((i * 60) + 8, (j * 60) + 8);
			}
			if (arr[i][j] == 2)
			{
				mySquare1((i * 60) + 15, (j * 60) + 15);
			}
			if (arr[i][j] == 3)
			{
				myDiamond1((i * 60) + 29, (j * 60) + 10);
			}
			if (arr[i][j] == 4)
			{
				myHexa((i * 60) + 27, (j * 60) + 8);
			}
			if (arr[i][j] == 5)
			{
				myTriangle2((i * 60) + 10, (j * 60) + 8);
			}
		}
		cout << endl;
	}
}
void newboard(int arr[][8], int R)  //Prints the board without using rand for further use.
{
	int i = 0;
	while (i < 480)
	{
		myLine(i + 60, 0, i + 60, 480, 255);
		myLine(0, i + 60, 480, i + 60, 255);
		i = i + 60;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arr[i][j] == 1)
			{
				myCircle2((i * 60) + 8, (j * 60) + 8);
			}
			if (arr[i][j] == 2)
			{
				mySquare1((i * 60) + 15, (j * 60) + 15);
			}
			if (arr[i][j] == 3)
			{
				myDiamond1((i * 60) + 29, (j * 60) + 10);
			}
			if (arr[i][j] == 4)
			{
				myHexa((i * 60) + 27, (j * 60) + 8);
			}
			if (arr[i][j] == 5)
			{
				myTriangle2((i * 60) + 10, (j * 60) + 8);
			}
		}
		cout << endl;
	}
}
int main()
{
	time_t end = time(NULL) + 60;
	int score = 0;
	int arr[8][8];
	int i = 0;
	while (i < 480)     //Lines 
	{
		myLine(i + 60, 0, i + 60, 480, 255);
		myLine(0, i + 60, 480, i + 60, 255);
		i = i + 60;
	}
	printboard(arr, 8);
	GemCombo(arr);
	GemCombo(arr);
	system("cls");
	newboard(arr, 8);
	newboard(arr, 8);
	myLine(5, 5, 5, 10, 255);
	int x = 0, y = 0;
	int srow1 = 0;
	int scol1 = 0;
	int srow2 = 0;
	int scol2 = 0;
	bool cv = 0;
	bool vm = 0;
	int f = 0;
	gotoxy(0, 0);
	for (int i = 0; i < 10;i++)
	{
		scol1 = 0, srow1 = 0, srow2 = 0, scol2 = 0;
		f = 0;
		cv = false;
		{
			for (int i = 0, x = 0, y = 0; i < 1000 && f == 0; i++)
			{
				char c = _getch();
				if (c == -32)
				{
					c = _getch();
					if (c == 'H')
					{
						if (y > 60)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							y = y - 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							scol1--;
						}
					}
					if (c == 'K')
					{

						if (x > 60)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							x = x - 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							srow1--;
						}
					}
					if (c == 'M')
					{
						if (x < 480)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							x = x + 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							srow1++;
						}
					}
					if (c == 'P')
					{
						if (y < 480)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							y = y + 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							scol1++;
						}
					}
				}
				else if (c == 's')
				{
					ofstream fout("save.txt");
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							fout << arr[i][j] << " ";
						}
					}
					fout.close();
				}
				else if (c == 'l')
				{
					ifstream fin("save.txt");
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							fin >> arr[i][j];
						}
					}
					gotoxy(0, 0);
					system("cls");
					newboard(arr, 8);
					newboard(arr, 8);
				}
				if (c == 13)
				{
					f = 1;
				}
			}
			f = 0;
			for (int i = 0, f = 0, x = 0, y = 0; i < 1000 && f == 0; i++)
			{
				char c = _getch();
				if (c == -32)
				{
					c = _getch();
					if (c == 'H')
					{
						if (y > 60)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							y = y - 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							scol2--;
						}
					}
					if (c == 'K')
					{
						if (x > 60)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							x = x - 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							srow2--;
						}
					}
					if (c == 'M')
					{
						if (x < 480)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							x = x + 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							srow2++;
						}
					}
					if (c == 'P')
					{
						if (y < 480)
						{
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 0);
							y = y + 61;
							myLine(5 + x, 5 + y, 10 + x, 10 + y, 255);
							scol2++;
						}
					}
				}
				else if (c == 's')    //Saves the game.
				{
					ofstream fout("save.txt");
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							fout << arr[i][j] << " ";
						}
					}
					fout.close();
				}
				else if (c == 'l')   //Loads the game.
				{
					ifstream fin("save.txt");
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							fin >> arr[i][j];
						}
					}
					gotoxy(0, 0);
					system("cls");
					newboard(arr, 8);
					newboard(arr, 8);
				}
				if (c == 13)
				{
					f = 1;
				}
			}
			cv = checkvalid(srow1, scol1, srow2, scol2);
			vm = ProperSwap(arr, srow1, scol1, srow2, scol2);
		}
		newboard(arr, 8);
		if (cv == true && vm == true)
		{
			score = score + (rand() % 10) + 1;
			swap(arr[srow1][scol1], arr[srow2][scol2]);
			GemCombo(arr);
			system("cls");
			newboard(arr, 8);
			newboard(arr, 8);
			newboard(arr, 8);
			GemCombo(arr);
			Sleep(250);
			system("cls");
			newboard(arr, 8);
			newboard(arr, 8);
			newboard(arr, 8);
		}
		else if (cv == true)
		{
			swap(arr[srow1][scol1], arr[srow2][scol2]);
			system("cls");
			gotoxy(0, 0);
			newboard(arr, 8);
			newboard(arr, 8);
			newboard(arr, 8);
			Sleep(250);
			swap(arr[srow1][scol1], arr[srow2][scol2]);
			system("cls");
			newboard(arr, 8);
			newboard(arr, 8);
			newboard(arr, 8);
		}
		else
		{
			gotoxy(0, 0);
			system("cls");
			newboard(arr, 8);
			newboard(arr, 8);
		}
	}
	system("cls");
	cout << "Your score is:" << endl << score;
	_getch();
}
