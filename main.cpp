#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "HangHoa.h"
#include "GioHang.h"
#include <algorithm>
#include <string> // Đã có sẵn, không cần thêm lại
#define PASSWORD 2

using namespace std;

// Khai báo các hàm cần thiết
void inDanhSachSanPham(Node* head);
void themSanPham(Node*& head, Node*& tail);
void xoaSanPham(Node*& head, Node*& tail);
void sua_san_pham(Node* head);
void swap(Hanghoa& a, Hanghoa& b);
void sapXepTheoGia(Node* head);
void sapXepTheoTen(Node* head);
void sapXep(Node* head);
void timKiemTheoMaSanPham(Node* head);
void timKiemTheoTen(Node* head);
void giaoDienTimKiem(Node* head);
void giaoDienChinhSua(Node*& head, Node*& tail);
void giaoDienThanhToan(Node* head, GioHang& quay_thanh_toan);
void giaoDienChinh(Node*& head, Node*& tail, GioHang& quay_thanh_toan);
void doc_file(Node*& head, Node*& tail);
void xuat_file(Node* head);

// Hiển thị danh sách sản phẩm
void inDanhSachSanPham(Node* head) {
    std::cout << "\n<-------Danh sach cac san pham dang bay ban: -------> \n"; // Thêm std::
    int index = 1;
    Node* current = head; // SỬA LỖI: Sử dụng con trỏ tạm thời
    while (current != nullptr) {
        std::cout << index++ << ". "; // Thêm std::
        current->data.xuat();
        current = current->next;
    }
}

// Thêm sản phẩm mới vào danh sách
void themSanPham(Node*& head, Node*& tail) {
    do {
        Hanghoa new_item;
        new_item.nhap_de_them_sp();
        new_item.setMasp("MDH" + string(4 - to_string(rand() % 10000).length(), '0') + to_string(rand() % 10000));

        Node* newNode = new Node(new_item);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        char lc;
        cout << "Ban co muon tiep tuc khong (y/n) ?";
        cin >> lc;
        if (lc != 'y') break;
    } while (true);
}

// Xóa sản phẩm khỏi danh sách
void xoaSanPham(Node*& head, Node*& tail) {
    do {
        string ma_sp_xoa;
        cout << "Nhap ma san pham can xoa (MDHxxxx): ";
        cin.ignore();
        getline(cin, ma_sp_xoa);
        transform(ma_sp_xoa.begin(), ma_sp_xoa.end(), ma_sp_xoa.begin(), ::toupper);

        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->data.layMaDonHang() == ma_sp_xoa) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                if (current == tail) {
                    tail = previous;
                }
                delete current;
                cout << "San pham da duoc xoa" << endl;
                break;
            }
            previous = current;
            current = current->next;
        }

        char lc;
        cout << "Ban co muon tiep tuc xoa khong (y/n) ?";
        cin >> lc;
        if (lc != 'y') break;
    } while (true);
}

// Sửa thông tin sản phẩm
void sua_san_pham(Node* head) {
    do {
        string masp;
        cout << "Nhap ma so cua san pham can sua (MDHxxxx):";
        cin.ignore();
        getline(cin, masp);
        transform(masp.begin(), masp.end(), masp.begin(), ::toupper);

        Node* current = head;
        while (current != nullptr) {
            if (current->data.layMaDonHang() == masp) {
                string ten;
                double gia;
                int soluong;
                cout << "Nhap thong tin san pham moi: ";
                cout << "\nNhap ten san pham moi: ";
                getline(cin, ten);
                cout << "Nhap gia thanh san pham moi: ";
                cin >> gia;
                cout << "Nhap so luong san pham: ";
                cin >> soluong;

                current->data.setTensp(ten);
                current->data.setGiasp(gia);
                current->data.setSoLuong(soluong);
                cout << "San pham da duoc sua." << endl;
                break;
            }
            current = current->next;
        }

        char lc;
        cout << "Ban co muon tiep tuc sua khong (y/n) ?";
        cin >> lc;
        if (lc != 'y') break;
    } while (true);
}

// Hoán đổi hai sản phẩm
void swap(Hanghoa& a, Hanghoa& b) {
    Hanghoa temp = a;
    a = b;
    b = temp;
}

// Sắp xếp sản phẩm theo giá
void sapXepTheoGia(Node* head) {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->data.layGiaThanh() > j->data.layGiaThanh()) {
                swap(i->data, j->data);
            }
        }
    }
}

// Sắp xếp sản phẩm theo tên
void sapXepTheoTen(Node* head) {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->data.layTenSanPham() > j->data.layTenSanPham()) {
                swap(i->data, j->data);
            }
        }
    }
}

// Menu sắp xếp sản phẩm
void sapXep(Node* head) {
    int luachon;
    cout << " __________________________________________________________________" << endl;
    cout << "|                              SAP XEP                             |" << endl;
    cout << "|__________________________________________________________________|" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|  1.  Sap xep theo gia                                            |" << endl;
    cout << "|  2.  Sap xep theo ten san pham                                   |" << endl;
    cout << "|  3.  Quay lai trang chu                                          |" << endl;
    cout << "|*________________________________________________________________*|" << endl;
    cout << " Nhap lua chon cua ban: ";
    cin >> luachon;
    switch (luachon) {
        case 1:
            sapXepTheoGia(head);
            break;
        case 2:
            sapXepTheoTen(head);
            break;
        case 3:
            break;
    }
}

// Tìm kiếm sản phẩm theo mã
void timKiemTheoMaSanPham(Node* head) {
    do {
        string ma_don_hang;
        bool isExist = false;
        cout << "Nhap ma don hang ban can tim kiem (MDHxxxx): ";
        cin.ignore();
        getline(cin, ma_don_hang);
        for (Node* current = head; current != nullptr; current = current->next) {
            if (current->data.layMaDonHang() == ma_don_hang) {
                current->data.xuat();
                isExist = true;
                break;
            }
        }
        if (!isExist) {
            cout << "Khong tim thay san pham voi ma da nhap\n";
        }
        char lc;
        cout << "Ban co muon tiep tuc tim khong (y/n) ?";
        cin >> lc;
        if (lc != 'y') break;
    } while (true);
}

// Tìm kiếm sản phẩm theo tên
void timKiemTheoTen(Node* head) {
    do {
        string ten_san_pham;
        bool isExist = false;
        cout << "Nhap ten san pham ban muon tim: ";
        cin.ignore();
        getline(cin, ten_san_pham);
        for (Node* current = head; current != nullptr; current = current->next) {
            if (current->data.layTenSanPham() == ten_san_pham) {
                current->data.xuat();
                isExist = true;
                break;
            }
        }
        if (!isExist) {
            cout << "Khong tim thay san pham voi ten da nhap\n";
        }
        char lc;
        cout << "Ban co muon tiep tuc tim khong (y/n) ?";
        cin >> lc;
        if (lc != 'y') break;
    } while (true);
}


// Đọc dữ liệu từ file
void doc_file(Node*& head, Node*& tail) {
    ifstream file("hanghoa.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file de doc du lieu!" << endl;
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

// Xuất dữ liệu ra file
void xuat_file(Node* head) {
    ofstream file("hoadon.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi du lieu!" << endl;
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

void giaoDienTimKiem(Node* head) {
    int choice_;

    cout << " __________________________________________________________________" << endl;
    cout << "|                             TIM KIEM                             |" << endl;
    cout << "|__________________________________________________________________|" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|  1.  Tim kiem theo ten                                           |" << endl;
    cout << "|  2.  Tim kiem theo ma san pham                                   |" << endl;
    cout << "|  3.  Quay lai trang chu                                          |" << endl;
    cout << "|*________________________________________________________________*|" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice_;

    switch (choice_) {
        case 1:
            timKiemTheoTen(head);
            break;
        case 2:
            timKiemTheoMaSanPham(head);
            break;
        case 3:
            break;
        default:
            cout << "Lua chon cua ban khong hop le!" << endl;
            break;
    }
}

void giaoDienChinhSua(Node*& head, Node*& tail) {
    int _choice;
    cout << " __________________________________________________________________" << endl;
    cout << "|                         QUYEN CHINH SUA                          |" << endl;
    cout << "|__________________________________________________________________|" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|  1.  Them san pham                                               |" << endl;
    cout << "|  2.  Xoa san pham                                                |" << endl;
    cout << "|  3.  Thay doi san pham                                           |" << endl;
    cout << "|  4.  Quay lai trang chu                                          |" << endl;
    cout << "|*________________________________________________________________*|" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> _choice;

    switch (_choice) {
        case 1:
            themSanPham(head, tail);
            break;
        case 2:
            xoaSanPham(head, tail);
            break;
        case 3:
            sua_san_pham(head);
            break;
        case 4:
            break;
        default:
            cout << "Khong co tinh nang da nhap!" << endl;
            break;
    }
}

void giaoDienThanhToan(Node* head, GioHang& quay_thanh_toan) {
    int choice_;
    double phanTram = 0;
    int STT_xoa = -1;
    int STT_them = -1;
    int so_luong = 1;

    quay_thanh_toan.inGioHang();
    cout << "\n";
    cout << " __________________________________________________________________" << endl;
    cout << "|                         THANH TOAN GIO HANG                      |" << endl;
    cout << "|__________________________________________________________________|" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|  1.  Them san pham                                               |" << endl;
    cout << "|  2.  Xoa san pham                                                |" << endl;
    cout << "|  3.  Thanh toan                                                  |" << endl;
    cout << "|  4.  Quay lai trang chu                                          |" << endl;
    cout << "|*________________________________________________________________*|" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice_;

    switch (choice_) {
        case 1:
            inDanhSachSanPham(head);
            std::cout << "\nBan muon them san pham so bao nhieu: "; // Thêm std::
            std::cin >> STT_them; // Thêm std::
            std::cout << "\nNhap so luong muon mua cua san pham vua chon: "; // Thêm std::
            std::cin >> so_luong; // Thêm std::
            {
                Node* current = head;
                for (int i = 1; i < STT_them && current != nullptr; ++i) {
                    current = current->next;
                }
                if (current != nullptr) { // SỬA LỖI: Kiểm tra nullptr
                    current->data.setSoLuong(so_luong);
                    quay_thanh_toan.themSanPham(current->data);
                } else {
                    std::cout << "So thu tu san pham khong hop le.\n"; // Thêm std::
                }
            }
            quay_thanh_toan.inGioHang();
            giaoDienThanhToan(head, quay_thanh_toan);
            break;
        case 2:
            quay_thanh_toan.inGioHang();
            cout << "\nBan muon xoa san pham so bao nhieu: ";
            cin >> STT_xoa;
            quay_thanh_toan.xoaSanPham(STT_xoa - 1);
            quay_thanh_toan.inGioHang();
            giaoDienThanhToan(head, quay_thanh_toan);
            break;
        case 3:
            cout << "\nNhap ti le giam gia: ";
            cin >> phanTram;
            quay_thanh_toan.apMaGiamGia(phanTram);
            quay_thanh_toan.thanhToan();
            break;
        case 4:
            break;
        default:
            cout << "Lua chon cua ban khong hop le!" << endl;
            break;
    }
}

void giaoDienChinh(Node*& head, Node*& tail, GioHang& quay_thanh_toan) {
    int choice;
    do {
        cout << " __________________________________________________________________" << endl;
        cout << "|                      QUAN LI CUA HANG MINI                       |" << endl;
        cout << "|__________________________________________________________________|" << endl;
        cout << "|                                                                  |" << endl;
        cout << "|  1.  Tim kiem san pham                                           |" << endl;
        cout << "|  2.  Xuat san pham trong kho                                     |" << endl;
        cout << "|  3.  Quyen chinh sua                                             |" << endl;
        cout << "|  4.  Thanh toan                                                  |" << endl;
        cout << "|  5.  Sap xep                                                     |" << endl;
        cout << "|  6.  In danh sach hien tai                                       |" << endl;
        cout << "|  7.  Thoat                                                       |" << endl;
        cout << "|*________________________________________________________________*|" << endl;
        cout << "                                                                    " << endl;
        cout << "Nhap lua chon cua ban [1-7]: ";
        cin >> choice;
        switch (choice) {
            case 1:
                giaoDienTimKiem(head);
                break;
            case 2:
                xuat_file(head);
                cout << "Xuat danh sach san pham thanh cong! \n";
                break;
            case 3: {
                int mat_khau;
                cout << "Nhap mat khau de truy cap: ";
                cin >> mat_khau;
                if (mat_khau == PASSWORD) {
                    giaoDienChinhSua(head, tail);
                } else {
                    cout << "Mat khau khong hop le!" << endl;
                }
                break;
            }
            case 4:
                giaoDienThanhToan(head, quay_thanh_toan);
                break;
            case 5:
                sapXep(head);
                cout << "Sap xep thanh cong! \n";
                break;
            case 6:
                cout << "Shop gui quy khach danh sach san pham hien co:\n";
                inDanhSachSanPham(head);
                break;
            case 7:
                cout << "Cam on ban da su dung chuong trinh!" << endl;
                exit(0);
            default:
                cout << "Lua chon cua ban chua hop le, vui long chon lai!" << endl;
                break;
        }
    } while (true);
}


int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    GioHang quay_thanh_toan;

    doc_file(head, tail);
    giaoDienChinh(head, tail, quay_thanh_toan);

    return 0;
}
