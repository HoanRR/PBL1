#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Book {
    string ID;
    string ten;
    string tac_gia;
    string nxb;
    long namsx;
    long sl;
};

struct Node {
    Node* next;
    Book* sach;
};

// Khởi tạo 1 sách mới
Book* tao_sach(const string& ID, const string& ten, const string& tac_gia, const string& nxb, long namsx, long sl) {
    Book* sach_moi = new Book;
    sach_moi->ID = ID;
    sach_moi->ten = ten;
    sach_moi->tac_gia = tac_gia;
    sach_moi->nxb = nxb;
    sach_moi->namsx = namsx;
    sach_moi->sl = sl;
    return sach_moi;
}

// In ra tất cả sách
void print_lib(Node* head) {
    head = head->next;
    while (head != nullptr) {
        cout << "ID: " << head->sach->ID
             << "\nTen: " << head->sach->ten
             << "\nTac gia: " << head->sach->tac_gia
             << "\nNXB: " << head->sach->nxb
             << "\nNam san xuat: " << head->sach->namsx
             << "\nSo luong: " << head->sach->sl << "\n\n";
        head = head->next;
    }
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


//-----------------------------Liet ke---------------------------------------------
void showtt(Node *head){
     cout << "ID: " << head->sach->ID
             << "\nTen: " << head->sach->ten
             << "\nTac gia: " << head->sach->tac_gia
             << "\nNXB: " << head->sach->nxb
             << "\nNam san xuat: " << head->sach->namsx
             << "\nSo luong: " << head->sach->sl << "\n\n";
}
string Vietthuong(string c){
    transform(c.begin(),c.end(),c.begin(),::tolower);
    return c;
}
void LietKebyTenSach(Node *head,string tensach){
    head = head->next;
    string t = Vietthuong(tensach);
    while(head!=NULL){
        if (Vietthuong(head->sach->ten) == t){
            showtt(head);
        }
        head = head->next;
    }
}

void LietKebyTacGia(Node *head,string tg){
    head = head->next;
    string t = Vietthuong(tg);
    while(head!=NULL){
        if (Vietthuong(head->sach->tac_gia) == t){
            showtt(head);
        }
        head = head->next;
    }
}
void LietKebyNXB(Node *head,string NXB){
    head = head->next;
    string t = Vietthuong(NXB);
    while(head!=NULL){
        if (Vietthuong(head->sach->nxb) == t){
            showtt(head);
        }
        head = head->next;
    }
}


// ---------------------------- Sap xep-----------------------------

void SapXepTheoTenSach(Node *head){ // tăng dần 
    head = head -> next;
    for (Node *i = head;i!=NULL;i=i->next){
        Node *minNode = i;
        for (Node * j = i->next ; j!=NULL;j=j->next){
            if (j->sach->ten < i->sach->ten){
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
            if (j->sach->tac_gia < i->sach->tac_gia){
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
            if (j->sach->nxb < i->sach->nxb){
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
            if (j->sach->namsx < i->sach->namsx){
                minNode = j;
            }
        }
        swap(i->sach,minNode->sach);
    }
}
// --------------------------- Xoa ----------------------------------
void DelByID(Node *head, string ID){
   
    while(head->next!=NULL && head->next->sach->ID != ID){
        head = head->next;
    }
    if (head->next!=NULL){
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
    }

}
 void DelByTenSach(Node *head, string ten){
   
    while(head->next!=NULL && head->next->sach->ten != ten){
        head = head->next;
    }
    if (head->next!=NULL){
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
    }

}

void DelByTacGia(Node *head, string tg){
   
while(head->next!=NULL){
    if (head->next->sach->tac_gia == tg){
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
    }
    else{
        head = head->next;
    }
    
    }

}

void XoaDau(Node *head){
    Node *temp = head->next;
    head->next = head->next->next;
    delete temp->sach;
    delete temp;
}

void XoaSauMa(Node *head,string ID){
    head = head->next;
    while(head!=NULL && head->next!=NULL && head->sach->ID != ID){
        head = head->next;
    }
    if (head !=NULL && head->next!=NULL){ // node hiện tại và phía sau đều tồn tại
        Node *temp = head->next;
        head->next = head->next->next;
        delete temp->sach;
        delete temp;
    }

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
        long sl = stol(sl_str);

        Book* sach = tao_sach(ID, ten, tac_gia, nxb, namsx, sl);
        pushend(head, sach);
    }

    fi.close();
}

// ------------------------lưu lại danh sách liên kết vào file
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
           << b->sl << "|" << endl;
        temp = temp->next;
    }
    fo.close();
}

// -------------Node giả------------
Node *Head(){
    Node *head = new Node;
    head->next = NULL;
    head->sach = NULL;
    return head;
}


// ------------------------------- Các thao tác -----------------------------

void tt1(Node *head){
    
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

void tt4(Node *head){
    cout << "1.Theo ten sach\n"
         << "2.Theo ten tac gia\n"
         << "3.Theo ten Nha xuat ban\n";
    int tt;cout << "Nhap thao tac: "; cin >> tt;
    while(tt!=1 && tt!=2 && tt!=3){
        cout << "Thao tac khong hop le\n";
        cout << "Nhap lai thao tac :"  ; cin >> tt;
    }
    cin.ignore();
    if (tt==1){
        cout << "Nhap ten sach : ";
        string tensach ; getline(cin,tensach);
        cout << "------------Danh sach liet ke --------------------\n";
        LietKebyTenSach(head,tensach);
    }
    else if (tt==2){
        // cin.ignore();
        cout << "Nhap ten tac gia : ";
        string tg ; getline(cin,tg);
        cout << "------------Danh sach liet ke --------------------\n";
        LietKebyTacGia(head,tg);
    }
    else if (tt==3){
        // cin.ignore();
        cout << "Nhap ten NXB : ";
        string nxb ; getline(cin,nxb);
        cout << "------------Danh sach liet ke --------------------\n";
        LietKebyNXB(head,nxb);
    }
}

int main() {
    Node* head = Head();
    r_lib(head);
    bool cnt = true;
    while(cnt){
        cout << "\n\n --------- Quan ly thu vien ---------------\n";
        cout << "1.Them sach vao danh sach\n"
             << "2.Xoa mot cuon sach khoi danh sach\n"
             << "3.Xoa sach\n"
             << "4.Tim kiem sach\n"
             << "5.Xem sach\n"
             << "6.Exit\n";
        int tt; cout << "Nhap thao tac : ";cin >> tt;
        cin.ignore();
        if (tt==1){
           tt1(head);
        }
        if (tt==3){
            
        }
        if (tt==4){
            tt4(head);
        }
        if (tt==5){
            print_lib(head);
        }
        if (tt==6) cnt = false;
    }

    save_to_file(head,"thuvien.txt"); // lưu lại DLSK đã sửa vào file
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


