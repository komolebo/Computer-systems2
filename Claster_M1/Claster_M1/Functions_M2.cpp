#include "Functions.h"
#include <Windows.h>
#include <future>
#include <iostream>

using namespace std;

extern Memory mem;
Settings settings_M2;
ProcessorState p1 = FREE, p2 = FREE;

void previous_load_M2(int _N, int _M)
{
	mem.N = _N; mem.M = _M;
	mem.i = mem.j = 0;

	// Generate matrix
	mem.A = new double *[mem.M];
	mem.B = new double *[mem.M];
	mem.C = new double *[mem.M];

	for (int i = 0; i < mem.M; ++i)
	{
		*(mem.A + i) = new double[mem.N];
		*(mem.B + i) = new double[mem.N];
		*(mem.C + i) = new double[mem.N];
	}

	//srand(100);

	for (int i = 0; i < mem.M; ++i)
	{
		for (int j = 0; j < mem.N; ++j)
		{
			// Integer part
			mem.A[i][j] = rand() % settings_M2.MAX_NUMBER + 1;
			mem.B[i][j] = rand() % settings_M2.MAX_NUMBER + 1;

			// Decimal part
			mem.A[i][j] += (double)(rand() % settings_M2.MAX_NUMBER) / settings_M2.MAX_NUMBER;
			mem.B[i][j] += (double)(rand() % settings_M2.MAX_NUMBER) / settings_M2.MAX_NUMBER;
		}
	}
}

void process_M2(int i, int j, int id) {
	mem.C[i][j] = mem.A[i][j] + mem.B[i][j];

	(id == 1) ? (p1 = FREE) : (p2 = FREE);
}

void processor_M2()
{
	for (int i = 0; i < mem.M; ++i)
	{
		for (int j = 0; j < mem.N; ++j)
		{
			while (true)
			{
				if (p1 == FREE)
				{
					p1 = BUSY;
					async(process_M2, i, j, 1);
					break;
				}
				else if (p2 == FREE)
				{
					p2 = BUSY;
					async(process_M2, i, j, 2);
					break;
				}
			}
			system("cls");
			cout << 100 * (i*mem.N + j) / (mem.M * mem.N) << '%' << endl;
		}
	}
}