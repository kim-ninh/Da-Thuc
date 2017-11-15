#include<iostream>
#include<fstream>
#include "DaThuc.h"
#include"TaoInputDaThuc.h"
#define INP_F1 "F1.txt" 
#define INP_F2 "F2.txt" 
#define OUTPUT "F-result.txt"
using namespace std;

void Solve(ostream &os, char times = 1)
{
	
	srand(time(nullptr));
	for (int i = 0; i < times; i++)
	{
		ofstream outFile1(INP_F1), outFile2(INP_F2);
		randomGenerate(outFile1, 7);
		randomGenerate(outFile2, 7);
		outFile1.close();
		outFile2.close();

		DaThuc F[5];
		F[0].NhapTuFile(INP_F1);
		F[1].NhapTuFile(INP_F2);

		F[0].RutGon();
		F[1].RutGon();
		F[2] = F[0] + F[1];
		F[3] = F[0] - F[1];
		F[4] = F[0] * F[1];
		for (int i = 0; i < 5; i++)
		{
			os << 'F' << i + 1 << endl;
			os << F[i] << endl << endl;
		}

		os << endl << endl;
	}
}


int main()
{
	ofstream outputFile(OUTPUT);
	Solve(outputFile);
	outputFile.close();
	cin.get();

	//DaThuc F1, F2;
	//F1.NhapTuFile(INP_F1);
	////F2.NhapTuFile(INP_F2);
	//fstream ofs;
	//ofs.open(OUTPUT, ios_base::out);	
	//F1.InRaFile(ofs);
	////F2.InRaFile(ofs);
	//ofs.close();

	
	return 0;
}



