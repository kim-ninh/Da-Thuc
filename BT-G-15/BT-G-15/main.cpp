#include<iostream> 
#include "DaThuc.h"
#include"TaoInputDaThuc.h"
#define INP_F1 "f1.txt" 
#define INP_F2 "f2.txt" 
#define OUTPUT "f.txt"
using namespace std;

void Solve(ostream &os, char times = 1)
{
	ofstream outFile1("input1.txt"), outFile2("input2.txt");
	srand(time(nullptr));
	for (int i = 0; i < times; i++)
	{
		randomGenerate(outFile1, 5);
		randomGenerate(outFile2, 5);
		outFile1.close();
		outFile2.close();
		
		DaThuc F[5];
		F[0].NhapTuFile("input1.txt");
		F[1].NhapTuFile("input2.txt");

		F[0].RutGon();
		F[1].RutGon();
		F[2] = F[0] + F[1];
		F[3] = F[0] - F[1];
		F[4] = F[0] * F[1];
		F[4].RutGon();
		for (int i = 0; i < 5; i++)
		{
			os << 'F' << i + 1 << endl;
			os << F[i] << endl << endl;
		}
	}
}


int main()
{
	Solve(cout);
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



