#include<bits/stdc++.h>
using namespace std;

bool can_put(int mat[][9],int i,int j,int n,int num)
{
	//Checks the row , coloumn, subgrid
	//x simply a counter
	for(int x=0;x<n;x++)
	{
		if(mat[x][j]==num or mat[i][x]==num)    //If the number is coming in row or in coloumn
		{
			return false;
		}
	}

	//Now check for the numbers not repeating in the subgrid
	int root_n = sqrt(n); // To find the dimension of the subgrid, here sqrt(9)=3;
	int cx= (i/root_n)*root_n;  // Starting Coordinate of x-axis of any subgrid to check if a subgrid contains duplicate or all the numbers or not
	int cy= (j/root_n)*root_n;  //Starting Coordinate of y-axis of any subgrid to check if a subgrid contains duplicate or all the numbers or not

	for(int x=cx;x<cx+root_n;x++)
	{
		for(int y=cy;y<cy+root_n;y++)
		{
			if(mat[x][y]==num)
			{
				return false;
			}
		}
	}

	return true;  //If any of the places(same row and coloumn) are not duplicated
}

bool sudoku_solver(int mat[][9],int i,int j,int n)
{
	//Base case for this will be
	if(i==n)
	{
		//Print the matrix
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<mat[i][j]<<" ";
			}
			//Changing the line 
			cout<<endl;
		}
		return true;
	}
	//If the coloumn gets end for a particular row
	if(j==n)
	{
		return sudoku_solver(mat,i+1,0,n);
	}
	//If there's already an element present in the grid
	if(mat[i][j]!=0)
	{
		return sudoku_solver(mat,i,j+1,n);
	}

	//Now the recursive case
	//THis includes the number feasible for the grid 
	//We have to fill from 1 to n ...here n=9,so
	for(int num=1;num<=n;num++)
	{
		//First check that can we place the number by following the rules that number is not repeated in same row and coloumn

		if(can_put(mat,i,j,n,num))  //If we can place that number then works
			{
				mat[i][j]=num;

				//Let's say the number we have put i,e "num" is correct, then
				bool can_we_solve= sudoku_solver(mat,i,j+1,n); //Stores if we can place the next number at mat[i][j]

				if(can_we_solve==true)  // If the above conditions true, then
				{
					return true;
				}

			}
	}

	//If the above for loop runs completely for a given cell, and result is false

	mat[i][j]=0;
	return false;
} //run main function after that

int main()
{
	int mat[9][9] =
		{
			{0,8,1,0,2,4,0,0,5},
			{6,3,0,0,9,0,7,0,0},
			{0,7,0,0,0,0,0,8,0},
			{2,0,0,0,4,7,5,0,0},
			{0,6,3,0,0,1,2,0,0},
			{0,0,0,0,0,0,0,9,8},
			{0,5,0,0,0,0,0,7,0},
			{0,0,9,6,0,5,0,0,3},
			{0,0,4,8,0,0,1,0,0}
		};

		sudoku_solver(mat,0,0,9);
	return 0;
}
