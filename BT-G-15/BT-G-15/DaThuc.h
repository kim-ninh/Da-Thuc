#pragma once
#include <iostream>
#include<fstream>
#include <string>
using namespace std;

enum State {
	HS,
	VAR,
	BAC,
	INIT
};

enum Type {
	NUM, MUL, PLUS, SUB, POWER, BIEN, //số, *, +, -, ^
	END	//ket thuc chuoi
};

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
private:
	NodeDonThuc* donthuc;
	Type typeof(char c);
	void quick_sort(NodeDonThuc*& dt_head, NodeDonThuc*& dt_tail, int(*cmp)(DonThuc&, DonThuc&));
public:
	DaThuc();
	DaThuc(const DaThuc& dathuc);
	~DaThuc();
	NodeDonThuc* CreateNodeDonThuc(float x,int b,char s);
	void InsertHead(NodeDonThuc* node);
	void NhapTuFile(string filename);
	void RutGon();
	int length();// Hàm phụ cho hàm RutGon và DeleteNode
	void DeleteNode(int pos); // Hàm phụ cho hàm RutGon
	void ChuanHoa();
	DonThuc NhanDonThuc(DonThuc d1, DonThuc d2); //Hàm phụ để nhân hai đơn thức
	DaThuc& operator = (const DaThuc&);
	DaThuc operator + (const DaThuc&);
	DaThuc operator - (const DaThuc& dathuc);
	DaThuc operator * (const DaThuc&);
	friend ostream& operator <<(ostream &, DaThuc &);
	/*DaThuc Cong(const DaThuc&);
	DaThuc Tru(const DaThuc&);
	DaThuc Nhan(const DaThuc&);*/
};


/**
* Hàm định nghĩa thứ tự ưu tiên của 2 đơn thức trong đa thức
* @dt1 đa thức 1
* @dt2 đa thức 2
* @return -1 nếu "nhỏ hơn" (dt1 đứng sau) | 0 nếu "bằng nhau"| 1 nếu "lớn hơn" (dt1 đứng trước)
*/
int priority(DonThuc& dt1, DonThuc& dt2);

void addTail(NodeDonThuc*& pHead, NodeDonThuc*& pTail, NodeDonThuc* p);