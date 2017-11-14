#include"TaoInputDaThuc.h"

float generateRandomFloat()
{
	float Low, High, randomFloat;
	Low = -10;
	High = 10;
	randomFloat = Low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (High - Low)));
	return randomFloat;
}

void randomGenerate(ostream& outDev, short SoDonThuc, short SoDonThucCungBac, short SoDonThucCungBien)
{
	char dsBien[] = { 'x','y'};
	short dsBac[] = { 1,2,4 };
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
		outDev << setprecision(2) <<fixed<< heso << '*' << dsBien[pos] << '^';
		pos = rand() % (sizeof(dsBac) / sizeof(short));
		outDev << dsBac[pos];
	}

}