#pragma once
#include "HangHoa.h"

class Node {
public:
    Hanghoa data;
    Node* next;

    Node(Hanghoa sanPham) : data(sanPham), next(nullptr) {}
};

class GioHang {
private:
    Node* head;               // Con trỏ đầu danh sách liên kết
    Node* tail;               // Con trỏ cuối danh sách liên kết
    double tienThanhToan;
    int soLuongHang;
    double phanTramGiamGia;

    void capNhatTienThanhToan(); // Cập nhật tiền khi thêm hoặc xóa sản phẩm

public:
    GioHang();
    void themSanPham(Hanghoa sanPham);
    void xoaSanPham(int index);
    void inGioHang();
    void apMaGiamGia(double phanTram);
    void thanhToan();

    double layTienThanhToan();
    int laySoLuongHang();
    double layPhanTramGiamGia();

    ~GioHang();
};
