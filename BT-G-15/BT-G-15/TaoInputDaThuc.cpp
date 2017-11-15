#include"TaoInputDaThuc.h"

float generateRandomFloat()
{
	float Low, High, randomFloat;
	Low = -10;
	High = 10;
	randomFloat = Low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (High - Low)));
	return randomFloat;
}

void randomGenerate(ostream& outDev, short SoDonThuc, short SoBienCuaDonThuc, short SoDonThucCungBac, short SoDonThucCungBien)
{
	char dsBien[] = { 'x','y','z'};
	short dsBac[] = { 0,1,2,4 };
	float heso;

	char demBac, demBien;
	demBac = demBien = 0;

	int pos;
	for (int i = 0; i < SoDonThuc; i++)
	{
		
		heso = -10 + rand() % 20;
		if (heso >= 0 && i != 0)
			outDev << '+';
		outDev << setprecision(2) << fixed << heso;
		
		for (int j = 0; j < SoBienCuaDonThuc; j++)
		{
			pos = rand() % (sizeof(dsBien) / sizeof(char));
			outDev << '*' << dsBien[pos] << '^';
			pos = rand() % (sizeof(dsBac) / sizeof(short));
			outDev << dsBac[pos];
		}
	}

}