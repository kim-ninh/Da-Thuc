#include<iostream> 
#include "DaThuc.h"

#define INP_F1 "f1.txt" 
#define INP_F2 "f2.txt" 
#define OUTPUT "f.txt"
using namespace std;

int main()
{
	DaThuc F1, F2;
	F1.NhapTuFile(INP_F1);
	//F2.NhapTuFile(INP_F2);
	fstream ofs;
	ofs.open(OUTPUT, ios_base::out);	
	F1.InRaFile(ofs);
	//F2.InRaFile(ofs);
	ofs.close();
	return 0;
}



