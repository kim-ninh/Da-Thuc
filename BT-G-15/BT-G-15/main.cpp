#include<iostream> 
#include "DaThuc.h"
#include"TaoInputDaThuc.h"
#define INP_F1 "f1.txt" 
#define INP_F2 "f2.txt" 
#define OUTPUT "f.txt"
using namespace std;

int main()
{
	/*ofstream outFile1("input1.txt"), outFile2("input2.txt");
	srand(time(nullptr));
	randomGenerate(outFile1, 3);
	randomGenerate(outFile2, 3);
	outFile1.close();
	outFile2.close();*/

	DaThuc F1, F2, F;
	F1.NhapTuFile("input1.txt");
	
	F2.NhapTuFile("input2.txt");
	
	//DaThuc F(F1 - F2);
	F1.ChuanHoa();
	F1.InRaFile(cout);
	cout << endl;
	F2.ChuanHoa();
	F2.InRaFile(cout);
	F = F1 + F2;
	cout << endl;
	F.InRaFile(cout);
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



