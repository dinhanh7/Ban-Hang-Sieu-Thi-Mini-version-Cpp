#include "GioHang.h"
#include <iostream>
using namespace std;

GioHang::GioHang() : head(nullptr), tail(nullptr), tienThanhToan(0), soLuongHang(0), phanTramGiamGia(0) {}

void GioHang::capNhatTienThanhToan() {
    tienThanhToan = 0;
    Node* current = head;
    while (current != nullptr) {
        tienThanhToan += current->data.layGiaThanh() * current->data.laySoLuong();
        current = current->next;
    }
}

void GioHang::themSanPham(Hanghoa sanPham) {
    Node* newNode = new Node(sanPham);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    soLuongHang++;
    capNhatTienThanhToan();
}

void GioHang::xoaSanPham(int index) {
    if (index < 0 || index >= soLuongHang) {
        cout << "Chi so khong hop le!" << endl;
        return;
    }
    Node* current = head;
    Node* previous = nullptr;

    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    if (previous == nullptr) { // Xóa đầu
        head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current == tail) { // Xóa cuối
        tail = previous;
        if (tail == nullptr) { // Sửa lỗi rò rỉ bộ nhớ: Xử lý trường hợp danh sách chỉ có 1 phần tử
            head = nullptr;
        }
    }

    delete current;
    soLuongHang--;
    capNhatTienThanhToan();
}

void GioHang::inGioHang() {
    cout << "\n<------------------Gio hang cua ban---------------->";
    Node* current = head;
    int index = 1;
    while (current != nullptr) {
        cout << "\n" << index++ << ". ";
        current->data.xuat();
        current = current->next;
    }
}

double GioHang::layTienThanhToan() const { // Thêm const
    return tienThanhToan;
}

int GioHang::laySoLuongHang() const { // Thêm const
    return soLuongHang;
}

double GioHang::layPhanTramGiamGia() const { // Thêm const
    return phanTramGiamGia;
}

void GioHang::apMaGiamGia(double phanTram) {
    phanTramGiamGia = phanTram;
    capNhatTienThanhToan(); // Tính lại tổng tiền TRƯỚC khi áp dụng giảm giá
    tienThanhToan *= (1 - phanTram / 100); // Sau đó mới áp dụng giảm giá
}

void GioHang::thanhToan() {
    inGioHang();
    cout << "\nSo tien phai tra la: " << layTienThanhToan() << " VND\n";
}

GioHang::~GioHang() {
    Node* current = head;
    while (current != nullptr) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}