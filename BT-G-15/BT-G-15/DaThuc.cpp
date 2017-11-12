#include "DaThuc.h"
DaThuc::DaThuc()
{
	donthuc->data=NULL;			
}
DaThuc::~DaThuc()
{
	while (donthuc != NULL)
	{
		delete[] donthuc;
		donthuc = donthuc->next;
	}
}
ostream& operator <<(ostream & os, NodeDonThuc donthuc)
{
	os << donthuc.data.hs << "*" << donthuc.data.bien->ten << "^" << donthuc.data.bien->bac;
	return os;
}
void DaThuc::InRaFile(fstream fileOut)
{
	fileOut.open("DaThuc.txt", ios_base::out);
	while (donthuc->next != NULL)
	{
		fileOut << donthuc;
		if (donthuc->data.hs > 0)
			fileOut << '+';
		donthuc = donthuc->next;
	}

	fileOut.close();
}