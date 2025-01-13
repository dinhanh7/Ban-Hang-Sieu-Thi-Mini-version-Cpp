#pragma once
#include "HangHoa.h"



class GioHang {
private:
    Node* head;         // Con trỏ đầu danh sách liên kết
    Node* tail;         // Con trỏ cuối danh sách liên kết
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

    double layTienThanhToan() const; // Thêm const
    int laySoLuongHang() const; // Thêm const
    double layPhanTramGiamGia() const; // Thêm const

    ~GioHang();
};