#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

class TSP_Greedy {
private:
    int n;
    vector<vector<int>> cost;
    vector<bool> visited;
    vector<int> path;
    int minCost;
    
public:
    TSP_Greedy(int n, vector<vector<int>>& cost) {
        this->n = n;
        this->cost = cost;
        visited.resize(n, false);
        minCost = 0;
    }
    
    void Try() {
        //start
        int current = 0;
        path.push_back(current);
        visited[current] = true;
        
        //tham n-1 thanh pho con lai
        for (int i = 1; i < n; i++) {
            int nextCity = -1;
            int minDist = INT_MAX;
            
            //tim thanh pho gan nhat
            for (int j = 0; j < n; j++) {
                if (!visited[j] && cost[current][j] > 0 && cost[current][j] < minDist) {
                    minDist = cost[current][j];
                    nextCity = j;
                }
            }
            
            //di chuyen den thanh pho gan nhat
            if (nextCity != -1) {
                visited[nextCity] = true;
                path.push_back(nextCity);
                minCost += minDist;
                current = nextCity;
            }
        }
        
        //quay ve thanh pho 0
        minCost += cost[current][0];
    }
    
    void printResult() {
        cout << "====GREEDY ====" << endl;
        cout << "Chi phi: " << minCost << endl;
        cout << "Lo trinh: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " ";
        }
        cout << " 0" << endl;
    }
    
    int getMinCost() {
        return minCost;
    }  
    vector<int> getPath() {
        return path;
    }
};

int main() {
    int n;
    cout << "Nhập số thành phố:\n";
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }
    
    //do thoi gian 
    auto start = high_resolution_clock::now();
    //Greedy
    TSP_Greedy greedy(n, cost);
    greedy.Try();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    greedy.printResult();
    cout << "Thoi gian: " << duration.count() << " ms" << endl;
    
    return 0;
}