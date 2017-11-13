#include "DaThuc.h"
Type DaThuc::typeof(char c)
{
	switch (c) {
	case '*': return MUL;
	case '+': return PLUS;
	case '-': return SUB;
	case '^': return POWER;
	case '\0': return END;
	default:
		if (c >= '0' && c <= '9' || c=='.')
			return NUM;
		else
			return BIEN;
	}
}
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
NodeDonThuc* DaThuc::CreateNodeDonThuc(float hs=1,int b=0,char s='x')
{
	NodeDonThuc* donthuc = new NodeDonThuc;
	donthuc->data.bien = new Bien;
	if (donthuc == NULL || donthuc->data.bien==NULL)
		return NULL;
	donthuc->data.hs = hs;
	donthuc->data.bien->ten=s;
	donthuc->data.bien->bac = b;
	donthuc->data.bien->next = NULL;
	donthuc->next = NULL;
	return donthuc;

}

void DaThuc::InsertHead(NodeDonThuc* node) {
	if (donthuc == NULL)
		donthuc = node;
	else
	{
		node->next = donthuc;
		donthuc = node;
	}
}

void DaThuc::NhapTuFile(string filename)
{
	//Đọc file chứa đa thức, viết liền không cách
	//vd: 12*a^3-0.5*a^8+1*a^0-0*b+3.5*b-c+d
	ifstream ifs(filename);
	if (ifs.fail())
		return;
	string strF;
	char c,var;
	string tmp ;
	float hs = 1;
	int deg = 0;
	ifs >> strF;
	State state=INIT;// cho biết kí tự vừa đọc thuộc loại gì (hệ số, biến, bậc, đơn thức)
	//các kí tự terminal: PLUS, SUB	
	for (int i = 0; i <= strF.size(); i++)
	{
		c = strF[i];
		if (c == '*')
			continue;
		Type type = typeof(c);
		switch (state) {
		case INIT:		//wating for new
			if (type == NUM || type==SUB || type==PLUS)
			{
				tmp += c;
				state = HS;
			}else
				if (type == BIEN) {
					state = VAR;
					var = c;
				}
			break;
		case HS:
			if (type == NUM) {
				tmp += c;
				state = HS;
			}
			else 
				if (tmp != "") {
					if (tmp == "-")
						tmp = "-1";		//truong hop he so -1 (-x^k)
					else if (tmp == "+")
						tmp = "1";
					hs = stof(tmp);		//doc duoc he so							
				}
				
			if (type == BIEN) {				
				var = c;			//doc duoc ten bien
				state = VAR;				
			}
			if (type == PLUS || type == SUB || type==END )	//ket thuc 1 don thuc bac 0
			{
				NodeDonThuc* dt= CreateNodeDonThuc(hs, 0, var);
				InsertHead(dt);					//them don thuc moi vao danh sach
				tmp = "";						//He so cua don thuc tiep theo
				tmp += c;			
				state = HS;
			}
			break;
		case VAR:
			if (type == POWER) {
				//san sang nhan so mu
				tmp = "";				
			}
			if (type == NUM) {	//so mu
				tmp += c;
				state = BAC;
			}
			if (type == PLUS || type == SUB || type==END) {		//ket thuc don thuc bac 1
				NodeDonThuc* dt = CreateNodeDonThuc(hs, 1, var);
				InsertHead(dt);					//them don thuc moi vao danh sach
				tmp = "";						//He so cua don thuc tiep theo
				tmp += c;
				state = HS;
			}
			break;
		case BAC:
			if (type == NUM)
				tmp += c;
			else				//ket thuc don thuc bac deg
			{
				deg = stoi(tmp);
				NodeDonThuc* dt = CreateNodeDonThuc(hs, deg, var);
				InsertHead(dt);					//them don thuc moi vao danh sach
				tmp = "";						//He so cua don thuc tiep theo
				tmp += c;
				state = HS;
			}
			break;
		}
	}

}
ofstream& operator <<(ofstream & os, NodeDonThuc donthuc)
{
	os << donthuc.data.hs << "*" << donthuc.data.bien->ten << "^" << donthuc.data.bien->bac;
	return os;
}
void DaThuc::InRaFile(ofstream& fileOut)
{
	fileOut.open("DaThuc.txt", ios_base::out);
	for (NodeDonThuc *p = donthuc; p != NULL; p = p->next)
	{

	}

	//fileOut.close();
}