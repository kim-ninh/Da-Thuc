#pragma once
#include <iostream>
#include<fstream>
using namespace std;

struct Bien
{
	char ten;
	short bac;
	Bien* next;

	Bien();
	Bien(const char ten, const short bac, Bien* next = nullptr);
	Bien(const Bien& bien);
};

struct DonThuc
{
	float hs;
	Bien* bien;

	DonThuc();
	DonThuc(const DonThuc& donthuc);
	int Bac() const;
};

struct NodeDonThuc
{
	DonThuc data;
	NodeDonThuc *next;

	NodeDonThuc();
	NodeDonThuc(const DonThuc& donthuc);
};

class DaThuc
{
public:
	NodeDonThuc* donthuc;

	void quick_sort(NodeDonThuc*& dt_head, NodeDonThuc*& dt_tail, int(*cmp)(DonThuc&, DonThuc&));
public:
	DaThuc();
	DaThuc(const DaThuc& dathuc);
	~DaThuc();
	NodeDonThuc* CreateNodeDonThuc(int x,int b,char s);
	DaThuc NhapTuFile(fstream);
	void RutGon();
	void ChuanHoa();
	DaThuc operator + (const DaThuc&);
	DaThuc operator - (const DaThuc& dathuc);
	DaThuc operator * (const DaThuc&);
	friend ostream& operator <<(ostream &, NodeDonThuc);
	/*DaThuc Cong(const DaThuc&);
	DaThuc Tru(const DaThuc&);
	DaThuc Nhan(const DaThuc&);*/
	void InRaFile(fstream);
};


/**
* Hàm định nghĩa thứ tự sắp xếp của 2 đa thức
* @dt1 đa thức 1
* @dt2 đa thức 2
* @return -1 nếu "nhỏ hơn" | 0 nếu "bằng nhau" | 1 nếu "lớn hơn"
*/
int priority(DonThuc& dt1, DonThuc& dt2);

void addTail(NodeDonThuc*& pHead, NodeDonThuc*& pTail, NodeDonThuc* p);