#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int n;                      //Số thành phố
long long cost[20][20];     //Ma trận chi phí di chuyển

//dp[mask][i]: chi phí nhỏ nhất để đi qua các thành phố trong mask và kết thúc tại thành phố i
long long dp[1 << 16][20];

//parent[mask][i]: lưu thành phố trước đó để truy vết lộ trình
int parent[1 << 16][20];

pair<long long, vector<int>> solveTSP() {

    //Khởi tạo toàn bộ dp là vô cùng
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = INF;
            parent[mask][i] = -1;
        }
    }

    //Bắt đầu từ thành phố 0 (chỉ có thành phố 0 được thăm)
    dp[1][0] = 0;

    //Duyệt qua tất cả các tập con của các thành phố
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {

            //Nếu thành phố u không thuộc mask thì bỏ qua hoặc trạng thái này chưa từng được cập nhật
            if (!(mask & (1 << u)) || dp[mask][u] == INF)
                continue;

            //Thử đi sang các thành phố chưa được thăm
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue; //v đã được thăm

                int newMask = mask | (1 << v);
                long long newCost = dp[mask][u] + cost[u][v];

                //Cập nhật nếu tìm được chi phí nhỏ hơn
                if (newCost < dp[newMask][v]) {
                    dp[newMask][v] = newCost;
                    parent[newMask][v] = u;
                }
            }
        }
    }

    //Khi đã thăm tất cả các thành phố
    int fullMask = (1 << n) - 1;
    long long minCost = INF;
    int lastCity = -1;

    //Tìm thành phố kết thúc sao cho quay về 0 có chi phí nhỏ nhất
    for (int i = 1; i < n; i++) {
        if (dp[fullMask][i] + cost[i][0] < minCost) {
            minCost = dp[fullMask][i] + cost[i][0];
            lastCity = i;
        }
    }

    //Truy vết lộ trình
    vector<int> route;
    int mask = fullMask;
    int cur = lastCity;

    while (cur != -1) {
        route.push_back(cur);
        int prev = parent[mask][cur];
        mask ^= (1 << cur);   //Loại bỏ thành phố hiện tại khỏi mask
        cur = prev;
    }

    //Đảo ngược để có thứ tự đúng từ thành phố 0
    reverse(route.begin(), route.end());
    route.push_back(0);  //Quay về điểm xuất phát

    return {minCost, route};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //Nhập số thành phố
    cin >> n;

    //Nhập ma trận chi phí
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    //Bắt đầu đo thời gian thực thi thuật toán
    auto start = chrono::high_resolution_clock::now();

    //Giải bài toán TSP
    auto result = solveTSP();
    long long minCost = result.first;
    vector<int> route = result.second;

    //Kết thúc đo thời gian
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    //Xuất kết quả ra màn hình
    cout << "==== DP - BITMASK ====\n";
    cout << "Chi phi toi thieu: " << minCost << "\n";
    cout << "Lo trinh: ";
    for (int city : route) {
        cout << city << " ";
    }
    cout << "\n";
    cout << "Thoi gian: " << duration.count() << " ms\n";

    return 0;
}
