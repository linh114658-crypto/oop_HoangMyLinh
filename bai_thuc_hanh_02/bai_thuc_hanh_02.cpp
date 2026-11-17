#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>   
#include <ctime>     
using namespace std;

string ChuanHoaTen(string s) {
    for (size_t i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    if (s == "car") return "Car";
    if (s == "motorcycle") return "Motorcycle";
    if (s == "bicycle") return "Bicycle";
    return "";
}
class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do_xe;

public:
    phuong_tien() {
        ma_xe = 0;
        loai_xe = "";
        gio_vao = 0;
        tg_do = 0;
        phi_do_xe = 0;
    }
    phuong_tien(int ma, string loai, int gio, int tg) {
        this->ma_xe = ma;
        this->loai_xe = loai;
        this->gio_vao = gio;
        this->tg_do = tg;
        this->phi_do_xe = 0;
        tinh_phi();
    }
    int lay_ma_xe() const { return ma_xe; }
    string lay_loai_xe() const { return loai_xe; }
    int lay_gio_vao() const { return gio_vao; }
    int lay_tg_do() const { return tg_do; }
    double lay_phi() const { return phi_do_xe; }
    void setMa_xe(int ma_xe) {
        this->ma_xe = ma_xe;
    }
    void setLoai_xe(string loai_xe) {
        if (ChuanHoaTen(loai_xe) != "") {
            this->loai_xe = ChuanHoaTen(loai_xe);
            tinh_phi();
        }
    }
    void setGio_vao(int gio_vao) {
        if (gio_vao >= 0 && gio_vao <= 23) {
            this->gio_vao = gio_vao;
            tinh_phi();
        }
    }
    void setTg_do(int tg_do) {
        if (tg_do >= 1 && tg_do <= 23) {
            this->tg_do = tg_do;
            tinh_phi();
        }
    }

    void setPhi(double phi_do_xe) {
        this->phi_do_xe = phi_do_xe;
    }
    void tinh_phi() {
        double gia = 0;
        if (loai_xe == "Car") gia = 6.0;
        else if (loai_xe == "Motorcycle") gia = 4.0;
        else if (loai_xe == "Bicycle") gia = 2.0;
        bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
        phi_do_xe = 0;
        for (int h = 1; h <= tg_do; h++) {
            if (h <= 2) {
                if (cao_diem) phi_do_xe += gia * 1.30;
                else phi_do_xe += gia * 0.95;
            } else {
                phi_do_xe += gia * 0.90;
            }
        }
    }

    void hien_thi() const {
        cout << "  ID: " << ma_xe << " | " << loai_xe << " | Vao: " << gio_vao
             << "h | Do: " << tg_do << "h" << " | Phi: $" << fixed << setprecision(2)
             << phi_do_xe << "\n";
    }
};

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int MAX_VEHICLES = 3;     
    phuong_tien ds_xe[MAX_VEHICLES];        
    int so_xe;                             

public:
    bai_xe() {
        ma_bai = 0;
        kich_thuoc = 'S';
        so_xe = 0;
    }

    bai_xe(int ma_bai, char kich_thuoc) {
        this->ma_bai = ma_bai;
        this->kich_thuoc = kich_thuoc;
        this->so_xe = 0;
    }

    int lay_ma() const { return ma_bai; }
    char lay_kich_thuoc() const { return kich_thuoc; }
    int lay_so_xe() const { return so_xe; }

    int suc_chua() const {
        if (kich_thuoc == 'S') return 1;
        if (kich_thuoc == 'M') return 2;
        return 3;
    }
    bool da_day() const { return so_xe >= suc_chua(); }
    int tim_xe(int ma_xe) const {
        for (int i = 0; i < so_xe; i++) {
            if (ds_xe[i].lay_ma_xe() == ma_xe) return i;
        }
        return -1;
    }
    bool them(const phuong_tien& v) {
        if (da_day()) return false;
        ds_xe[so_xe] = v;
        so_xe++;
        return true;
    }

    bool xoa(int ma_xe) {
        int vt = tim_xe(ma_xe);
        if (vt == -1) return false;
        for (int i = vt; i < so_xe - 1; i++) {
            ds_xe[i] = ds_xe[i + 1];        
        }
        so_xe--;                            
        return true;
    }

    void hien_thi() const {
        cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
             << so_xe << "/" << suc_chua() << " xe\n";
        for (int i = 0; i < so_xe; i++) ds_xe[i].hien_thi();
    }

    int dem_theo_loai(string loai) const {
        int n = 0;
        for (int i = 0; i < so_xe; i++)
            if (ds_xe[i].lay_loai_xe() == loai) n++;
        return n;
    }

    double tong_phi_theo_loai(string loai) const {
        double s = 0;
        for (int i = 0; i < so_xe; i++)
            if (ds_xe[i].lay_loai_xe() == loai) s += ds_xe[i].lay_phi();
        return s;
    }

    int hien_thi_theo_loai(string loai) const {
        int n = dem_theo_loai(loai);
        if (n == 0) return 0;
        cout << "Bai " << ma_bai << " [" << kich_thuoc << "]:\n";
        for (int i = 0; i < so_xe; i++)
            if (ds_xe[i].lay_loai_xe() == loai) ds_xe[i].hien_thi();
        return n;
    }
};

class SystemInterface {
private:
    static const int MAX_LOTS = 10;         
    bai_xe ds_bai[MAX_LOTS];                
    int so_bai;                           
    int tim_bai(int ma) const {
        for (int i = 0; i < so_bai; i++)
            if (ds_bai[i].lay_ma() == ma) return i;
        return -1;
    }
    int tim_bai_chua_xe(int ma_xe) const {
        for (int i = 0; i < so_bai; i++)
            if (ds_bai[i].tim_xe(ma_xe) != -1) return i;
        return -1;
    }
    string ten_loai(int i) {
        if (i == 1) return "Car";
        if (i == 2) return "Motorcycle";
        return "Bicycle";
    }
    void tao_bai() {
        if (so_bai >= MAX_LOTS) {
            cout << "Da du so bai toi da!\n";
            return;
        }
        int ma;
        cout << "Ma bai: ";
        cin >> ma;
        while (cin.fail() || ma < 1) {
            cin.clear();                    
            cin.ignore(1000, '\n');         
            cout << "Gia tri khong hop le, nhap lai (so duong): ";
            cin >> ma;
        }
        if (ton_tai_ma_bai(ma)) {
            cout << "Ma bai " << ma << " bi trung! ";
            while (ton_tai_ma_bai(ma)) ma = sinh_ma_ngau_nhien();   
            cout << "Da tu dong gan ma moi: " << ma << "\n";
        }
        char kt;
        cout << "Kich thuoc (S/M/L): ";
        cin >> kt;
        kt = toupper(kt);
        while (kt != 'S' && kt != 'M' && kt != 'L') {
            cout << "Chi nhan S, M, L. Nhap lai: ";
            cin >> kt;
            kt = toupper(kt);
        }
        ds_bai[so_bai] = bai_xe(ma, kt);    
        so_bai++;
        cout << "Da tao bai " << ma << "\n";
    }

    void them_xe() {
        if (so_bai == 0) {
            cout << "Chua co bai nao!\n";
            return;
        }
        int ma;
        cout << "Ma xe: ";
        cin >> ma;
        while (cin.fail() || ma < 1) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Gia tri khong hop le, nhap lai (so duong): ";
            cin >> ma;
        }
        if (ton_tai_ma_xe(ma)) {
            cout << "Ma xe " << ma << " bi trung! ";
            while (ton_tai_ma_xe(ma)) ma = sinh_ma_ngau_nhien();
            cout << "Da tu dong gan ma moi: " << ma << "\n";
        }
        string loai;
        cout << "Loai (Car/Motorcycle/Bicycle): ";
        cin >> loai;
        loai = ChuanHoaTen(loai);
        while (loai == "") {
            cout << "Loai xe sai. Nhap lai: ";
            cin >> loai;
            loai = ChuanHoaTen(loai);
        }
        int gio;
        cout << "Gio vao (0-23): ";
        cin >> gio;
        while (cin.fail() || gio < 0 || gio > 23) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Gia tri khong hop le, nhap lai (0-23): ";
            cin >> gio;
        }
        int tg;
        cout << "Thoi luong (1-23): ";
        cin >> tg;
        while (cin.fail() || tg < 1 || tg > 23 || gio + tg > 24) {   
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Khong hop le (1-23 va gio vao + thoi luong <= 24), nhap lai: ";
            cin >> tg;
        }

        phuong_tien v(ma, loai, gio, tg);
        for (int i = 0; i < so_bai; i++) {
            if (ds_bai[i].them(v)) {
                cout << "Da them xe " << ma << " vao bai " << ds_bai[i].lay_ma()
                     << " | Phi: $" << fixed << setprecision(2) << v.lay_phi() << "\n";
                return;
            }
        }
        cout << "Tat ca bai da day!\n";
    }

    void xoa_bai() {
        int ma;
        cout << "Ma bai can xoa: ";
        cin >> ma;
        while (cin.fail() || ma < 1) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Gia tri khong hop le, nhap lai (so duong): ";
            cin >> ma;
        }
        int vt = tim_bai(ma);
        if (vt == -1) { cout << "Khong tim thay bai!\n"; return; }
        for (int i = vt; i < so_bai - 1; i++) {
            ds_bai[i] = ds_bai[i + 1];
        }
        so_bai--;
        cout << "Da xoa bai " << ma << "\n";
    }

    void lay_xe_ra() {
        int ma;
        cout << "Ma xe can lay ra: ";
        cin >> ma;
        while (cin.fail() || ma < 1) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Gia tri khong hop le, nhap lai (so duong): ";
            cin >> ma;
        }
        int vt = tim_bai_chua_xe(ma);
        if (vt != -1 && ds_bai[vt].xoa(ma)) cout << "Da lay xe ra\n";   
        else cout << "Khong tim thay xe!\n";
    }

    void hien_thi_cac_bai() {
        if (so_bai == 0) { cout << "Chua co bai nao!\n"; return; }
        for (int i = 0; i < so_bai; i++) {
            cout << "Bai " << ds_bai[i].lay_ma() << " | Size " << ds_bai[i].lay_kich_thuoc()
                 << " | " << ds_bai[i].lay_so_xe() << "/" << ds_bai[i].suc_chua() << " xe\n";
        }
    }

    void hien_thi_xe_theo_bai() {
        int ma;
        cout << "Ma bai: ";
        cin >> ma;
        while (cin.fail() || ma < 1) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Gia tri khong hop le, nhap lai (so duong): ";
            cin >> ma;
        }
        int vt = tim_bai(ma);
        if (vt == -1) cout << "Khong tim thay bai!\n";
        else ds_bai[vt].hien_thi();
    }

    void liet_ke_theo_loai() {
        string loai;
        cout << "Loai xe: ";
        cin >> loai;
        loai = ChuanHoaTen(loai);
        if (loai == "") { cout << "Loai xe khong hop le!\n"; return; }
        int tong = 0;
        for (int i = 0; i < so_bai; i++)
            tong += ds_bai[i].hien_thi_theo_loai(loai);
        if (tong == 0) cout << "Khong co xe loai " << loai << "\n";
    }

    void bao_cao() {
        cout << "--- Toan he thong ---\n";
        for (int t = 1; t <= 3; t++) {
            int dem = 0;
            double tong = 0;
            for (int i = 0; i < so_bai; i++) {
                dem += ds_bai[i].dem_theo_loai(ten_loai(t));
                tong += ds_bai[i].tong_phi_theo_loai(ten_loai(t));
            }
            cout << ten_loai(t) << ": ";
            if (dem == 0) cout << "khong co xe\n";
            else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
        }
        cout << "--- Theo tung bai ---\n";
        for (int i = 0; i < so_bai; i++) {
            cout << "Bai " << ds_bai[i].lay_ma() << ":\n";
            for (int t = 1; t <= 3; t++) {
                int dem = ds_bai[i].dem_theo_loai(ten_loai(t));
                cout << "  " << ten_loai(t) << ": ";
                if (dem == 0) cout << "khong co xe\n";
                else cout << dem << " xe | TB: $" << fixed << setprecision(2)
                          << ds_bai[i].tong_phi_theo_loai(ten_loai(t)) / dem << "\n";
            }
        }
    }

public:
    SystemInterface();
    void runMenu();
    bool ton_tai_ma_bai(int pID) const;     
    bool ton_tai_ma_xe(int vID) const;     
    int sinh_ma_ngau_nhien();               
};

SystemInterface::SystemInterface() {
    so_bai = 0;
}
bool SystemInterface::ton_tai_ma_bai(int pID) const {
    return tim_bai(pID) != -1;
}
bool SystemInterface::ton_tai_ma_xe(int vID) const {
    return tim_bai_chua_xe(vID) != -1;
}
int SystemInterface::sinh_ma_ngau_nhien() {
    return rand() % 9000 + 1000;
}

void SystemInterface::runMenu() {
    int chon;
    do {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
        while (cin.fail() || chon < 1 || chon > 9) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Gia tri khong hop le, nhap lai (1-9): ";
            cin >> chon;
        }
        switch (chon) {
            case 1: tao_bai(); break;
            case 2: them_xe(); break;
            case 3: xoa_bai(); break;
            case 4: lay_xe_ra(); break;
            case 5: hien_thi_cac_bai(); break;
            case 6: hien_thi_xe_theo_bai(); break;
            case 7: liet_ke_theo_loai(); break;
            case 8: bao_cao(); break;
            case 9: cout << "Tam biet!\n"; break;
        }
    } while (chon != 9);
}

int main() {
    srand(time(0));     
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
