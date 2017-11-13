#include "DaThuc.h"
DaThuc::DaThuc()
{
	donthuc=NULL;			
}
DaThuc::~DaThuc()
{
	while (donthuc != NULL)
	{
		delete donthuc->data.bien;
		delete donthuc;
		donthuc = donthuc->next;
	}
}
NodeDonThuc* DaThuc::CreateNodeDonThuc(int x,int b,char s)
{
	NodeDonThuc* donthuc = new NodeDonThuc;
	donthuc->data.bien = new Bien;
	if (donthuc == NULL || donthuc->data.bien==NULL)
		return NULL;
	donthuc->data.hs = x;
	donthuc->data.bien->ten=s;
	donthuc->data.bien->bac = b;
	donthuc->data.bien->next = NULL;
	donthuc->next = NULL;
	return donthuc;

}
ostream& operator <<(ostream & os, NodeDonThuc donthuc)
{
	os << donthuc.data.hs << "*" << donthuc.data.bien->ten << "^" << donthuc.data.bien->bac;
	return os;
}
void DaThuc::InRaFile(fstream fileOut)
{
	NodeDonThuc * p = donthuc;
	fileOut.open("DaThuc.txt", ios_base::out);
	while (p->next != NULL)
	{
		fileOut << p;
		if (p->data.hs > 0)
			fileOut << '+';
		p = p->next;
	}

	fileOut.close();
}