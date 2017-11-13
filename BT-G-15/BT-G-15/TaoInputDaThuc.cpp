#include<fstream>
#include<iomanip>
#include<ctime>
using namespace std;

float generateRandomFloat()
{
	float Low, High, randomFloat;
	Low = -128.0;
	High = 127.0;
	randomFloat = Low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (High - Low)));
	return randomFloat;
}

void randomGenerate(ostream& outDev, short SoDonThuc, short SoDonThucCungBac = 0, short SoDonThucCungBien = 0)
{
	srand(time(nullptr));
	char dsBien[] = { 'x','y','z' };
	short dsBac[] = { 0,1,3 };
	float heso;

	char demBac, demBien;
	demBac = demBien = 0;

	int pos;
	for (int i = 0; i < SoDonThuc; i++)
	{
		pos = rand() % (sizeof(dsBien) / sizeof(char));
		heso = generateRandomFloat();
		if (heso > 0 && i != 0)
			outDev << '+';
		outDev << setprecision(4) << heso << '*' << dsBien[pos] << '^';
		pos = rand() % (sizeof(dsBac) / sizeof(short));
		outDev << dsBac[pos];
	}

}