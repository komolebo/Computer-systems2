#include "Functions.h"
#include <iostream>
#include <Windows.h>

using namespace std;

Memory mem;
Settings settings;
CRITICAL_SECTION cs;

void previous_load_M1(int _N, int _M)
{
	mem.N = _N; mem.M = _M;
	mem.i = mem.j = 0;
	
	// Generate matrix
	mem.A = new double * [mem.M];
	mem.B = new double * [mem.M];
	mem.C = new double * [mem.M];

	for (int i = 0; i < mem.M; ++i)
	{
		*(mem.A + i) = new double[mem.N];
		*(mem.B + i) = new double[mem.N];
		*(mem.C + i) = new double[mem.N];
	}
	for (int i = 0; i < mem.M; ++i)
	{
		for (int j = 0; j < mem.N; ++j)
		{
			// Integer part
			mem.A[i][j] = rand() % settings.MAX_NUMBER + 1;
			mem.B[i][j] = rand() % settings.MAX_NUMBER + 1;

			// Decimal part
			mem.A[i][j] += (double) (rand() % settings.MAX_NUMBER) / settings.MAX_NUMBER;
			mem.B[i][j] += (double) (rand() % settings.MAX_NUMBER) / settings.MAX_NUMBER;
		}
	}
	InitializeCriticalSection(&cs);
}

void process_M1(int id)
{
	int i, j;

	while (true)
	{
		if (mem.i == mem.M)
			break;

		EnterCriticalSection(&cs);

		i = mem.i, j = mem.j;
		if (mem.j == mem.N - 1)
		{
			mem.j = 0;
			mem.i++;
		}
		else
			mem.j++;

		LeaveCriticalSection(&cs);

		mem.C[i][j] = mem.A[i][j] + mem.B[i][j];
		
		system("cls");
		cout << 100 * (i*mem.N + j) / (mem.M * mem.N) << '%' << endl;
	}
}

void output()
{
	cout << endl << "Counted: " << endl << endl;

	for (int i = 0; i < mem.M; ++i)
		for (int j = 0; j < mem.N; ++j)
			printf("%15f + %15f = %15f\n", mem.A[i][j], mem.B[i][j], mem.C[i][j]);
			//cout << endl << mem.A[i][j] << " + " << (double)mem.B[i][j] << " = " << (double)mem.C[i][j] << endl;
}