#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>
using namespace std;
// sửa giao diện chính có nút thoát
// Đang kí amin bị trùng nhưng vẫn được
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
    bool Trang_thai;
};

struct Node {
    Node* next;
    Book* sach;
};


// Khởi tạo 1 sách mới
Book* tao_sach(const string& ID, const string& ten, const string& tac_gia, const string& nxb,long namsx, bool trangthai) {
    Book* sach_moi = new Book;
    sach_moi->ID = ID;
    sach_moi->ten = ten;
    sach_moi->tac_gia = tac_gia;
    sach_moi->nxb = nxb;
    sach_moi->namsx = namsx;
    sach_moi->Trang_thai = trangthai;
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
// thiếu chèn sau một cuốn sách

// Thêm vào đầu danh sách
void pushhead(Node* head, Book* sach) {
    Node* new_node = khoitao_node(sach);
        new_node->next = head->next;
        head->next = new_node;
    }


// Thêm vào cuối danh sách
void pushend(Node* head, Book* sach) {
    Node* new_node = khoitao_node(sach);
    while(head->next!=NULL){
        head = head->next;
    }
    head->next = new_node;
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
    cout << "ten dang nhap hoac mat khau khong dung\n";
    fi.close();
    return "";
}   
//-----------------------Đăng Ký----------------------------------
void DangKyTaiKhoan(){
    fstream fi("user.txt",ios::in | ios :: out | ios :: app);
    bool kt=true;
    string TenDangNhap, Matkhau;
    while (kt){
        kt = false;
        cout <<"Nhap ten dang nhap :";
        cin >> TenDangNhap;
        cout << "Nhap mat khau :";
        cin >> Matkhau;

        fi.clear();
        fi.seekg(0, ios::beg);

        string line;
        while (getline(fi,line)){
            stringstream ss(line);
            string ten;
            getline(ss,ten,'|');
            if (ten==TenDangNhap && ten.substr(0,5)!="admin"){
                kt = true;
                cout << "Ten dang nhap ton tai.Hay nhap lai.";
            }
        }
    }
    fi.clear();
    fi.seekp(0, ios::end);
    fi << TenDangNhap <<"|"<< Matkhau <<"|" <<endl;
    fi.close();
    cout << "Dang ky thanh cong!";
}
// ----------------------Đọc từ ----------------------------------

void r_lib(Node* &head) {
    ifstream fi("thuvien.txt");
    if (!fi.is_open()) {
        cout << "Khong the mo file\n";
        return;
    }

    string line;
    while (getline(fi, line)) {
        stringstream ss(line);
        string ID, ten, tac_gia, nxb, namsx_str, sl_str;

        getline(ss, ID, '|');
        getline(ss, ten, '|');
        getline(ss, tac_gia, '|');
        getline(ss, nxb, '|');
        getline(ss, namsx_str, '|');
        getline(ss, sl_str, '|');

        long namsx = stol(namsx_str);
        bool Trang_thai;
        if (sl_str == "Da muon") Trang_thai= false;
        else Trang_thai = true;

        Book* sach = tao_sach(ID, ten, tac_gia, nxb, namsx, Trang_thai);
        pushend(head, sach);
    }

    fi.close();
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
// --------------------------- Xoa ----------------------------------
bool DelByID(Node *head, string ID){
   
    while(head->next!=NULL && Vietthuong(head->next->sach->ID) != Vietthuong(ID)){
        head = head->next;
    }
    if (head->next!=NULL){
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        return true;
    }
    return false;

}
 bool DelByTenSach(Node *head, string ten){
   
    while(head->next!=NULL && Vietthuong(head->next->sach->ten) != Vietthuong(ten)){
        head = head->next;
    }
    if (head->next!=NULL){
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        return true;
    }
    return false;

}

bool DelByTacGia(Node *head, string tg){
    bool check = false;
while(head->next!=NULL){
    if (Vietthuong(head->next->sach->tac_gia) == Vietthuong(tg)){
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        check = true;
    }
    else{
        head = head->next;
    }
    
    }
    return check;
}

void XoaDau(Node *head){
    Node *temp = head->next;
    head->next = head->next->next;
    delete temp->sach;
    delete temp;
}

bool XoaSauMa(Node *head,string ID){
    head = head->next;
    while(head!=NULL && head->next!=NULL && Vietthuong(head->sach->ID) != Vietthuong(ID)){
        head = head->next;
    }
    if (head !=NULL && head->next!=NULL){ // node hiện tại và phía sau đều tồn tại
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
        return true;
    }
    return false;
}

void XoaCuoi(Node *head){
   if (head->next==NULL) return;

   Node *prev = head;
   Node *temp = head->next;

   while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
   }
   prev->next = NULL;
   delete temp->sach;
   delete temp;
   
}

//-----------------------------In ra màn hình---------------------------------------------
// In ra tất cả sách
void print_lib(Node* head) {
    head = head->next;
    while (head != nullptr) {
        cout << "ID: " << head->sach->ID
             << "\nTen: " << head->sach->ten
             << "\nTac gia: " << head->sach->tac_gia
             << "\nNXB: " << head->sach->nxb
             << "\nNam san xuat: " << head->sach->namsx;
        if (head->sach->Trang_thai) cout << "\nTrang thai: chua muon\n\n";
        else cout <<"\n Trang thai: da muon\n";
        head = head->next;
    }
}

void showtt(Node *head){
     cout << "ID: " << head->sach->ID
             << "\nTen: " << head->sach->ten
             << "\nTac gia: " << head->sach->tac_gia
             << "\nNXB: " << head->sach->nxb
             << "\nNam san xuat: " << head->sach->namsx;
        if (head->sach->Trang_thai) cout << "\nTrang thai: chua muon\n\n";
        else cout <<"\n Trang thai: da muon\n";
}
//-----------------------Tìm Kiếm---------------------
Book** FindbyID(Node *head,string ID){
    Node *DS = Head();
    head = head->next;
    string t = Vietthuong(ID);
    while(head!=NULL){
        if (Vietthuong(head->sach->ID) == t){
            return &(head->sach);
        }
        head = head->next;
    }
    cout << "Khong co sach ID: " << ID << endl;
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
           << b->namsx << "|";
        if (b->Trang_thai) fo << "chua muon|"<<endl;
        else fo<<"da muon|"<<endl;
        temp = temp->next;
    }
    cout << "Luu thanh cong\n";
    fo.close();
}

// ------------------------------- Các thao tác -----------------------------


void them_sach(Node *head){
    
    string ID,tensach, tacgia,NXB;
    long namsx ,sluong;
    cout << "Nhap ID : " ; getline(cin,ID);
    cout << "Nhap ten sach : " ; getline(cin,tensach);
    cout << "Nhap ten tac gia : " ; getline(cin,tacgia);
    cout << "Nhap Nha xuat ban : "; getline(cin,NXB);
    cout << "Nhap Nam San Xuat : "; cin >> namsx;
    cout << "Nhap So Luong : "; cin >> sluong;
    Book *C = tao_sach(ID,tensach,tacgia,NXB,namsx,sluong);
    cout << "1.Them vao dau\n"
         << "2.Them vao cuoi\n";
    int tt;cout << "Nhap thao tac: "; cin >> tt;
    while(tt!=1 && tt!=2){
        cout << "Thao tac khong hop le\n";
        cout << "Nhap lai thao tac :"  ; cin >> tt;
    }
    if (tt==1){
        pushhead(head,C);
        cout << "Da them thanh cong\n";
    }
    else if (tt==2){
        pushend(head,C);
        cout << "Da them thanh cong\n";
    }
}
void xoa_sach(Node *head){
    cout << "1.Theo Ma So\n"
         << "2.Theo Ten Sach\n"
         << "3.Theo Ten Tac Gia\n"
         << "4.Xoa sach dau danh sach\n"
         << "5.Xoa sach sau ma so\n"
         << "6.Xoa cuoi danh sach\n";
      int tt;cout << "Nhap thao tac: "; cin >> tt;
    while(tt!=1 && tt!=2 && tt!=3 && tt!=4 && tt!=5 && tt!=6){
        cout << "Thao tac khong hop le\n";
        cout << "Nhap lai thao tac :"  ; cin >> tt;
    }
    cin.ignore();
    if (tt==1){
        string ID ; cout << "Nhap ma so : ";getline(cin,ID);
        if (DelByID(head,ID)) cout << "Xoa thanh cong\n";
        else cout << "Khong tim thay\n";
    }
    else if (tt==2){
        string ts ; cout << "Nhap ten sach : ";getline(cin,ts);
        if (DelByTenSach(head,ts))cout << "Xoa thanh cong\n";
        else cout << "Khong tim thay\n";
    }
    else if (tt==3){
        string tg; cout << "Nhap ten tac gia : ";getline(cin,tg);
        if(DelByTacGia(head,tg))cout << "Xoa thanh cong\n";
        else cout << "Khong tim thay\n";
    }
    else if (tt==4){
        XoaDau(head);
        cout << "Xoa thanh cong\n";
    }
    else if (tt==5){
       string ID ; cout << "Nhap ma so : ";getline(cin,ID);
       if( XoaSauMa(head,ID)) cout << "Xoa thanh cong\n";
        else cout << "Khong tim thay\n";
    }
    else if (tt==6){
        XoaCuoi(head);
        cout << "Xoa thanh cong\n";
    }
}

void Tim_sach(Node *head){
    cout << "1.Theo ten sach\n"
         << "2.Theo ten tac gia\n"
         << "3.Theo ten Nha xuat ban\n"
         << "4.Sach chua muon\n";
    int tt;cout << "Nhap thao tac: "; cin >> tt;
    while(tt!=1 && tt!=2 && tt!=3 && tt!= 4){
        cout << "Thao tac khong hop le\n";
        cout << "Nhap lai thao tac :"  ; cin >> tt;
    }
    cin.ignore();
    if (tt==1){
        cout << "Nhap ten sach : ";
        string tensach ; getline(cin,tensach);
        cout << "------------Danh sach liet ke --------------------\n";
        Node* ds = FindbyTenSach(head,tensach);
        print_lib(ds);
        delete ds;
    }
    else if (tt==2){
        // cin.ignore();
        cout << "Nhap ten tac gia : ";
        string tg ; getline(cin,tg);
        cout << "------------Danh sach liet ke --------------------\n";
        Node* ds = FindbyTacGia(head,tg);
        print_lib(ds);
        delete ds;
    }
    else if (tt==3){
        // cin.ignore();
        cout << "Nhap ten NXB : ";
        string nxb ; getline(cin,nxb);
        cout << "------------Danh sach liet ke --------------------\n";
        Node* ds = FindbyNXB(head,nxb);
        print_lib(ds);
        delete ds;
    }
    else if (tt == 4){
        Node* ds =FindChuaMuon(head);
        cout << "------------Danh sach liet ke --------------------\n";
        print_lib(ds);
        delete ds;
    }
}

void Sua_sach(Node *head){
    head = head->next;
    cout << "Nhap ID sach can sua : ";
    string ID; getline(cin,ID);
    while(head!=NULL && head->sach->ID != ID){
        head = head->next;
    }
    if (head == NULL) {
        cout << "Khong tim thay\n";
     return;
 }
    bool check = true;
    while(check){
    cout << "1.Sua ID\n"
         << "2.Sua Ten Sach\n"
         << "3.Sua Tac Gia\n"
         << "4.Sua NXB\n"
         << "5.Sua Nam SX\n"
         << "6.Sua trang thai\n"
         << "7.Thoat\n";
    int tt; cout << "Nhap thao tac : "; cin >> tt;
    cin.ignore();
    if (tt==7) check = false;
    else if (tt==1){
        string id; cout << "Nhap ID sua : "; getline(cin,id);
        head->sach->ID = id;
        cout << "Sua doi thanh cong!\n";
    }
    else if (tt==2){
        string ten; cout << "Nhap ten sach : "; getline(cin,ten);
        head->sach->ten = ten;
        cout << "Sua doi thanh cong!\n";
    }
    else if (tt==3){
        string tg; cout << "Nhap ten tac gia : "; getline(cin,tg);
        head->sach->tac_gia = tg;
        cout << "Sua doi thanh cong!\n";
    }
    else if (tt==4){
        string nxb; cout << "Nhap NXB : "; getline(cin,nxb);
        head->sach->nxb = nxb;
        cout << "Sua doi thanh cong!\n";
    }
   else if (tt==5){
        long sx; cout << "Nhap nam san xuat : "; cin >> sx;
        head->sach->namsx = sx;
        cout << "Sua doi thanh cong!\n";
    }
    else if (tt==6){
         bool tthai;cout << "Chinh sua trang thai thanh : \n1.Chua muon\n2.Da muon\n Nhap thao tac : ";
        int tt2 ; cin >> tt2;
        if (tt2==1) {
            tthai = true;
            cout << "Sua doi thanh cong!\n";
        }
         else if  (tt2==2) {tthai = false;
            cout << "Sua doi thanh cong!\n";
        }
        else cout << "Du lieu khong hop le\n";
        head->sach->Trang_thai = tthai;
    }
    else {
        cout << "Du lieu khong hop le ! \n";
    }

    }

}

void xem_sach(Node *head){ // thieu
    cout << "1.Xem toan bo danh sach\n"
         << "2.Xem theo thu tu\n";
     int tt;cout << "Nhap thao tac: "; cin >> tt;
    while(tt!=1 && tt!=2 ){
        cout << "Thao tac khong hop le\n";
        cout << "Nhap lai thao tac :"  ; cin >> tt;
    }
    if (tt==1){
        print_lib(head);
    }
    else if (tt==2){
        cout << "1.Theo ten sach\n"
             << "2.Theo ten tac gia\n"
             << "3.Theo ten NXB \n"
             << "4.Moi duoc xuat ban\n";
         int tt2;cout << "Nhap thao tac: "; cin >> tt2;
        while(tt2!=1 && tt2!=2 && tt2!=3 && tt2!=4){
            cout << "Thao tac khong hop le\n";
            cout << "Nhap lai thao tac :"  ; cin >> tt;
        }
            if (tt2==1){
                SapXepTheoTenSach(head);
            }
            else if (tt2==2){
                SapXepTheoTenTacGia(head);}
            else if (tt2==3){
                SapXepTheoNXB(head);
            }
            else SapXepTheoNamSX(head);
        cout << "\n ---------------Danh sach--------------------------\n";
        print_lib(head);
    }
}

void LuuVaoFile(Node *head){
    cout << "Nhap ten file de luu : ";
    string file_name;
    getline(cin,file_name);
    save_to_file(head,file_name);
}
void trang_chu_admin(Node *head){
    bool cnt = true;
     while(cnt){
        cout << "\n\n --------- Quan ly thu vien ---------------\n";
        cout << "1.Them sach vao danh sach\n"
             << "2.Xoa sach\n"
             << "3.Tim kiem sach\n"
             << "4.Xem sach\n"
             << "6.Sua noi dung sach\n"
             << "7.Luu vao file\n"
             << "8.Thoat\n";
        int tt; cout << "Nhap thao tac : ";cin >> tt;
        cin.ignore();
        if (tt==1){
           them_sach(head);
        }
        if (tt==2){
            xoa_sach(head);
        }
        if (tt==3){
            Tim_sach(head);
        }
        if (tt==4){
            xem_sach(head);
        }
        if (tt==6){
            Sua_sach(head);
        }
        if (tt==7){
            LuuVaoFile(head);
        }
        if (tt==8) cnt = false;
    }
    save_to_file(head,"thuvien.txt");
}
//----------------Mượn sách -----------------
void MuonSach(const string& Ten,Node *head){
    string temp = Ten;
    string ID;
    cout << "Nhap ID sach can muon: ";
    cin >> ID;
    Book** sach = FindbyID(head,ID);
    if (sach == NULL) return;
    if (!(*sach)->Trang_thai){
        cout <<" Sach da duoc muon";
        return;
    }
    temp += ".txt";
    ofstream fo(temp,ios::app);
    time_t now = time(0);
    string dt = ctime(&now);
    dt.pop_back();// xoa dau \n o cuoi
    (*sach)->Trang_thai = false; // Đã sửa và đã thành   
    fo  << (*sach)->ID << "|"
        << (*sach)->ten << "|"
        << (*sach)->tac_gia << "|"
        << dt << "|" << endl;
    cout << "Muon sach thanh cong\n";
}
void TraSach(const string& ten){
    string temp = ten;
    string ID;
    cout << "Nhap ID sach can muon:";
    cin >> ID;
    temp += ".txt";
    bool kt = false;
    ifstream fi(temp);
    vector <string> lines;
    string line;
    int SLDong = 1;
    while(getline(fi,line)){
        string id;
        stringstream ss(line);
        getline(ss,id,'|');
        if (id!=ID){
            lines.push_back(line);
        }
        else kt = true;
        SLDong++;
    }
    if (!kt){
        cout << "Loi tra sach!";
        return;
    }
    fi.close();
    ofstream fo(temp,ios::trunc);
    for (const auto&dong :lines){
        fo <<dong<<endl;
    }
    fo.close();
    cout << "Tra sach thanh cong";

}
//---------------in sach da muon-------------
void print_user(const string &ten){
    string temp = ten;
    temp += ".txt";
    ifstream fi (temp);   
    string line;
    int i =1;
    while (getline(fi,line)){
        string ID,ten,tacgia,ThoiGian;
        stringstream ss(line);
        getline(ss,ID,'|');
        getline(ss,ten,'|');
        getline(ss,tacgia,'|');
        getline(ss,ThoiGian,'|');
        cout << "Sach: " << i <<endl
                <<"ID: " << ID <<endl
                <<"Ten: "<< ten<<endl
                <<"Tac Gia: "<<tacgia<<endl
                <<"Thoi gian muon: "<<ThoiGian<<endl;
        i++;
    }
    fi.close();
}
void trang_chu_user(const string& TenDangNhap, Node *head){
    bool cnt = true;
     while(cnt){
        cout << "\n\n --------- Thu vien ---------------\n";
        cout << "1.Tim kiem sach\n"
             << "2.Xem sach da muon\n"
             << "3.Muon sach\n"
             << "4.Tra sach\n"
             << "5.Thoat\n";
        int tt; cout << "Nhap thao tac : ";cin >> tt;
        cin.ignore();
        if (tt==1){
           Tim_sach(head);
        }
        if (tt==2){
            print_user(TenDangNhap);
        }
        if (tt==3){
            MuonSach(TenDangNhap,head);
        }
        if (tt==4){
            TraSach(TenDangNhap);
        }
        if (tt==5) cnt = false;
    }

}


//--------------đăng nhập--------------
string dangnhap(){
    string TenDangNhap;
    string MatKhau;
    for (int i=3; i>0;i--){
        cout << "Nhap ten dang nhap: "; cin >> TenDangNhap;
        cout << "Nhap mat khau: "; cin >> MatKhau;
        string s = KiemTraDangNhap(TenDangNhap,MatKhau);
        if (s=="") cout << "Ban con " << i-1<<"lan dang nhap";
        else break;
    }
    return TenDangNhap;
}
int main() {
    Node* head = Head();
    r_lib(head);
    cout << "1. Dang nhap\n"
        << "2. Dang Ki\n";
    int tt; cout <<"Nhap thao tac : "; cin >> tt;
    while (tt!=1&&tt!=2){
        cout <<"Thao tac khong hop le!"<< endl;
        cout <<"Nhap lai thao tac"; cin >> tt;
    }
    if (tt==1){
        string TK = dangnhap();
        if (TK.substr(0,5)=="admin"){
            trang_chu_admin(head);
        }
        else trang_chu_user(TK,head);
    }
    else DangKyTaiKhoan();
    //  save_to_file(head,"thuvien.txt"); // lưu lại DLSK đã sửa vào file
    // Giải phóng bộ nhớ
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp->sach;
        delete temp;
    }

    return 0;
}


