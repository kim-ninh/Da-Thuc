#include<iostream> 
using namespace std;

int TinhTong(int n)
{
	int tong; 
	for (int i = 1; i <= n; i++)
		tong += i;
	return tong;
}

int TinhGiaiThua(int n)
{
	int GiaiThua;
	for (int i = 1; i <= n; i++)
		GiaiThua *= i;
	return GiaiThua;
}

int DemSoNguyenTo(int a[], int n)
{
	int dem;
	for (int i = 0; i < n; i++)
		if (LaSoNguyenTo(a[i]) == true)
			dem++;
	return dem;
}

int main()
{
	cout << "Hello World";
	return 0;
}