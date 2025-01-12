#include "HangHoa.h"

Hanghoa::Hanghoa() : san_pham(""), ma_san_pham(""), gia_thanh(0), so_luong(0) {}

Hanghoa::Hanghoa(string sanPham, string maSanPham, double giaThanh)
    : san_pham(sanPham), ma_san_pham(maSanPham), gia_thanh(giaThanh), so_luong(0) {}

Hanghoa::Hanghoa(string sanPham, string maSanPham, double giaThanh, int soLuong)
    : san_pham(sanPham), ma_san_pham(maSanPham), gia_thanh(giaThanh), so_luong(soLuong) {}

void Hanghoa::nhap() {
    cout << "Nhap ten san pham: ";
    cin.ignore();
    getline(cin, san_pham);
    cout << "Nhap ma san pham: ";
    getline(cin, ma_san_pham);
    cout << "Nhap gia thanh: ";
    cin >> gia_thanh;
    cout << "Nhap so luong: ";
    cin >> so_luong;
}

void Hanghoa::nhap_de_them_sp() {
    cout << "Nhap ten san pham: ";
    cin.ignore();
    getline(cin, san_pham);
    cout << "Nhap gia thanh: ";
    cin >> gia_thanh;
    cout << "Nhap so luong: ";
    cin >> so_luong;
}

void Hanghoa::xuat() {
    cout << san_pham << "    " << ma_san_pham << "     " << gia_thanh << " VND     x" << so_luong << endl;
}

void Hanghoa::setTensp(string tensp) {
    san_pham = tensp;
}

void Hanghoa::setMasp(string ma) {
    ma_san_pham = ma;
}

void Hanghoa::setGiasp(double gia) {
    gia_thanh = gia;
}

void Hanghoa::setSoLuong(int soLuong) {
    so_luong = soLuong;
}

string Hanghoa::layMaDonHang() {
    return ma_san_pham;
}

string Hanghoa::layTenSanPham() {
    return san_pham;
}

double Hanghoa::layGiaThanh() {
    return gia_thanh;
}

int Hanghoa::laySoLuong() {
    return so_luong;
}

Hanghoa Hanghoa::operator=(const Hanghoa& other) {
    if (this != &other) {
        san_pham = other.san_pham;
        ma_san_pham = other.ma_san_pham;
        gia_thanh = other.gia_thanh;
        so_luong = other.so_luong;
    }
    return *this;
}

bool Hanghoa::operator>(const Hanghoa& other) {
    return gia_thanh > other.gia_thanh;
}
