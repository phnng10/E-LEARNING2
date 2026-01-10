#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
using namespace std;

int n;
int c[20][20];
int visited[20];
int x[20];
int d = 0;
int ans = INT_MAX;

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
    for(int j = 0; j < n; j++) {
        if(visited[j] == 0) {
            x[i] = j;
            visited[j] = 1;
            d += c[x[i-1]][x[i]];

            if(i == n - 1) {
                ans = min(ans, d + c[x[n-1]][x[0]]);
            } else {
                Try(i + 1);
            }

            // backtrack
            visited[j] = 0;
            d -= c[x[i-1]][x[i]];
        }
    }
}

int main() {
    nhap();

    auto start = chrono::high_resolution_clock::now();

    x[0] = 0;
    visited[0] = 1;

    Try(1);   

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    // ===== IN OUTPUT =====
    cout << "====BACKTRACKING====" << endl;  
    cout << "Chi phi toi thieu: " << ans << endl;
    cout << "Lo trinh: ";
    for(int i = 0; i < n; i++)
        cout << x[i] << " ";
    cout << x[0] << endl;
    cout << "Thoi gian chay: " << elapsed.count() << " ms" << endl;

    return 0;
}
