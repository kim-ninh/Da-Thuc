#include "DaThuc.h"

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
	donthuc=NULL;			
}

DaThuc::DaThuc(const DaThuc& dathuc)
{
	if (dathuc.donthuc == nullptr)
		return;

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
	DaThuc result(dathuc);
	return result;
}

DaThuc DaThuc::operator-(const DaThuc& dathuc)
{
	// cho rằng cả 2 đa thức đã được chuẩn hóa

	DaThuc f;
	NodeDonThuc *p = this->donthuc;			// dùng để duyệt vòng lặp cho đa thức 1
	NodeDonThuc *q = dathuc.donthuc;		// dùng để duyệt vòng lặp cho đa thức 2
	NodeDonThuc *dummy = new NodeDonThuc();			// tạo node giả, các node từ 2 đa thức sẽ được thêm vào sau node này, được hủy ở cuối hàm
	NodeDonThuc *tail = dummy;			// con trỏ giữ node cuối cùng tạm thời của đa thức kết quả

	while (p != nullptr && q != nullptr)
	{
		if (priority(p->data, q->data) > 0)
		{
			tail->next = new NodeDonThuc(p->data);
			tail = tail->next;
			p = p->next;
		}
		else if (priority(p->data, q->data) < 0)
		{
			tail->next = new NodeDonThuc(q->data);
			tail = tail->next;
			tail->data.hs = -tail->data.hs;
			q = q->next;
		}
		else
		{
			tail->next = new NodeDonThuc(p->data);
			tail = tail->next;
			tail->data.hs += q->data.hs;
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
		tail->data.hs = -tail->data.hs;				// đổi lại dấu hệ số
		q = q->next;
	}

	f.donthuc = dummy->next;		// các node của đa thức kết quả sẽ bắt đầu sau node giả
	delete dummy;	// hủy node giả

	return f;
}

ostream& operator <<(ostream & os, NodeDonThuc *donthuc)
{
	os << donthuc->data.hs << "*" << donthuc->data.bien->ten << "^" << donthuc->data.bien->bac;
	return os;
}
void DaThuc::InRaFile(ostream& fileOut)
{
	NodeDonThuc * p = donthuc;
	
	while (p->next != NULL)
	{
		fileOut << p;
		if (p->data.hs > 0)
			fileOut << '+';
		p = p->next;
	}

	//fileOut.close();
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

void addTail(NodeDonThuc*& pHead, NodeDonThuc*& pTail, NodeDonThuc* p)
{
	if (pHead == nullptr)
		pHead = pTail = p;
	else
	{
		pTail->next = p;
		pTail = pTail->next;
	}
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

void DaThuc::RutGon() {
	if (donthuc == NULL || donthuc->next == NULL)return;
	ChuanHoa();// Sắp xếp đa thức tăng trước khi rút gọn
	NodeDonThuc*p = donthuc;
	NodeDonThuc*q = p->next;
	int pos = 0, n = length();

	// xóa các đơn thức có hệ số bằng 0 hoặc những đơn thức giống nhau hoặc những đơn thức có bậc bằng 0
	while (pos < n) {
		if (p->data.hs == 0) {		// hệ số bằng 0
			p = p->next;
			q = q->next;
			DeleteNode(pos);
			pos++;
			n--;
		}
		if (priority(p->data, q->data) == 0) {		// 2 đơn thức bằng nhau
			p->data.hs += q->data.hs;
			q = q->next;
			pos++;
			DeleteNode(pos);
			pos--;
			n--;
		}
		else if (p->data.bien->bac == 0 && q->data.bien->bac == 0) {		// 2 đơn thức có bậc bằng 0
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