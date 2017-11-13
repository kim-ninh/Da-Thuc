#include<iostream> 
#include "DaThuc.h"
using namespace std;

int TinhTong(int n)
{
	int tong; 
	tong = 0;
	for (int i = 1; i <= n; i++)
		tong += i;
	return tong;
}

int TinhGiaiThua(int n)
{
	int GiaiThua = 1;
	for (int i = 1; i <= n; i++)
		GiaiThua *= i;
	return GiaiThua;
}


int main()
{

	cout << "Hello World";
	return 0;
}
