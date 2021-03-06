﻿#include "DaThuc.h"

Bien::Bien()
{
	this->next = nullptr;
}

Bien::Bien(const char ten, const short bac, Bien* next) : ten(ten), bac(bac), next(next)
{
}

Bien::Bien(const Bien& bien)
{
	this->bac = bien.bac;
	this->ten = bien.ten;
	this->next = nullptr;
}

DonThuc::DonThuc()
{
	this->hs = 0.0f;
	this->bien = nullptr;
}

DonThuc::DonThuc(const DonThuc& donthuc)
{
	this->hs = donthuc.hs;

	Bien *dummy = new Bien();
	Bien *tail = dummy;			// phần tử giả
	Bien *p = donthuc.bien;

	while (p != nullptr)
	{
		tail->next = new Bien(*p);
		tail = tail->next;
		p = p->next;
	}
	
	this->bien = dummy->next;
	delete dummy;
	dummy = nullptr;
}

void DonThuc::ChuanHoa()
{
	if (bien == nullptr)
		return;

	Bien* tail = bien;

	// tìm con trỏ tail, phục vụ cho thao tác sắp xếp
	while (tail->next != nullptr)
		tail = tail->next;

	Sort(bien, tail, priority);
}

int DonThuc::Bac() const
{
	int bac = 0;
	Bien* p = bien;

	while (p != nullptr)
	{
		bac += p->bac;
		p = p->next;
	}

	return bac;
}

NodeDonThuc::NodeDonThuc()
{
	this->next = nullptr;
}

NodeDonThuc::NodeDonThuc(const DonThuc& donthuc)
{
	data = DonThuc(donthuc);
	this->next = nullptr;
}
//input
//Loai ky tu
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
//Chen them don thuc vao dau
void DaThuc::InsertHead(NodeDonThuc* node) {
	if (donthuc == NULL)
		donthuc = node;
	else
	{
		node->next = donthuc;
		donthuc = node;
	}
}
//doc file
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
//------------------

void DaThuc::quick_sort(NodeDonThuc*& dt_head, NodeDonThuc*& dt_tail, int(* cmp)(DonThuc&, DonThuc&))
{
	if (dt_head == dt_tail) // đã có thứ tự
		return;

	NodeDonThuc *dt1_head, *dt1_tail;
	NodeDonThuc *dt2_head, *dt2_tail;

	dt1_head = dt1_tail = nullptr;
	dt2_head = dt2_tail = nullptr;

	NodeDonThuc* X = dt_head;
	dt_head = dt_head->next;
	X->next = nullptr;

	// tách thành 2 dãy con
	while (dt_head != nullptr)
	{
		NodeDonThuc* pNode = dt_head;
		dt_head = dt_head->next;
		pNode->next = nullptr;

		if (cmp(pNode->data, X->data) >= 0)
			addTail(dt1_head, dt1_tail, pNode);
		else
			addTail(dt2_head, dt2_tail, pNode);
	}

	// gọi đệ quy cho 2 dãy con
	quick_sort(dt1_head, dt1_tail, cmp);
	quick_sort(dt2_head, dt2_tail, cmp);

	// nối 2 dãy con và phần tử cầm canh vào
	if (dt1_head != nullptr)
	{
		dt_head = dt1_head;
		dt1_tail->next = X;
	}
	else
		dt_head = X;

	X->next = dt2_head;

	if (dt2_tail != nullptr)
		dt_tail = dt2_tail;
	else
		dt_tail = X;
}

DaThuc::DaThuc()
{
	donthuc=nullptr;			
}

DaThuc::DaThuc(const DaThuc& dathuc)
{
	if (dathuc.donthuc == nullptr)
		this->donthuc = nullptr;

	NodeDonThuc *dummy = new NodeDonThuc();
	NodeDonThuc *tail = dummy;
	NodeDonThuc *p = dathuc.donthuc;

	while (p != nullptr)
	{
		tail->next = new NodeDonThuc(p->data);
		tail = tail->next;
		p = p->next;
	}
	
	this->donthuc = dummy->next;
	delete dummy;
	dummy = nullptr;
}

DaThuc::~DaThuc()
{
	NodeDonThuc *p = donthuc;
	while (p != nullptr)
	{
		donthuc = donthuc->next;					//Cập nhật lại đầu dslk 'donthuc'
													
		Bien *q = p->data.bien;						//Tiến hành xóa dslk 'Bien' trong đơn thức 'p'
		while (q != nullptr)
		{
			p->data.bien = p->data.bien->next;		//Cập nhật lại đầu dslk 'bien'
			delete q;
			q = p->data.bien;
		}

		delete p;
		p = donthuc;
	}
}
NodeDonThuc* DaThuc::CreateNodeDonThuc(float x,int b,char s)
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

void DaThuc::ChuanHoa()
{
	if (donthuc == nullptr)
		return;

	NodeDonThuc* tail = donthuc;

	// tìm con trỏ tail, phục vụ cho thao tác sắp xếp
	while (tail->next != nullptr)
		tail = tail->next;

	quick_sort(donthuc, tail, priority);
}

DaThuc& DaThuc::operator=(const DaThuc & dathuc)
{
	if (dathuc.donthuc == nullptr)
		return DaThuc();
	
	if (this->donthuc != nullptr)
		this->~DaThuc();

	NodeDonThuc *dummy = new NodeDonThuc();
	NodeDonThuc *tail = dummy;
	NodeDonThuc *p = dathuc.donthuc;

	while (p != nullptr)
	{
		tail->next = new NodeDonThuc(p->data);
		tail = tail->next;
		p = p->next;
	}

	this->donthuc = dummy->next;
	delete dummy;
	dummy = nullptr;

	return *this;
}

DaThuc DaThuc::operator+(const DaThuc&dathuc) {
	DaThuc f;
	NodeDonThuc*p = this->donthuc;
	NodeDonThuc*q = dathuc.donthuc;
	NodeDonThuc*dummy = new NodeDonThuc();
	NodeDonThuc*tail = dummy;
	// liên kết 2 đa thức sau đó gọi hàm rút gọn

	// Thêm các node của đa thức 1 vào cuối
	while (p) {
		tail->next = new NodeDonThuc(p->data);
		tail = tail->next;
		p = p->next;
	}

	// thêm các node của đa thức 2 vào cuối (đa thức 1 đã hết)
	while (q) {
		tail->next = new NodeDonThuc(q->data);
		tail = tail->next;
		q = q->next;
	}

	f.donthuc = dummy->next;		// các node của đa thức kết quả sẽ bắt đầu sau node giả
	delete dummy;	// hủy node giả

	f.RutGon();// rút gọn đa thức kết quả
	return f;
}

DaThuc DaThuc::operator-(const DaThuc& dathuc)
{
	DaThuc dt1(*this);
	DaThuc dt2(dathuc);
	dt1.RutGon();
	dt2.RutGon();
	DaThuc f;
	NodeDonThuc *p = dt1.donthuc;           // dùng để duyệt vòng lặp cho đa thức 1
	NodeDonThuc *q = dt2.donthuc;       // dùng để duyệt vòng lặp cho đa thức 2
	NodeDonThuc *dummy = new NodeDonThuc();         // tạo node giả, các node từ 2 đa thức sẽ được thêm vào sau node này, được hủy ở cuối hàm
	NodeDonThuc *tail = dummy;          // con trỏ giữ node cuối cùng tạm thời của đa thức kết quả
	while (p != nullptr && q != nullptr)
	{
		if (priority(p->data, q->data) > 0)                    // đơn thức nằm trong đa thức bị trừ có ưu tiên lớn hơn
		{
			tail->next = new NodeDonThuc(p->data);
			tail = tail->next;
			p = p->next;
		}
		else if (priority(p->data, q->data) < 0)           // đơn thức nằm trong đa thức trừ có ưu tiên lớn hơn
		{
			tail->next = new NodeDonThuc(q->data);
			tail = tail->next;
			tail->data.hs = -tail->data.hs;
			q = q->next;
		}
		else                // 2 đơn thức có cùng độ ưu tiên (chỉ khác hệ số) => cộng 2 hệ số rồi đẩy vào đa thức kết quả
		{
			tail->next = new NodeDonThuc(p->data);
			tail = tail->next;
			tail->data.hs -= q->data.hs;
			p = p->next;
			q = q->next;
		}
	}
	// thêm các node còn lại của đa thức 1 (đa thức 2 đã hết)
	while (p)
	{
		tail->next = new NodeDonThuc(p->data);
		tail = tail->next;
		p = p->next;
	}
	// thêm các node còn lại của đa thức 2 (đa thức 1 đã hết)
	while (q)
	{
		tail->next = new NodeDonThuc(q->data);
		tail = tail->next;
		tail->data.hs = -tail->data.hs;               // đổi lại dấu hệ số
		q = q->next;
	}
	f.donthuc = dummy->next;     // các node của đa thức kết quả sẽ bắt đầu sau node giả
	delete dummy;   // hủy node giả
	f.RutGon();
	return f;           // đa thức kết quả trả về đã chuẩn hóa sẵn, ko cần chuẩn hóa lại
}

DonThuc DaThuc::NhanDonThuc(DonThuc d1, DonThuc d2)
{
	DonThuc result;
	result.hs = d1.hs * d2.hs;

	Bien *p, *dummy, *tail;
	dummy = new Bien();
	tail = dummy;
	
	// Nối các biến của dt1 và dt2 vào 1 dt kết quả, ko nối những biến có bậc bằng 0
	p = d1.bien;					
	while (p != nullptr)
	{
		if (p->bac != 0)
		{
			tail->next = new Bien;
			tail->next->ten = p->ten;
			tail->next->bac = p->bac;

			tail = tail->next;
		}
		p = p->next;
	}	
									
	p = d2.bien;					
	while (p != nullptr)
	{
		if (p->bac != 0)
		{
			tail->next = new Bien;
			tail->next->ten = p->ten;
			tail->next->bac = p->bac;

			tail = tail->next;
		}
		p = p->next;
	}
	tail->next = nullptr;			
	//==============================================
	
	//	Xóa các biến trùng lặp, tăng bậc
	p = dummy->next;
	Bien *q, *pre;
	while (p)
	{
		q = p->next;
		pre = p;
		while (q)
		{
			if (q->ten == p->ten)
			{
				p->bac += q->bac;
				pre->next = q->next;
				Bien *temp = q;
				q = q->next;
				delete temp;
			}
			else
			{
				q = q->next;
				pre = pre->next;
			}
		}
		p = p->next;
	}
	//==================================
	result.bien = dummy->next;	//đầu dslk biến chính là dummy->next
	delete dummy;
	result.ChuanHoa();		
	return result;
}

DaThuc DaThuc::operator*(const DaThuc&dathuc)
{
	DaThuc f;
	NodeDonThuc*p = this->donthuc;
	NodeDonThuc*dummy = new NodeDonThuc();
	NodeDonThuc*tail = dummy;
	while (p)
	{
		NodeDonThuc*q = dathuc.donthuc;		//Tạo mới lại con trỏ q mỗi lần vòng lặp while(q) kết thúc
		while (q)
		{
			DonThuc temp = NhanDonThuc(p->data, q->data); //Tạo một đơn thức
			tail->next = new NodeDonThuc(temp);			//Tạo một node đơn thức rồi gắn vào đa thức mới
			tail = tail->next;
			q = q->next;
		}
		p = p->next;
	}
	f.donthuc = dummy->next;
	delete dummy;
	f.RutGon();
	return f;
}

ostream& operator <<(ostream & os, DaThuc &dathuc)
{
	if (dathuc.donthuc == nullptr)
	{
		os << '0';
		return os;
	}
	NodeDonThuc *p = dathuc.donthuc;

	while (p != nullptr)
	{
		if (p != dathuc.donthuc && p->data.hs >= 0)
			os << '+';
		os << p->data.hs;

		Bien *q = p->data.bien;
		while (q != nullptr)
		{
			if (q->bac != 0 && q->bac != 1)
				os << "*" << q->ten << "^" << q->bac;
			else if (q->bac == 1)
				os << "*" << q->ten;
			q = q->next;
		}

		if (p->next != nullptr)			//Comment lại 2 dòng này để in ra giống như ví dụ của thầy
			os << ' ';					//
		p = p->next;
	}

	return os;
}

int priority(DonThuc& dt1, DonThuc& dt2)
{
	
	int dt1_bac = dt1.Bac();
	int dt2_bac = dt2.Bac();

	// so sánh bậc
	if (dt1_bac < dt2_bac)
		return 1;

	if (dt1_bac > dt2_bac)
		return -1;

	// bậc bằng nhau => duyệt từng cặp tên biến

	Bien* p = dt1.bien;
	Bien* q = dt2.bien;

	while (p != nullptr && q != nullptr)
	{
		if (p->ten < q->ten)
			return 1;
		else if (p->ten > q->ten)
			return -1;
		else
		{
			if (p->bac < q->bac)
				return 1;
			else if (p->bac > q->bac)
				return -1;
		}

		p = p->next;
		q = q->next;
	}

	// đã duyệt hết biến của đa thức 1
	if (q != nullptr)			// đa thức 1 ít biến hơn đa thức 2
		return 1;
	if (p != nullptr)		// đa thức 1 nhiều biến hơn đa thức 2
		return -1;

	// số biến bằng nhau, tên biến bằng nhau
	return 0;
}

template <class T>
void addTail(T*& pHead, T*& pTail, T* p)
{
	if (pHead == nullptr)
		pHead = pTail = p;
	else
	{
		pTail->next = p;
		pTail = pTail->next;
	}
}

void Sort(Bien*& pHead, Bien*& pTail, int(*cmp)(const Bien&, const Bien&))
{
	if (pHead == pTail) // đã có thứ tự
		return;

	Bien *head1, *tail1;
	Bien *head2, *tail2;

	head1 = tail1 = nullptr;
	head2 = tail2 = nullptr;

	Bien* X = pHead;
	pHead = pHead->next;
	X->next = nullptr;

	// tách thành 2 dãy con
	while (pHead != nullptr)
	{
		Bien* pNode = pHead;
		pHead = pHead->next;
		pNode->next = nullptr;

		if (cmp(*pNode, *X) >= 0)
			addTail(head1, tail1, pNode);
		else
			addTail(head2, tail2, pNode);
	}

	// gọi đệ quy cho 2 dãy con
	Sort(head1, tail1, cmp);
	Sort(head2, tail2, cmp);

	// nối 2 dãy con và phần tử cầm canh vào
	if (head1 != nullptr)
	{
		pHead = head1;
		tail1->next = X;
	}
	else
		pHead = X;

	X->next = head2;

	if (tail2 != nullptr)
		pTail = tail2;
	else
		pTail = X;
}

int priority(const Bien& bien1, const Bien& bien2)
{
	// các tên biến trong đơn thức khác nhau từng đôi

	if (bien1.ten < bien2.ten)
		return 1;

	return -1;
}

int DaThuc::length() {
	int count = 0;
	for (NodeDonThuc*p = donthuc; p; p = p->next)count++;
	return count;
}

void DaThuc::DeleteNode(int pos) {
	if (pos < 0 || pos >= length())return;
	if (donthuc == NULL)return;
	if (donthuc->next == NULL) {
		delete donthuc;
		donthuc = NULL;
	}
	else if (pos == 0) {
		NodeDonThuc*p = donthuc;
		donthuc = donthuc->next;
		p->next = NULL;
		delete p;
	}
	else {
		NodeDonThuc*tmp1 = donthuc;
		NodeDonThuc*tmp2 = donthuc->next;
		for (int i = 0; i < pos - 1; i++) {
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		tmp1->next = tmp2->next;
		tmp2->next = NULL;
		delete tmp2;
	}
}

bool KiemTraBac(DonThuc dt1, DonThuc dt2){
	for (Bien*p = dt1.bien; p; p = p->next) {
		if (p->bac != 0){
			return false;
		}
	}
	for (Bien*q = dt2.bien; q; q = q->next) {
		if (q->bac != 0) {
			return false;
		}
	}
	return true;
}

void DaThuc::RutGon() {
	if (donthuc == NULL || donthuc->next == NULL)return;

	ChuanHoa();// Sắp xếp đa thức tăng trước khi rút gọn
	
	NodeDonThuc*p = donthuc;
	NodeDonThuc*q = p->next;
	int pos = 0, n = length();
	int tmp = 0;

	// xóa các đơn thức có hệ số bằng 0 hoặc những đơn thức giống nhau hoặc những đơn thức có bậc bằng 0

	while (p->next!=NULL) {		// đã sửa lại điều kiện vòng lặp
		 if (priority(p->data, q->data) == 0) {		// 2 đơn thức bằng nhau
			p->data.hs += q->data.hs;
			q = q->next;
			pos++;
			DeleteNode(pos);
			pos--;
			n--;
		}
		else if (KiemTraBac(p->data,q->data)==true) {		// 2 đơn thức có bậc bằng 0
			p->data.hs += q->data.hs;
			q = q->next;
			pos++;
			DeleteNode(pos);
			pos--;
			n--;
		}
		else {
			p = p->next;
			q = q->next;
			pos++;
		}
	}
	NodeDonThuc*p1 = donthuc;
	int pos1 = 0;
	while (p1) {
		if (p1->data.hs == 0) {		// hệ số bằng 0
			p1 = p1->next;
			DeleteNode(pos1);
			n--;
		}
		else {
			p1 = p1->next;
			pos1++;
		}
	}
}

