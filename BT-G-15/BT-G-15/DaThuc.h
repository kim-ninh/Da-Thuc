#pragma once
#include <iostream>
#include <string>
#include<fstream>
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

	Type typeof(char c);
public:
	DaThuc();
	~DaThuc();
	NodeDonThuc* CreateNodeDonThuc(float x,int b,char s);
	void InsertHead(NodeDonThuc* node);
	void NhapTuFile(string filename);
	void RutGon();
	void ChuanHoa();
	DaThuc operator + (const DaThuc&);
	DaThuc operator - (const DaThuc&);
	DaThuc operator * (const DaThuc&);
	friend ofstream& operator <<(ofstream &, NodeDonThuc);
	/*DaThuc Cong(const DaThuc&);
	DaThuc Tru(const DaThuc&);
	DaThuc Nhan(const DaThuc&);*/
	void InRaFile(ofstream&);
};