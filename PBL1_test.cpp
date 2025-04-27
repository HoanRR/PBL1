#include "headed.h"
#include "giao_dien.h"


string Vietthuong(string c){
    transform(c.begin(),c.end(),c.begin(),::tolower);
    return c;
}

struct Book {
    string ID;
    string ten;
    string tac_gia;
    string nxb;
    long namsx;
    long soluong;
    bool Trang_thai;
};

struct Node {
    Node* next;
    Book* sach;
};
void drawBox(int x, int y, int width, int height);

void save_to_file(Node *head, const string& filename);
void print_lib(Node* head) ;
void SapXepTheoTenSach(Node *head);
void SapXepTheoTenTacGia(Node *head);
void SapXepTheoNXB(Node *head);
void SapXepTheoNamSX(Node *head);
void Add_RecycleBin(Node *rac,Book *b);
void KhoiPhuc_TatCa(Node *head,Node *rac);
void KhoiPhuc_1Cuon(Node *head, Node *rac);
void KhoiPhuc(Node* head,Node* rac);
bool DelByTenSach(Node *head,Node *rac, string ten);
bool DelByID(Node *head,Node *rac, string ID);

void XoaDau(Node *head,Node *rac);
void XoaCuoi(Node *head,Node *rac);
bool XoaSauMa(Node *head,Node *rac,string ID);
bool DelByTacGia(Node *head,Node *rac, string tg);


void showtt(Node *head,int x , int y);
Book** FindbyID(Node *head,const string& ID);
Node* FindbyTenSach(Node *head,string tensach);
Node* FindbyTacGia(Node *head,string tg);
Node* FindbyNXB(Node *head,string NXB);
Node* FindChuaMuon(Node *head);

void them_sach(Node *head);
void xoa_sach(Node *head,Node *rac);
void Xem_sach(Node* head);
void Thung_rac(Node *head, Node *rac);
void Tim_sach(Node *head);
void Sua_sach(Node *head);

void LuuVaoFile(Node *head);


void MuonSach(const string& Ten,Node *head);
void TraSach(const string& ten, Node *head);
void print_user(const string &ten);
void trang_chu_user(const string& TenDangNhap, Node *head);

// Khởi tạo 1 sách mới
Book* tao_sach(const string& ID, const string& ten, const string& tac_gia, const string& nxb,long namsx,long soluong) {
    Book* sach_moi = new Book;
    sach_moi->ID = ID;
    sach_moi->ten = ten;
    sach_moi->tac_gia = tac_gia;
    sach_moi->nxb = nxb;
    sach_moi->namsx = namsx;
    sach_moi->soluong = soluong;
    if (soluong > 0) sach_moi->Trang_thai = true;
    else sach_moi->Trang_thai = false;
    return sach_moi;
}
// -------------Node giả------------
Node *Head(){
    Node *head = new Node;
    head->next = NULL;
    head->sach = NULL;
    return head;
}

// Khởi tạo node mới
Node* khoitao_node(Book* sach) {
    Node* node_moi = new Node;
    if (node_moi == nullptr) {
        cout << "Het bo nho!!\n";
        return nullptr;
    }
    node_moi->next = nullptr;
    node_moi->sach = sach;
    return node_moi;
}
// --------------------Chèn vào danh sách ----------------

// Thêm vào đầu danh sách
void pushhead(Node* head, Book* sach) {
	Book** kt = FindbyID(head, sach->ID);
	if (kt != NULL && *kt != NULL) {
    	(*kt)->soluong += sach->soluong;
	}
	else{
 	    Node* new_node = khoitao_node(sach);
    	new_node->next = head->next;
        head->next = new_node;
    }
}

// Thêm vào cuối danh sách
void pushend(Node* head, Book* sach) {
	Book** kt = FindbyID(head, sach->ID);
	if (kt != NULL && *kt != NULL) {
    	(*kt)->soluong += sach->soluong;
	}
	else{
	    Node* new_node = khoitao_node(sach);
	    while(head->next!=NULL){
	        head = head->next;
	    }
	    head->next = new_node;
	}
}

//-----------------------Đăng Nhập--------------------------------
string KiemTraDangNhap(const string& TenDangNhap, const string& Matkhau){
    ifstream fi("user.txt");
    string line;
    while (getline(fi,line)){
        stringstream ss(line);
        string ten,mk;
        getline(ss,ten,'|');
        getline(ss,mk,'|');
        if (ten==TenDangNhap && mk==Matkhau){
            return ten;
        }
    }
    gotoXY(21,11);
    cout << "Ten dang nhap hoac mat khau khong dung.\n";
    fi.close();
    return "";
}   
//-----------------------Đăng Ký----------------------------------
void DangKyTaiKhoan() {
    system("cls");
    int x = 20, y = 2, width = 80, height = 12;
    drawBox(x, y, width, height);
    gotoXY(x + (width - 10) / 2, y + 1);   cout << "DANG KY TAI KHOAN";

    fstream fi("user.txt", ios::in | ios::out | ios::app);
    bool kt = true;
    string TenDangNhap, Matkhau;
    
    while (kt) {
        kt = false;
        gotoXY(x + 2, y + 3); cout << "Nhap ten dang nhap: ";
        cin >> TenDangNhap;
        gotoXY(x + 2, y + 4); cout << "Nhap mat khau: ";
        cin >> Matkhau;

        fi.clear();
        fi.seekg(0, ios::beg);
        string line;
        
        while (getline(fi, line)) {
            stringstream ss(line);
            string ten;
            getline(ss, ten, '|');

            if (TenDangNhap.length() >= 5 && TenDangNhap.substr(0, 5) == "admin") {
                kt = true;
                gotoXY(x + 2, y + 6); cout << "Khong duoc su dung ten dang nhap bat dau bang 'admin'. Vui long nhap lai.";
                break;
            } 
            else if (ten == TenDangNhap) {
                kt = true;
                gotoXY(x + 2, y + 6); cout << "Ten dang nhap da ton tai. Vui long nhap lai.";
                break;
            }
        }
    }

    fi.clear();
    fi.seekp(0, ios::end);
    fi << TenDangNhap << "|" << Matkhau << "|" << endl;
    fi.close();

    gotoXY(x + 2, y + 6); cout << "Dang ky thanh cong!";
    Sleep(1500);
}


// ----------------------Đọc từ ----------------------------------

void read_file(Node* &head,const string& TenFile) {
    ifstream fi(TenFile);
    if (!fi.is_open()) {
        cout << "Khong the mo file\n";
        return;
    }

    string line;
    while (getline(fi, line)) {
        stringstream ss(line);
        string ID, ten, tac_gia, nxb, namsx_str, sl,trangthai;

        getline(ss, ID, '|');
        getline(ss, ten, '|');
        getline(ss, tac_gia, '|');
        getline(ss, nxb, '|');
        getline(ss, namsx_str, '|');
        getline(ss, sl, '|');

        long namsx = stol(namsx_str);
        long soluong =stol(sl);
    
        Book* sach = tao_sach(ID, ten, tac_gia, nxb, namsx, soluong);
        pushend(head, sach);
    }

    fi.close();
}


//-----------------------------In ra màn hình---------------------------------------------
// In ra tất cả sách
void print_lib(Node* head) {
    int widths[] = {10, 30, 20, 20, 10, 10, 10};
    const char *headers[] = {"ID", "Ten", "TacGia", "NXB", "Nam", "SoLuong", "TT"};
    int cols = 7;
    int total = 1; 
    for (int i = 0; i < cols; i++) total += widths[i] + 1;
    // Top border
    cout << char(201);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < widths[i]; j++) cout << char(205);
        cout << (i < cols-1 ? char(203) : char(187));
    }
    cout << "\n";
    // Header row
    cout << char(186);
    for (int i = 0; i < cols; i++) {
        string h = headers[i];
        cout << h;
        for (int j = h.length(); j < widths[i]; j++) cout << ' ';
        cout << char(186);
    }
    cout << "\n";
    // Header separator
    cout << char(204);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < widths[i]; j++) cout << char(205);
        cout << (i < cols-1 ? char(206) : char(185));
    }
    cout << "\n";
    // Data rows
    head = head->next;
    while (head) {
        cout << char(186);
        cout << head->sach->ID;
        for (int j = head->sach->ID.length(); j < widths[0]; j++) cout << ' ';
        cout << char(186);
        cout << head->sach->ten;
        for (int j = head->sach->ten.length(); j < widths[1]; j++) cout << ' ';
        cout << char(186);
        cout << head->sach->tac_gia;
        for (int j = head->sach->tac_gia.length(); j < widths[2]; j++) cout << ' ';
        cout << char(186);
        cout << head->sach->nxb;
        for (int j = head->sach->nxb.length(); j < widths[3]; j++) cout << ' ';
        cout << char(186);
        cout << head->sach->namsx;
        for (int j = to_string(head->sach->namsx).length(); j < widths[4]; j++) cout << ' ';
        cout << char(186);
        cout << head->sach->soluong;
        for (int j = to_string(head->sach->soluong).length(); j < widths[5]; j++) cout << ' ';
        cout << char(186);
        string tt = head->sach->Trang_thai ? "Con" : "Het";
        cout << tt;
        for (int j = tt.length(); j < widths[6]; j++) cout << ' ';
        cout << char(186) << "\n";
        head = head->next;
    }
    // Bottom border
    cout << char(200);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < widths[i]; j++) cout << char(205);
        cout << (i < cols-1 ? char(202) : char(188));
    }
    cout << "\n";
}

// ---------------------------- Sap xep-----------------------------

void SapXepTheoTenSach(Node *head){ // tăng dần 
    head = head -> next;
    for (Node *i = head;i!=NULL;i=i->next){
        Node *minNode = i;
        for (Node * j = i->next ; j!=NULL;j=j->next){
            if (j->sach->ten < minNode->sach->ten){
                minNode = j;
            }
        }
        swap(i->sach,minNode->sach);
    }
}

void SapXepTheoTenTacGia(Node *head){ // tăng dần
    head = head -> next;
    for (Node *i = head;i!=NULL;i=i->next){
        Node *minNode = i;
        for (Node * j = i->next ; j!=NULL;j=j->next){
            if (j->sach->tac_gia < minNode->sach->tac_gia){
                minNode = j;
            }
        }
        swap(i->sach,minNode->sach);
    }
}

void SapXepTheoNXB(Node *head){ // tăng dan
    head = head -> next;
    for (Node *i = head;i!=NULL;i=i->next){
        Node *minNode = i;
        for (Node * j = i->next ; j!=NULL;j=j->next){
            if (j->sach->nxb < minNode->sach->nxb){
                minNode = j;
            }
        }
        swap(i->sach,minNode->sach);
    }
}

void SapXepTheoNamSX(Node *head){ // tăng dan
    head = head -> next;
    for (Node *i = head;i!=NULL;i=i->next){
        Node *minNode = i;
        for (Node * j = i->next ; j!=NULL;j=j->next){
            if (j->sach->namsx < minNode->sach->namsx){
                minNode = j;
            }
        }
        swap(i->sach,minNode->sach);
    }
}
// ---------------------------Thung rac-----------------
void Add_RecycleBin(Node *rac, Book *b) {
    if (b == nullptr) return; 
    pushend(rac, b);
    ofstream fo("thung_rac.txt", ios::app);
    if (!fo.is_open()) {
        cout << "Khong the mo file de ghi\n";
        return;
    }
    fo << b->ID << "|"
       << b->ten << "|"
       << b->tac_gia << "|"
       << b->nxb << "|"
       << b->namsx << "|"
       << b->soluong << "|";
       if (b->Trang_thai) fo << "Con"<<endl;
        else fo<<"Het"<<endl;
    fo.close();
}

void KhoiPhuc_TatCa(Node *head,Node *rac){
    Node* temp = rac->next;

    while (temp->next!= NULL){
        pushend(head,temp->sach);
        temp = temp->next;
    }
    save_to_file(head,"thuvien.txt");
    rac->next = NULL;
    save_to_file(rac,"Thung_rac.txt");
}


void KhoiPhuc(Node* head, Node* rac) {
    bool check = true;
    while (check) {
        system("cls");
        int x = 20, y = 2, width = 80, height = 14;
        drawBox(x, y, width, height);
        gotoXY(x + (width - 10) / 2, y + 1);  cout << "KHOI PHUC SACH";

        gotoXY(x + 2, y + 3);  cout << "1. Khoi phuc tat ca";
        gotoXY(x + 2, y + 5);  cout << "2. Khoi phuc 1 cuon sach";
        gotoXY(x + 2, y + 7);  cout << "3. Thoat";
        
        int tt;
        gotoXY(x + 2, y + 9);  cout << "Nhap thao tac: ";
        cin >> tt;
        cin.clear();
        cin.ignore(1000, '\n');

        if (tt == 1) {
            KhoiPhuc_TatCa(head, rac);
            gotoXY(x + 2, y + 11); cout << "Da khoi phuc tat ca sach!";
            Sleep(1500);
        }
        else if (tt == 2) {
            system("cls");
            drawBox(x, y, width, height);
            gotoXY(x + (width - 10) / 2, y + 1);  cout << "KHOI PHUC SACH"; 
            string ID;
            gotoXY(x + 2, y + 3);
            cout <<"Nhap ID sach muon khoi phuc : "; cin >> ID;
            Book** Sach = FindbyID(rac,ID);
            if ((*Sach)!=NULL && Sach != NULL){
            DelByID(rac,rac,ID);
            pushend(head,*Sach);
            }
            save_to_file(head,"thuvien.txt");
            save_to_file(rac,"Thung_rac.txt");
            gotoXY(x + 2, y + 11); cout << "Da khoi phuc 1 cuon sach!";
            Sleep(1500);
        }
        else if (tt == 3) {
            check = false;
        }
        else {
            gotoXY(x + 2, y + 11); cout << "Thao tac khong hop le. Vui long nhap lai!";
            Sleep(1500);
        }
    }
}

// --------------------------- Xoa ----------------------------------
bool DelByID(Node *head,Node *rac, string ID){

    while(head->next!=NULL && Vietthuong(head->next->sach->ID) != Vietthuong(ID)){
        head = head->next;
    }
    if (head->next!=NULL){
        Add_RecycleBin(rac,head->next->sach);
            showtt(head->next,22,6);

        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        return true;
    }

    return false;
}
bool DelByTenSach(Node *head,Node *rac, string ten){

    while(head->next!=NULL && Vietthuong(head->next->sach->ten) != Vietthuong(ten)){
        head = head->next;
    }
    if (head->next!=NULL){
        Add_RecycleBin(rac,head->next->sach);
            showtt(head->next,22,6);

        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        return true;
    }

    return false;

}

bool DelByTacGia(Node *head,Node *rac, string tg){
    bool check = false;
    int x = 22 , y = 6;
while(head->next!=NULL){
    if (Vietthuong(head->next->sach->tac_gia) == Vietthuong(tg)){
        Node *temp = head->next;
        Add_RecycleBin(rac,head->next->sach);
        showtt(head->next,x,y);
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        check = true;
        y+=3;

    }
    else{
        head = head->next;
    }
    }
    return check;
}

void XoaDau(Node *head,Node *rac){
    Add_RecycleBin(rac,head->next->sach);
    showtt(head->next,22,6);
    Node *temp = head->next;
    head->next = head->next->next;
    delete temp->sach;
    delete temp;
}

bool XoaSauMa(Node *head,Node *rac,string ID){
    head = head->next;
    while(head!=NULL && head->next!=NULL && Vietthuong(head->sach->ID) != Vietthuong(ID)){
        head = head->next;
    }
    if (head !=NULL && head->next!=NULL){ // node hiện tại và phía sau đều tồn tại
        Node *temp = head->next;
        Add_RecycleBin(rac,head->next->sach);
        showtt(head->next,22,6);

        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        return true;
    }
    return false;
}

void XoaCuoi(Node *head,Node *rac){
   if (head->next==NULL) return;

   Node *prev = head;
   Node *temp = head->next;

   while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
   }
   Add_RecycleBin(rac,temp->sach);
    showtt(temp,22,6);

   prev->next = NULL;
   delete temp->sach;
   delete temp;
   
}


void showtt(Node *head, int x , int y){
     gotoXY(x,y);
     cout << "ID: " << head->sach->ID;
     gotoXY(x,y+1) ; cout << "Ten: " << head->sach->ten;
}
//-----------------------Tìm Kiếm---------------------
Book** FindbyID(Node *head,const string& ID){
    head = head->next;
    string t = Vietthuong(ID);
    while(head!=NULL){
        if (Vietthuong(head->sach->ID) == t){
            return &(head->sach);
        }
        head = head->next;
    }
    return NULL;
}
Node* FindbyTenSach(Node *head,string tensach){
    Node *DS = Head();
    head = head->next;
    string t = Vietthuong(tensach);
    while(head!=NULL){
        if (Vietthuong(head->sach->ten) == t){
            pushhead(DS,head->sach);
        }
        head = head->next;
    }
    return DS;
}

Node* FindbyTacGia(Node *head,string tg){
    Node *DS = Head();
    head = head->next;
    string t = Vietthuong(tg);
    while(head!=NULL){
        if (Vietthuong(head->sach->tac_gia) == t){
            pushhead(DS,head->sach);
        }
        head = head->next;
    }
    return DS;
}
Node* FindbyNXB(Node *head,string NXB){
    Node *DS = Head();
    head = head->next;
    string t = Vietthuong(NXB);
    while(head!=NULL){
        if (Vietthuong(head->sach->nxb) == t){
            pushhead(DS,head->sach);
        }
        head = head->next;
    }
    return DS;
}
Node* FindChuaMuon(Node *head){
    Node *DS = Head();
    head = head->next;
    while(head!=NULL){
        if (head->sach->Trang_thai){
            pushend(DS,head->sach);
        }
        head = head->next;
    }
    return DS;
}

// ------------lưu lại danh sách liên kết vào file---------
void save_to_file(Node *head, const string& filename){ 
    ofstream fo(filename);
    head = head->next;
    if (!fo.is_open()){
        cout << "Khong the mo file de ghi\n";
        return;
    }
    Node *temp = head;
    while (temp !=NULL){
        Book *b = temp->sach;
        fo << b->ID << "|"
           << b->ten << "|"
           << b->tac_gia << "|"
           << b->nxb << "|"
           << b->namsx << "|"
           << b->soluong << "|";
        if (b->Trang_thai) fo << "Con|"<<endl;
        else fo<<"Het|"<<endl;
        temp = temp->next;
    }
    fo.close();
}

// ------------------------------- Các thao tác -----------------------------


void them_sach(Node *head) {
    system("cls");
    int x = 20, y = 2, width = 80, height = 25;
    drawBox(x, y, width, height);

    gotoXY(x + (width - 20) / 2, y + 1);
    cout << "THEM SACH VAO THU VIEN";

    string ID, tensach, tacgia, NXB;
    long namsx, sluong;

    gotoXY(x + 2, y + 3);
    cout << "Nhap ID: ";
    getline(cin, ID);

    gotoXY(x + 2, y + 5);
    cout << "Nhap ten sach: ";
    getline(cin, tensach);

    gotoXY(x + 2, y + 7);
    cout << "Nhap ten tac gia: ";
    getline(cin, tacgia);

    gotoXY(x + 2, y + 9);
    cout << "Nhap Nha xuat ban: ";
    getline(cin, NXB);

    gotoXY(x + 2, y + 11);
    cout << "Nhap Nam San Xuat: ";
    cin >> namsx;

    gotoXY(x + 2, y + 13);
    cout << "Nhap So Luong: ";
    cin >> sluong;
    cin.ignore();

    Book *C = tao_sach(ID, tensach, tacgia, NXB, namsx, sluong);

    gotoXY(x + 2, y + 15);
    cout << "1. Them vao dau";
    gotoXY(x + 2, y + 16);
    cout << "2. Them vao cuoi";
    bool check = true;
    int tt;
    gotoXY(x + 2, y + 17);
    cout << "Nhap thao tac: ";
    cin >> tt;
    cin.clear();
    int i = 1;
    while (tt != 1 && tt != 2) {
        gotoXY(x + 2, y + 18 +i);
        cout << "Thao tac khong hop le!. Nhap lai : ";
        cin >> tt;
        i++;
    }

    if (tt == 1) {
        pushhead(head, C);
    } else {
        pushend(head, C);
    }

    save_to_file(head, "thuvien.txt");

    gotoXY(x + 2, y + height-3);
    cout << "Da them sach thanh cong!";
    Sleep(1500);
}
void xoa_sach(Node *head, Node *rac) {
    bool check = true;
    while(check){
    system("cls");
    int x = 20, y = 2, width = 80, height = 22;
    drawBox(x, y, width, height);

    gotoXY(x + (width - 12) / 2, y + 1);
    cout << "XOA SACH";

    gotoXY(x + 2, y + 3);
    cout << "1. Theo Ma So";
    gotoXY(x + 2, y + 5);
    cout << "2. Theo Ten Sach";
    gotoXY(x + 2, y + 7);
    cout << "3. Theo Ten Tac Gia";
    gotoXY(x + 2, y + 9);
    cout << "4. Xoa dau danh sach";
    gotoXY(x + 2, y + 11);
    cout << "5. Xoa sau ma so";
    gotoXY(x + 2, y + 13);
    cout << "6. Xoa cuoi danh sach";
    gotoXY(x+2,y+15);
    cout << "7. Thoat";

    int tt;
    gotoXY(x + 2, y + 17);
    cout << "Nhap thao tac: ";
    cin >> tt;
    cin.clear();
    cin.ignore(1000, '\n');

    int i = 1;
    while (tt != 1 && tt != 2 && tt!=3 && tt!=4 && tt!=5 && tt!=6 && tt!=7) {
        gotoXY(x + 2, y + 17 +i);
        cout << "Thao tac khong hop le!. Nhap lai : ";
        cin >> tt;
        cin.clear();
        cin.ignore(1000,'\n');
        i++;
    }

    system("cls");
    string ID, ts, tg;
    bool ok = false;
    drawBox(x, y, width, height);
    gotoXY(x + (width - 12) / 2, y + 1);
    cout << "XOA SACH";
    gotoXY(x + 2, y + 3);
    switch (tt) {
        case 1:
            cout << "Nhap ma so: ";
            getline(cin, ID);
            ok = DelByID(head, rac, ID);
            break;
        case 2:
            cout << "Nhap ten sach: ";
            getline(cin, ts);
            ok = DelByTenSach(head, rac, ts);
            break;
        case 3:
            cout << "Nhap ten tac gia: ";
            getline(cin, tg);
            ok = DelByTacGia(head, rac, tg);
            break;
        case 4:
            XoaDau(head, rac);
            ok = true;
            break;
        case 5:
            cout << "Nhap ma so: ";
            getline(cin, ID);
            ok = XoaSauMa(head, rac, ID);
            break;
        case 6:
            XoaCuoi(head, rac);
            ok = true;
            break;
        case 7:
            check = false;
            break;
    }
    if (tt!=7){
    if (ok) {
        gotoXY(x + 2, y + 18);
        cout << "Xoa thanh cong!";
    } else {
        gotoXY(x + 2, y + 7);
        cout << "Khong tim thay!";
    }}
    save_to_file(head, "thuvien.txt");
    if (tt!=7) system("pause");
}
}

void Thung_rac(Node *head, Node *rac) {
    bool check = true;
    while (check) {
        system("cls");
        int x = 20, y = 2, width = 80, height = 20;
        drawBox(x, y, width, height);

        gotoXY(x + (width - 10) / 2, y + 1);
        cout << "THUNG RAC";

        gotoXY(x + 2, y + 3);
        cout << "1. Xem thung rac";
        gotoXY(x + 2, y + 5);
        cout << "2. Tim sach";
        gotoXY(x + 2, y + 7);
        cout << "3. Khoi phuc tu thung rac";
        gotoXY(x + 2, y + 9);
        cout << "4. Thoat";

        int tt;
        gotoXY(x + 2, y + 11);
        cout << "Nhap thao tac: ";
        cin >> tt;
        cin.clear();
        cin.ignore(1000, '\n');

        while (tt < 1 || tt > 4) {
            gotoXY(x + 2, y + 13);
            cout << "Thao tac khong hop le! Nhap lai: ";
            cin >> tt;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        system("cls");
        switch (tt) {
            case 1:
                Xem_sach(rac);
                break;
            case 2:
                Tim_sach(rac);
                break;
            case 3:
                KhoiPhuc(head, rac);
                break;
            case 4:
                check = false;
                break;
        }
        if (tt != 4) {
            cout << "\nNhan phim bat ky de tiep tuc...";
            _getch();
        }
    }
}


void Tim_sach(Node *head) {
    bool check = true;
    while (check) {
        system("cls");
        int x = 20, y = 2, width = 80, height = 20;
        drawBox(x, y, width, height);

        gotoXY(x + (width - 12) / 2, y + 1);
        cout << "TIM SACH";

        gotoXY(x + 2, y + 3);
        cout << "1. Theo ten sach";
        gotoXY(x + 2, y + 5);
        cout << "2. Theo ten tac gia";
        gotoXY(x + 2, y + 7);
        cout << "3. Theo ten NXB";
        gotoXY(x + 2, y + 9);
        cout << "4. Sach chua muon";
        gotoXY(x + 2, y + 11);
        cout << "5. Thoat";


        int tt;
        gotoXY(x + 2, y + 13);
        cout << "Nhap thao tac: ";
        cin >> tt;
        cin.clear();
        cin.ignore(1000, '\n');
        bool check1 = true;
        if (tt < 1 || tt > 5) {
            gotoXY(x + 2, y + 15);
            cout << "Thao tac khong hop le!";
            Sleep(1000);
            check1 = false;
        }
        if (!check1) continue;

        system("cls");
        string input;
        Node* ds = NULL;

        switch (tt) {
            case 1:
                drawBox(x, y, width, height);
                gotoXY(x + (width - 12) / 2, y + 1);
                cout << "TIM SACH";
                gotoXY(x+2,y+3);
                cout << "Nhap ten sach: ";
                getline(cin, input);
                ds = FindbyTenSach(head, input);
                system("cls");
                break;
            case 2:
                drawBox(x, y, width, height);
                gotoXY(x + (width - 12) / 2, y + 1);
                cout << "TIM SACH";
                gotoXY(x+2,y+3);
                cout << "Nhap ten tac gia: ";
                getline(cin, input);
                ds = FindbyTacGia(head, input);
                system("cls");
                break;
            case 3:
                drawBox(x, y, width, height);
                gotoXY(x + (width - 12) / 2, y + 1);
                cout << "TIM SACH";
                gotoXY(x+2,y+3);
                cout << "Nhap ten NXB: ";
                getline(cin, input);
                ds = FindbyNXB(head, input);
                system("cls");
                break;
            case 4:
                ds = FindChuaMuon(head);
                break;
            case 5:
                check = false;
                break;
        }   

        if (ds != NULL && ds->next != NULL) {
            cout << "------------Danh sach liet ke --------------------\n";
            print_lib(ds);
            delete ds;
        } else {
            drawBox(x, y, width, height);
                gotoXY(x + (width - 12) / 2, y + 1);
                cout << "TIM SACH";
                gotoXY(x+2,y+3);
            cout << "Thu vien khong co sach nay!\n";
        }

        if (tt != 5) {
            gotoXY(x+2,y+5);

            cout << "Nhan phim bat ky de tiep tuc...";
            _getch();
        }
    }
}


void Sua_sach(Node *head) {
    system("cls");
    int x = 20, y = 2, width = 80, height = 20;
    drawBox(x, y, width, height+3);
    gotoXY(x + (width - 12) / 2, y + 1);
    cout << "SUA SACH";

    gotoXY(x + 2, y + 3);
    cout << "Nhap ID sach can sua: ";
    string ID;
    getline(cin, ID);
    Book **Vitri = FindbyID(head, ID);
    if (!Vitri || !*Vitri) {
        gotoXY(x + 2, y + 5);
        cout << "Khong tim thay sach!";
        Sleep(1500);
        return;
    }

    bool check = true;
    while (check) {
        system("cls");
        drawBox(x, y, width, height+5);
        gotoXY(x + (width - 12) / 2, y + 1);
        cout << "SUA SACH";

        gotoXY(x + 2, y + 3);
        cout << "1. Sua ID";
        gotoXY(x + 2, y + 5);
        cout << "2. Sua Ten Sach";
        gotoXY(x + 2, y + 7);
        cout << "3. Sua Tac Gia";
        gotoXY(x + 2, y + 9);
        cout << "4. Sua NXB";
        gotoXY(x + 2, y + 11);
        cout << "5. Sua Nam SX";
        gotoXY(x + 2, y + 13);
        cout << "6. Sua So Luong";
        gotoXY(x + 2, y + 15);
        cout << "7. Thoat";

        int tt;
        gotoXY(x + 2, y + 17);
        cout << "Nhap thao tac: ";
        cin >> tt;
        cin.clear();
        cin.ignore(1000, '\n');
        bool  ok = true;
        switch (tt) {
            case 1: {
                gotoXY(x + 2, y + 18);
                cout << "Nhap ID moi: ";
                string id; getline(cin, id);
                (*Vitri)->ID = id;
                break;
            }
            case 2: {
                gotoXY(x + 2, y + 18);
                cout << "Nhap ten moi: ";
                string ten; getline(cin, ten);
                (*Vitri)->ten = ten;
                break;
            }
            case 3: {
                gotoXY(x + 2, y + 18);
                cout << "Nhap tac gia moi: ";
                string tg; getline(cin, tg);
                (*Vitri)->tac_gia = tg;
                break;
            }
            case 4: {
                gotoXY(x + 2, y + 18);
                cout << "Nhap NXB moi: ";
                string nxb; getline(cin, nxb);
                (*Vitri)->nxb = nxb;
                break;
            }
            case 5: {
                gotoXY(x + 2, y + 18);
                cout << "Nhap nam SX moi: ";
                long sx; cin >> sx;
                (*Vitri)->namsx = sx;
                break;
            }
            case 6: {
                gotoXY(x + 2, y + 18);
                cout << "Nhap so luong moi: ";
                long soluong; cin >> soluong;
                (*Vitri)->soluong = soluong;
                (*Vitri)->Trang_thai = (soluong > 0);
                break;
            }
            case 7:
                check = false;
                continue;
            default:
                ok = false;
                gotoXY(x + 2, y + 18);
                cout << "Thao tac khong hop le!";
                break;
        }

        save_to_file(head, "thuvien.txt");
        gotoXY(x + 2, y + 19);
        if (ok) cout << "Sua doi thanh cong!";
        Sleep(1500);
    }
}




void Xem_sach(Node *head) {
    bool check = true;
    while (check) {
        system("cls");
        int x = 20, y = 2, width = 80, height = 12;
        drawBox(x, y, width, height+8);
        gotoXY(x + (width - 8) / 2, y + 1);    cout << "XEM SACH";
        gotoXY(x + 2, y + 3);                  cout << "1. Xem toan bo danh sach";
        gotoXY(x + 2, y + 5);                  cout << "2. Xem theo thu tu";
        gotoXY(x + 2, y + 7);                  cout << "3. Thoat";
        gotoXY(x + 2, y + 9 );
        cout << "Nhap thao tac: ";

        int tt;
        cin >> tt;
        cin.clear();
        cin.ignore(1000, '\n');
        while (tt < 1 || tt > 3) {
            gotoXY(x + 2, y + 18);
            cout << "Thao tac khong hop le! Nhap lai: ";
            cin >> tt;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (tt == 1) {
            system("cls");
            print_lib(head);
            gotoXY(x+2,y+18);
            cout << "Nhan phim bat ky de tiep tuc...";
            _getch();
        }
        else if (tt == 2) {
            bool sub = true;
            while (sub) {
                system("cls");
                drawBox(x, y, width, height+5);
                gotoXY(x + (width - 16) / 2, y + 1);  cout << "SAP XEP SACH";
                gotoXY(x + 2, y + 3);                  cout << "1. Theo ten sach";
                gotoXY(x + 2, y + 5);                  cout << "2. Theo tac gia";
                gotoXY(x + 2, y + 7);                  cout << "3. Theo NXB";
                gotoXY(x + 2, y + 9);                  cout << "4. Theo nam SX";
                gotoXY(x + 2, y + 11);                 cout << "5. Thoat";
                gotoXY(x + 2, y + 13);                 cout << "Nhap thao tac: ";

                int tt2;
                cin >> tt2;
                cin.clear();
                cin.ignore(1000, '\n');
                while (tt2 < 1 || tt2 > 5) {
                    gotoXY(x + 2, y + 15);
                    cout << "Thao tac khong hop le! Nhap lai: ";
                    cin >> tt2;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                switch (tt2) {
                    case 1: SapXepTheoTenSach(head); break;
                    case 2: SapXepTheoTenTacGia(head); break;
                    case 3: SapXepTheoNXB(head); break;
                    case 4: SapXepTheoNamSX(head); break;
                    case 5: sub = false; continue;
                }

                system("cls");
                print_lib(head);
                gotoXY(x+2,y+18);
                cout << "Nhan phim bat ky de tiep tuc...";
                _getch();
                sub = false;
            }
        }
        else {
            check = false;
        }
    }
}


// hàm ni dùng ở đâu ri
void LuuVaoFile(Node *head){
    system("cls");
    int x = 20, y = 2, width = 80, height = 20;
    drawBox(x, y, width, height+3);
    gotoXY(x + (width - 12) / 2, y + 1);
    cout << "Luu vao FIle";

    gotoXY(x + 2, y + 3);
    string file_name;
    cout << "Nhap ten file de luu : ";
    getline(cin,file_name);
    save_to_file(head,file_name);
    gotoXY(x+2,y+5) ; cout << "Luu thanh cong !";
    gotoXY(x+2,y+7); system("pause");
}

void trang_chu_admin(Node *head) {
    Node *rac = Head();
    read_file(rac, "thung_rac.txt");
    bool cnt = true;
    while (cnt) {
        system("cls");
        int x = 25, y = 3, width = 70, height = 24;
        drawBox(x, y, width, height);

        gotoXY(x + (width - 24) / 2, y + 1);
        cout << "QUAN LY THU VIEN ADMIN";

        gotoXY(x + 2, y + 3);
        cout << "1. Them sach vao danh sach";
        gotoXY(x + 2, y + 5);
        cout << "2. Xoa sach";
        gotoXY(x + 2, y + 7);
        cout << "3. Tim kiem sach";
        gotoXY(x + 2, y + 9);
        cout << "4. Xem sach";
        gotoXY(x + 2, y + 11);
        cout << "5. Thung rac";
        gotoXY(x + 2, y + 13);
        cout << "6. Sua noi dung sach";
        gotoXY(x + 2, y + 15);
        cout << "7. Luu vao file";
        gotoXY(x + 2, y + 17);
        cout << "8. Thoat";

        gotoXY(x + 2, y + 19);
        cout << "Nhap thao tac: ";
        int tt;
        cin >> tt;

        cin.clear();
        cin.ignore(1000, '\n');

        switch (tt) {
            case 1:
                them_sach(head);
                break;
            case 2:
                xoa_sach(head, rac);
                break;
            case 3:
                Tim_sach(head);
                break;
            case 4:
                Xem_sach(head);
                break;
            case 5:
                Thung_rac(head, rac);
                break;
            case 6:
                Sua_sach(head);
                break;
            case 7:
                LuuVaoFile(head);
                break;
            case 8:
                cnt = false;
                break;
            default:
                gotoXY(x + 2, y + height-2);
                cout << "Thao tac khong hop le!";
                Sleep(1000);
                break;
        }
    }
    save_to_file(head, "thuvien.txt");
}

//----------------Mượn sách -----------------
void MuonSach(const string& TenDangNhap, Node *head) {
    system("cls");
    int x = 20, y = 2, width = 80, height = 12;
    drawBox(x, y, width, height);
    gotoXY(x + (width - 10) / 2, y + 1);   cout << "MUON SACH";

    gotoXY(x + 2, y + 3);                  cout << "Nhap ID sach can muon: ";
    string ID; 
    cin >> ID;
    cin.clear();
    cin.ignore(1000, '\n');

    Book** sach = FindbyID(head, ID);
    if (!sach || !*sach) {
        gotoXY(x + 2, y + 5);              cout << "Khong tim thay sach!";
        Sleep(1500);
        return;
    }
    if (!(*sach)->Trang_thai) {
        gotoXY(x + 2, y + 5);              cout << "Sach da het!";
        Sleep(1500);
        return;
    }

    (*sach)->soluong--;
    if ((*sach)->soluong == 0) (*sach)->Trang_thai = false;
    save_to_file(head, "thuvien.txt");

    string filename = TenDangNhap + ".txt";
    ofstream fo(filename, ios::app);
    time_t now = time(0);
    string dt = ctime(&now);
    dt.pop_back();

    fo << (*sach)->ID << "|"
       << (*sach)->ten << "|"
       << (*sach)->tac_gia << "|"
       << dt << "|\n";
    fo.close();

    gotoXY(x + 2, y + 5);                  cout << "Muon sach thanh cong!";
    gotoXY(x+2,y+6) ; cout << "Ten sach : " << (*sach)->ten << endl;
    gotoXY(x+2,y+7) ; cout << "Thoi gian muon : " << ctime(&now);
    gotoXY(x+2,y+8);
    system("pause");
}


void TraSach(const string& TenDangNhap, Node *head) {
    system("cls");
    int x = 20, y = 2, width = 80, height = 12;
    drawBox(x, y, width, height);
    gotoXY(x + (width - 10) / 2, y + 1);   cout << "TRA SACH";

    gotoXY(x + 2, y + 3);                  cout << "Nhap ID sach can tra: ";
    string ID; 
    cin >> ID;
    cin.clear();
    cin.ignore(1000, '\n');

    string filename = TenDangNhap + ".txt";
    ifstream fi(filename);
    if (!fi.is_open()) {
        gotoXY(x + 2, y + 5);              cout << "Khong mo duoc file nguoi dung!";
        Sleep(1500);
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;
    while (getline(fi, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if (id != ID) {
            lines.push_back(line);
        } else {
            found = true;
        }
    }
    fi.close();

    if (!found) {
        gotoXY(x + 2, y + 5);              cout << "Loi tra sach! Khong tim thay sach.";
        Sleep(1500);
        return;
    }

    // Ghi lai file sau khi xoa sach tra
    ofstream fo(filename, ios::trunc);
    for (const auto& dong : lines) {
        fo << dong << endl;
    }
    fo.close();

    // Cap nhat lai so luong sach
    Book** sach = FindbyID(head, ID);
    if (sach && *sach) {
        (*sach)->soluong++;
        (*sach)->Trang_thai = true; // Neu so luong > 0 thi co san
        save_to_file(head, "thuvien.txt");
    }
    time_t now = time(0);
    gotoXY(x + 2, y + 5);                  cout << "Tra sach thanh cong!";
    gotoXY(x+2,y+6) ; cout << "Ten sach : " << (*sach)->ten << endl;
    gotoXY(x+2,y+7) ; cout << "Thoi gian tra : " << ctime(&now);
    gotoXY(x+2,y+8);
    system("pause");
}

//---------------in sach da muon-------------
void print_user(const string &ten) {
    system("cls");
    int x = 20, y = 2, width = 80, height = 25;
    drawBox(x, y, width, height);
    gotoXY(x + (width - 20) / 2, y + 1); cout << "DANH SACH SACH DA MUON";

    string temp = ten + ".txt";
    ifstream fi(temp);
    string line;
    int i = 1;

    if (!fi) {
        gotoXY(x + 2, y + 3); cout << "Khong co sach da muon!";
        return;
    }

    while (getline(fi, line)) {
        string ID, ten, tacgia, ThoiGian;
        stringstream ss(line);
        getline(ss, ID, '|');
        getline(ss, ten, '|');
        getline(ss, tacgia, '|');
        getline(ss, ThoiGian, '|');
        
        gotoXY(x + 2, y -3 + i * 6); cout << "Sach: " << i;
        gotoXY(x + 2, y  -2 + i * 6); cout << "ID: " << ID;
        gotoXY(x + 2, y - 1 + i * 6); cout << "Ten: " << ten;
        gotoXY(x + 2, y  + i * 6); cout << "Tac Gia: " << tacgia;
        gotoXY(x + 2, y +1 + i * 6); cout << "Thoi gian muon: " << ThoiGian;
        i++;
    }
    cout << endl;
    gotoXY(x+2,y+2+(i-1)*6);
    system("pause");
    fi.close();
}


void trang_chu_user(const string& TenDangNhap, Node *head) {
    bool cnt = true;
    while (cnt) {
        system("cls");
        int x = 25, y = 3, width = 70, height = 18;
        drawBox(x, y, width, height);

        gotoXY(x + (width - 16) / 2, y + 1);
        cout << "THU VIEN USER";

        gotoXY(x + 2, y + 3);
        cout << "1. Tim kiem sach";
        gotoXY(x + 2, y + 5);
        cout << "2. Xem sach da muon";
        gotoXY(x + 2, y + 7);
        cout << "3. Muon sach";
        gotoXY(x + 2, y + 9);
        cout << "4. Tra sach";
        gotoXY(x + 2, y + 11);
        cout << "5. Dang xuat";

        gotoXY(x + 2, y + 13);
        cout << "Nhap thao tac: ";
        int tt;
        cin >> tt;

        cin.clear();
        cin.ignore(1000, '\n');

        switch (tt) {
            case 1:
                Tim_sach(head);
                break;
            case 2:
                print_user(TenDangNhap);
                break;
            case 3:
                MuonSach(TenDangNhap, head);
                break;
            case 4:
                TraSach(TenDangNhap, head);
                break;
            case 5:
                cnt = false;
                break;
            default:
                gotoXY(x + 2, y + height-2);
                cout << "Thao tac khong hop le!";
                Sleep(1000);
                break;
        }
    }
    save_to_file(head, "thuvien.txt");
}


//--------------đăng nhập--------------
string NhapMatKhau() {
    string matkhau = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) break; // Enter
        else if (ch == 8) { // Backspace
            if (!matkhau.empty()) {
                cout << "\b \b";
                matkhau.pop_back();
            }
        }
        else {
            matkhau.push_back(ch);
            cout << '*';
        }
    }
    return matkhau;
}

string dangnhap() {
    string TenDangNhap;
    string MatKhau;
    string s;
    for (int i = 3; i > 0; i--) {
        system("cls");
        int x = 20, y = 5, width = 60, height = 15;
        drawBox(x, y, width, height);
        gotoXY(x + (width - 18) / 2, y + 1);
        cout << "DANG NHAP HE THONG";
        gotoXY(x + 2, y + 3);
        cout << "Ten dang nhap: ";
        gotoXY(x + 18, y + 3);
        cin >> TenDangNhap;
        gotoXY(x + 2, y + 5);
        cout << "Mat khau: ";
        gotoXY(x + 18, y + 5);
        MatKhau = NhapMatKhau();
        cout << endl;
        s = KiemTraDangNhap(TenDangNhap, MatKhau);
        if (s == "" && i - 1 != 0) {
            gotoXY(x + 2, y + 7);
            cout << "Sai thong tin. Con " << i - 1 << " lan dang nhap.";
            Sleep(1500);
        }
        else if (s == "" && i - 1 == 0) {
            gotoXY(x + 2, y + 7);
            cout << "Da het lan dang nhap.";
            Sleep(1500);
        }
        else break;
    }
    if (s == "") exit(0);
    else return s;
}

void drawBox(int x, int y, int width, int height) {
    gotoXY(x, y);
    cout << char(201); // ╔
    for (int i = 0; i < width - 2; i++) cout << char(205); // ═
    cout << char(187); // ╗

    for (int i = 1; i < height - 1; i++) {
        gotoXY(x, y + i);
        cout << char(186); // ║
        gotoXY(x + width - 1, y + i);
        cout << char(186); // ║
    }

    gotoXY(x, y + height - 1);
    cout << char(200); // ╚
    for (int i = 0; i < width - 2; i++) cout << char(205); // ═
    cout << char(188); // ╝
}
void showIntro() {
    system("cls");
    //SetColor(11);
    drawBox(20, 5, 60, 10);
    gotoXY(30, 8);
    cout << "CHAO MUNG BAN DEN VOI CHUONG TRINH";
    Sleep(2000); // dừng lại 2 gi
}

void showHomePage() {
    system("cls");
    drawBox(20, 5, 60, 16);
    gotoXY(45, 7);
    cout << "TRANG CHU";
    gotoXY(30, 10);
    cout << "1. Dang nhap";
    gotoXY(30, 12);
    cout << "2. Dang ky";
    gotoXY(30, 14);
    cout << "0. Thoat chuong trinh";
    gotoXY(28, 17);
    cout << "Nhap lua chon: ";
}


void menuLoop(Node* head) {
    int choice;
    do {
    showHomePage();
    SetColor(15);
    gotoXY(44, 17);
    cin >> choice;

    if (choice == 27) {
        system("cls");
        gotoXY(10, 10);
        cout << "Dang thoat chuong trinh...";
        Sleep(1000);
        exit(0);
    }

    switch (choice) {
    case 1: {
        system("cls");
        string user = dangnhap();
        system("cls");
        if (user.substr(0,5)=="admin"){
        trang_chu_admin(head);
        }
        else trang_chu_user(user,head);
        break;
    }
    case 2:{
        system("cls");
        DangKyTaiKhoan();
        break;
    }
    case 0:{
        system("cls");
        gotoXY(10, 10);
        cout << "Dang thoat chuong trinh...";
        Sleep(1000);
        exit(0);
        break;
    }
    default:
        gotoXY(22,19);
        cout << "Lua chon khong hop le!";
        Sleep(1000); // Cho người dùng đọc được lỗi, sau đó tự quay lại
        break;
    }}while (true);
}
int main() {
    Node* head = Head();
    read_file(head,"thuvien.txt"); // đọc vào thư 
    showIntro();
    system("cls");
    menuLoop(head);
    return 0;
}


