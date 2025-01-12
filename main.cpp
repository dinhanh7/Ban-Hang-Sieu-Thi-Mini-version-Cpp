#include "HangHoa.h"
#include "GioHang.h"
#include "HangHoa.cpp"
#include "GioHang.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// In danh sach san pham
void inDanhSachSanPham(Node* head) {
    Node* current = head;
    cout << "\n<-------Danh sach cac san pham dang bay ban: ------->\n";
    int index = 1;
    while (current != nullptr) {
        cout << index++ << ". ";
        current->data.xuat();
        current = current->next;
    }
}

// Them san pham
void themSanPham(Node*& head, Node*& tail) {
    Hanghoa new_item;
    new_item.nhap_de_them_sp();
    new_item.setMasp("MDH" + to_string(rand() % 10000));

    Node* newNode = new Node(new_item);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Xoa san pham
void xoaSanPham(Node*& head, Node*& tail, const string& ma_sp) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.layMaDonHang() == ma_sp) {
            if (previous == nullptr) { // Xoa dau
                head = current->next;
            } else {
                previous->next = current->next;
            }
            if (current == tail) { // Xoa cuoi
                tail = previous;
            }
            delete current;
            cout << "San pham da duoc xoa." << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "Khong tim thay san pham voi ma da nhap." << endl;
}

// Sua san pham
void sua_san_pham(Node* head, const string& ma_sp) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.layMaDonHang() == ma_sp) {
            string ten;
            double gia;
            int soluong;

            cout << "Nhap ten san pham moi: ";
            cin.ignore();
            getline(cin, ten);

            cout << "Nhap gia thanh san pham moi: ";
            cin >> gia;

            cout << "Nhap so luong san pham moi: ";
            cin >> soluong;

            current->data.setTensp(ten);
            current->data.setGiasp(gia);
            current->data.setSoLuong(soluong);

            cout << "San pham da duoc sua." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Khong tim thay san pham voi ma da nhap." << endl;
}

// Swap data giữa hai node
void swap(Node* a, Node* b) {
    Hanghoa temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Sap xep theo gia
void sapXepTheoGia(Node* head) {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->data.layGiaThanh() > j->data.layGiaThanh()) {
                swap(i, j);
            }
        }
    }
}

// Sap xep theo ma san pham
void sapXepTheoMaSanPham(Node* head) {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->data.layMaDonHang() > j->data.layMaDonHang()) {
                swap(i, j);
            }
        }
    }
}

// Sap xep theo ten
void sapXepTheoTen(Node* head) {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->data.layTenSanPham() > j->data.layTenSanPham()) {
                swap(i, j);
            }
        }
    }
}

// Sap xep
void sapXep(Node* head, int luaChon) {
    switch (luaChon) {
        case 1:
            sapXepTheoGia(head);
            break;
        case 2:
            sapXepTheoMaSanPham(head);
            break;
        case 3:
            sapXepTheoTen(head);
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
    }
}

// Tim kiem theo ma san pham
void timKiemTheoMaSanPham(Node* head, const string& ma_sp) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.layMaDonHang() == ma_sp) {
            current->data.xuat();
            return;
        }
        current = current->next;
    }
    cout << "Khong tim thay san pham voi ma da nhap." << endl;
}

// Tim kiem theo ten
void timKiemTheoTen(Node* head, const string& ten_sp) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.layTenSanPham() == ten_sp) {
            current->data.xuat();
            return;
        }
        current = current->next;
    }
    cout << "Khong tim thay san pham voi ten da nhap." << endl;
}

// Giao dien tim kiem
void giaoDienTimKiem(Node* head) {
    int luaChon;
    cout << "\n1. Tim kiem theo ma san pham";
    cout << "\n2. Tim kiem theo ten san pham";
    cout << "\nNhap lua chon: ";
    cin >> luaChon;

    if (luaChon == 1) {
        string ma_sp;
        cout << "Nhap ma san pham: ";
        cin.ignore();
        getline(cin, ma_sp);
        timKiemTheoMaSanPham(head, ma_sp);
    } else if (luaChon == 2) {
        string ten_sp;
        cout << "Nhap ten san pham: ";
        cin.ignore();
        getline(cin, ten_sp);
        timKiemTheoTen(head, ten_sp);
    } else {
        cout << "Lua chon khong hop le." << endl;
    }
}

// Doc file
void doc_file(Node*& head, Node*& tail, const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string ma, ten;
        double gia;
        int soluong;

        getline(iss, ma, ',');
        getline(iss, ten, ',');
        iss >> gia;
        iss.ignore();
        iss >> soluong;

        Hanghoa sp(ten, ma, gia, soluong);
        Node* newNode = new Node(sp);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    file.close();
}

// Xuat file
void xuat_file(Node* head, const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        file << current->data.layMaDonHang() << "," << current->data.layTenSanPham()
             << "," << current->data.layGiaThanh() << "," << current->data.laySoLuong() << endl;
        current = current->next;
    }
    file.close();
}

// Main
int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    doc_file(head, tail, "hanghoa.txt");

    int luaChon;
    do {
        cout << "\n1. Xem danh sach san pham";
        cout << "\n2. Them san pham";
        cout << "\n3. Xoa san pham";
        cout << "\n4. Sua san pham";
        cout << "\n5. Sap xep san pham";
        cout << "\n6. Tim kiem san pham";
        cout << "\n7. Xuat danh sach ra file";
        cout << "\n8. Thoat";
        cout << "\nNhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                inDanhSachSanPham(head);
                break;
            case 2:
                themSanPham(head, tail);
                break;
            case 3: {
                string ma_sp;
                cout << "Nhap ma san pham can xoa: ";
                cin.ignore();
                getline(cin, ma_sp);
                xoaSanPham(head, tail, ma_sp);
                break;
            }
            case 4: {
                string ma_sp;
                cout << "Nhap ma san pham can sua: ";
                cin.ignore();
                getline(cin, ma_sp);
                sua_san_pham(head, ma_sp);
                break;
            }
            case 5: {
                int loaiSapXep;
                cout << "\n1. Sap xep theo gia";
                cout << "\n2. Sap xep theo ma san pham";
                cout << "\n3. Sap xep theo ten";
                cout << "\nNhap lua chon: ";
                cin >> loaiSapXep;
                sapXep(head, loaiSapXep);
                break;
            }
            case 6:
                giaoDienTimKiem(head);
                break;
            case 7:
                xuat_file(head, "hoadon.txt");
                break;
            case 8:
                cout << "Thoat chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
        }
    } while (luaChon != 8);

    return 0;
}
