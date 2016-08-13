#include "Functions.h"
#include <iostream>
#include <Windows.h>

using namespace std;

Memory mem_s;
Settings settings_s;

void previous_load_s(int _N, int _M)
{
	mem_s.N = _N; mem_s.M = _M;
	mem_s.i = mem_s.j = 0;

	// Generate matrix
	mem_s.A = new double *[mem_s.M];
	mem_s.B = new double *[mem_s.M];
	mem_s.C = new double *[mem_s.M];

	for (int i = 0; i < mem_s.M; ++i)
	{
		*(mem_s.A + i) = new double[mem_s.N];
		*(mem_s.B + i) = new double[mem_s.N];
		*(mem_s.C + i) = new double[mem_s.N];
	}
	for (int i = 0; i < mem_s.M; ++i)
	{
		for (int j = 0; j < mem_s.N; ++j)
		{
			// Integer part
			mem_s.A[i][j] = rand() % settings_s.MAX_NUMBER + 1;
			mem_s.B[i][j] = rand() % settings_s.MAX_NUMBER + 1;

			// Decimal part
			mem_s.A[i][j] += (double)(rand() % settings_s.MAX_NUMBER) / settings_s.MAX_NUMBER;
			mem_s.B[i][j] += (double)(rand() % settings_s.MAX_NUMBER) / settings_s.MAX_NUMBER;
		}
	}
}

void process_simple()
{
	for (int i = 0; i < mem_s.M; ++i)
	{
		for (int j = 0; j < mem_s.N; ++j)
		{
			mem_s.C[i][j] = mem_s.A[i][j] + mem_s.B[i][j];

			system("cls");
			cout << 100 * (i*mem_s.N + j) / (mem_s.M * mem_s.N) << '%' << endl;
		}
	}
}

/*
M1 [50][50] = 29.382
M2 [50][50] = 57.855
S  [50][50] = 71.116
*/