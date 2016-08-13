#include "Functions.h"
#include <thread>
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
	int mode, m, n;
	clock_t tStart;

	while (true)
	{
		cout << "Choose mode: 1 - M1,  2 - M2,  3 - Simple system" << endl;
		cin >> mode;

		if (mode > 3) break;

		cout << "M:" << endl;
		cin >> m;
		cout << "N:" << endl;
		cin >> n;

		if (mode == 1)
		{
			cout << "Performing OS M1" << endl;
			previous_load_M1(n, m);

			tStart = clock();

			thread p1(process_M1, 1), p2(process_M1, 2);

			p1.join();
			p2.join();
		}
		else if (mode == 2)
		{
			cout << "Performing OS M2" << endl;
			previous_load_M2(n, m);

			tStart = clock();

			processor_M2();
			//output();
		}
		else if (mode == 3)
		{
			cout << "Performing simple algourithm " << endl;
			previous_load_s(n, m);

			tStart = clock();

			process_simple();
		}

		cout << endl << "Worked for " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;
	}
	
	getchar();

	return 0;
}