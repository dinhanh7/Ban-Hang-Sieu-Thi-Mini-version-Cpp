#pragma once
#include <string>
#include <iostream>
using namespace std;

class Hanghoa {
private:
    string san_pham;
    string ma_san_pham;
    double gia_thanh;
    int so_luong;

public:
    Hanghoa();
    Hanghoa(string, string, double);
    Hanghoa(string, string, double, int);

    void nhap();
    void nhap_de_them_sp();
    void xuat();
    void setTensp(string tensp);
    void setMasp(string ma);
    void setGiasp(double gia);
    void setSoLuong(int soLuong);

    string layMaDonHang();
    string layTenSanPham();
    double layGiaThanh();
    int laySoLuong();

    Hanghoa operator=(const Hanghoa& other);
    bool operator>(const Hanghoa& other);
};
class Node {
public:
    Hanghoa data;
    Node* next;

    Node(Hanghoa sanPham) : data(sanPham), next(nullptr) {}
};
