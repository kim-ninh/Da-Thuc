#pragma once
#include <iostream>
#include<fstream>
using namespace std;

struct Bien
{
	char ten;
	short bac;
	Bien* next;
};

struct DonThuc
{
	float hs;
	Bien* bien;
};

struct NodeDonThuc
{
	DonThuc data;
	NodeDonThuc *next;
};

class DaThuc
{
private:
	NodeDonThuc* donthuc;
public:
	DaThuc();
	~DaThuc();
	NodeDonThuc* CreateNodeDonThuc(int x,int b,char s);
	DaThuc NhapTuFile(fstream);
	void RutGon();
	void ChuanHoa();
	DaThuc operator + (const DaThuc&);
	DaThuc operator - (const DaThuc&);
	DaThuc operator * (const DaThuc&);
	friend ostream& operator <<(ostream &, NodeDonThuc);
	/*DaThuc Cong(const DaThuc&);
	DaThuc Tru(const DaThuc&);
	DaThuc Nhan(const DaThuc&);*/
	void InRaFile(fstream);
};