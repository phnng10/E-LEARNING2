#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
using namespace std;

int n;// Số lượng thành phố
int c[20][20];// Ma trận chi phí di chuyển giữa các thành phố
int visited[20];// Tự động khởi tạo giá trị bằng 0 - Đánh dấu thành phố đã thăm
int x[20]; // Lưu lộ trình hiện tại
int best_path[20]; // Lưu lộ trình tốt nhất
int d = 0;// Chi phí hiện tại
int ans = INT_MAX;// Chi phí tối thiểu

void nhap() {
    ifstream fin("input.txt"); 
    fin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fin >> c[i][j];
        }
    }
    fin.close();
}

void Try(int i) {
    // Duyệt qua tất cả các thành phố
    for(int j = 0; j < n; j++) {
        // Nếu thành phố j chưa được thăm
        if(visited[j] == 0) {
            // BƯỚC 1: Chọn thành phố j làm thành phố thứ i trong lộ trình
            x[i] = j;
            visited[j] = 1; // Đánh dấu thành phố j đã thăm
            d += c[x[i-1]][x[i]]; // Cộng chi phí từ thành phố trước đó đến thành phố j

            // BƯỚC 2: Kiểm tra điều kiện dừng
            if(i == n - 1) {
                // Đã thăm đủ n thành phố, tính tổng chi phí (bao gồm quay về điểm xuất phát)
                int total_cost = d + c[x[n-1]][x[0]];
                if(total_cost < ans) {
                    ans = total_cost;
                    // Lưu lộ trình tốt nhất
                    for(int k = 0; k < n; k++) {
                        best_path[k] = x[k];
                    }
                }
            } else {
                // BƯỚC 3: Chưa đủ n thành phố, tiếp tục đệ quy
                Try(i + 1);
            }

            // BƯỚC 4: BACKTRACK - Quay lui để thử các khả năng khác
            visited[j] = 0; // Bỏ đánh dấu thành phố j
            d -= c[x[i-1]][x[i]]; // Trừ lại chi phí
        }
    }
}

int main() {
    nhap();

    auto start = chrono::high_resolution_clock::now();

    x[0] = 0; // Bắt đầu từ thành phố 0
    visited[0] = 1; // Đánh dấu thành phố 0 đã đi

    Try(1);   

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    // ===== IN OUTPUT =====
    cout << "====BACKTRACKING====" << endl;  
    cout << "Chi phi toi thieu: " << ans << endl;
    cout << "Lo trinh toi uu: ";
    for(int i = 0; i < n; i++)
        cout << best_path[i] << " ";
    cout << best_path[0] << endl; // Quay về điểm xuất phát
    cout << "Thoi gian chay: " << elapsed.count() << " ms" << endl;

    return 0;
}
