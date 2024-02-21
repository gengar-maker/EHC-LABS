#include <iostream>
#include <random>
#include <chrono>
#include <math.h>
using namespace std;

void setup();

const int SIZE = 9000;
double __attribute__((aligned(32))) tableA[SIZE][SIZE];
double __attribute__((aligned(32))) tableB[SIZE][SIZE];
double __attribute__((aligned(32))) results[SIZE][SIZE];

int main()
{
	setup();

	auto start = chrono::high_resolution_clock::now(); /********************* Scalar Row Traversing Loop ********************/
#pragma novector
	for (int x = 0; x < SIZE; x++)
	{
#pragma nounroll
#pragma novector
		for (int y = 0; y < SIZE; y++)
		{
			results[x][y] = (tableA[x][y] / tableB[x][y]) - ((double)500.0 * atan(tableB[x][y]));
		}
	}
	auto stop = chrono::high_resolution_clock::now();
	cout << "(unvectorized) Across Rows: " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds\n";

	start = chrono::high_resolution_clock::now(); /******************* Scalar Column Traversing Loop *******************/
#pragma novector
	for (int x = 0; x < SIZE; x++)
	{
#pragma nounroll
#pragma novector
		for (int y = 0; y < SIZE; y++)
		{
			results[y][x] = (tableA[y][x] / tableB[y][x]) - ((double)500.0 * atan(tableB[y][x]));
		}
	}
	stop = chrono::high_resolution_clock::now();
	cout << "(unvectorized) Down Columns: " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds\n";

	start = chrono::high_resolution_clock::now(); /******************* Vectorized Row Traversing Loop ******************/
	for (int x = 0; x < SIZE; x++)
	{
#pragma nounroll
		for (int y = 0; y < SIZE; y++)
		{
			results[x][y] = (tableA[x][y] / tableB[x][y]) - ((double)500.0 * atan(tableB[x][y]));
		}
	}
	stop = chrono::high_resolution_clock::now();
	cout << "(vectorized) Across rows: " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds\n";

	start = chrono::high_resolution_clock::now(); /**************** Interchanged Column Traversing Loop ****************/
	for (int x = 0; x < SIZE; x++)
	{
#pragma nounroll
		for (int y = 0; y < SIZE; y++)
		{
			results[y][x] = (tableA[y][x] / tableB[y][x]) - ((double)500.0 * atan(tableB[y][x]));
		}
	}
	stop = chrono::high_resolution_clock::now();
	cout << "(vectorized) Down Columns: " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds\n";
}

void setup()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			tableA[i][j] = (double)(rand() % 5000);
			tableB[i][j] = (double)((rand() % 4900) + 1);
		}
	}
}
