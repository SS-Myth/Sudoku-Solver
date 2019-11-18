#include <stdio.h>
#include <stdbool.h>

bool solve(struct space[9][9], int, int, int);
bool isSafe(struct space[9][9], int, int, int);

struct space
{
	int value;
	bool set;
};

int main()
{
	struct space array[9][9];
	int board[9][9] = { 5, 0, 4, 0, 0, 7, 0, 0, 0,
						0, 0, 0, 0, 0, 3, 0, 0, 6,
						0, 7, 0, 0, 2, 0, 0, 9, 4,
						1, 0, 6, 0, 0, 4, 0, 0, 8,
						0, 0, 5, 0, 0, 0, 1, 0, 0,
						7, 0, 0, 2, 0, 0, 6, 0, 3,
						9, 6, 0, 0, 4, 0, 0, 1, 0,
						8, 0, 0, 6, 0, 0, 0, 0, 0,
						0, 0, 0, 1, 0, 0, 8, 0, 2};

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			array[i][j].value = board[i][j];
			if (board[i][j] > 0)
				array[i][j].set = true;
			else
				array[i][j].set = false;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d", array[i][j].value);
		}
		printf("%s", "\n");
	}

	solve(array, 0, 0, 1);

	printf("\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d", array[i][j].value);
		}
		printf("%s", "\n");
	}

	getchar();
	return 0;
}

bool solve(struct space arr[9][9], int row, int col, int num)
{
	bool complete = false;
	bool safe = false;
	

	if (row < 9 && col < 9)
	{
		while (complete == false)
		{
			//if the current space is not a set number
			if (arr[row][col].set == false)
			{
				safe = false;

				while (safe == false && num <= 9)
				{
					if (isSafe(arr, row, col, num))
						safe = true;
					else
						num++;
				}

				//if a number is safe to place
				if (safe == true)
				{
					arr[row][col].value = num;

					//if on col 0 thru 7 go to next column
					if (col < 8)
						complete = solve(arr, row, col + 1, 1);
					//else go to next row and reset col to 0
					else
						complete = solve(arr, row + 1, 0, 1);
				}
				//else if no safe numbers reset to 0, go to prev space and try new numbers
				else
				{
					arr[row][col].value = 0;
					return false;
				}
			}
			//else if the current space is a set num
			else
			{
				printf("set num %d, %d\n", row, col);
				//if on col 0 thru 7 go to next column
				if (col < 8)
					complete = solve(arr, row, col + 1, 1);
				//else go to next row and reset col to 0
				else
					complete = solve(arr, row + 1, 0, 1);
				return complete;
			}
		}
	}
	return true;
}

/*int solve(int arr[9][9], int row, int col, int num)
{
	bool safe = false;
	printf("%s", "solving...\n");

	//call recursively until board is complete
	if (row < 9 && col < 9)
	{
		printf("%s", "not complete...\n");

		//if the space is not an already set number
		if (arr[row][col] == 0)
		{
			printf("%s", "empty space\n");

			//check for a safe number at arr[row][col]
			while (safe == false && num <= 9)
			{
				printf("is safe?\n");
				if (isSafe(arr, row, col, num))
					safe = true;
				else
					num++;
			}

			//if a number is safe to place
			if (safe == true)
			{
				printf("%d is safe", num);
				arr[row][col] = num;

				//if on col 0 thru 7 go to next column
				if (col < 8)
					solve(arr, row, col + 1, 1);
				//else go to next row and reset col to 0
				else
					solve(arr, row + 1, 0, 1);
			}

			//else if no safe numbers go to previous space and try new numbers
			else
			{
				//if the previous space was not an already occupied with set number, try new numbers in that space
				if (prevOcc == false)
				{
					arr[row][col] = 0;
					//if on col 1 thru 8 go to prev column
					if (col > 0)
					{
						num = arr[row][col - 1];
						solve(arr, row, col - 1, num + 1);
					}
					//else go to prev row and reset col to 8
					else
					{
						num = arr[row - 1][8];
						solve(arr, row - 1, 8, num + 1);
					}
				}
			}
		}

		//else if space is occupied by a set num go to next space
		else
		{
			printf("%s", "occupied space\n");
			//if on col 0 thru 7 go to next column
			if (col < 8)
				solve(arr, row, col + 1, 1, true);
			//else go to next row and reset col to 0
			else
				solve(arr, row + 1, 0, 1, true);
		}
	}

	//once board is complete return 0
	return 0;
}*/

bool isSafe(struct space arr[9][9], int row, int col, int num)
{
	bool check = true;

	//check for num in that row
	for (int i = 0; i < 9; i++)
	{
		if (arr[row][i].value == num)
		{
			check = false;
		}
	}

	//check for num in that column
	for (int i = 0; i < 9; i++)
	{
		if (arr[i][col].value == num)
		{
			check = false;
		}
	}

	//if in grid 1
	if ((0 <= row && row <= 2) && (0 <= col && col <= 2))
	{
		//check for num in grid
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 2
	if ((0 <= row && row <= 2) && (3 <= col && col <= 5))
	{
		//check for num in grid
		for (int i = 0; i < 3; i++)
		{
			for (int j = 3; j < 6; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 3
	if ((0 <= row && row <= 2) && (6 <= col && col <= 8))
	{
		//check for num in grid
		for (int i = 0; i < 3; i++)
		{
			for (int j = 6; j < 9; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 4
	if ((3 <= row && row <= 5) && (0 <= col && col <= 2))
	{
		//check for num in grid
		for (int i = 3; i < 6; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 5
	if ((3 <= row && row <= 5) && (3 <= col && col <= 5))
	{
		//check for num in grid
		for (int i = 3; i < 6; i++)
		{
			for (int j = 3; j < 6; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 6
	if ((3 <= row && row <= 5) && (6 <= col && col <= 8))
	{
		//check for num in grid
		for (int i = 3; i < 6; i++)
		{
			for (int j = 6; j < 9; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 7
	if ((6 <= row && row <= 8) && (0 <= col && col <= 2))
	{
		//check for num in grid
		for (int i = 6; i < 9; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 8
	if ((6 <= row && row <= 8) && (3 <= col && col <= 5))
	{
		//check for num in grid
		for (int i = 6; i < 9; i++)
		{
			for (int j = 3; j < 6; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	//if in grid 9
	if ((6 <= row && row <= 8) && (6 <= col && col <= 8))
	{
		//check for num in grid
		for (int i = 6; i < 9; i++)
		{
			for (int j = 6; j < 9; j++)
			{
				if (arr[i][j].value == num)
					check = false;
			}
		}
	}

	return check;
}