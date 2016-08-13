struct Memory
{
	int i, j;
	int N, M;
	double ** A, ** B, ** C;
};

struct Settings
{
	int N, M;
	long int MAX_NUMBER = 1000000;
};

enum ProcessorState { FREE, BUSY };

void previous_load_M1(int, int);
void previous_load_M2(int, int);
void previous_load_s(int, int);

void process_M1(int );
void processor_M2();
void process_simple();

void output();