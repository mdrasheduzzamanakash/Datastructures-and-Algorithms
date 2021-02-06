#include <bits/stdc++.h>
using namespace std;

// one based implementation
struct FenwickTreeOneBasedIndexing {
    vector<int> bit;
    int n;
    FenwickTreeOneBasedIndexing(int n) {
        this -> n = n + 1;
        bit.assign(n + 1, 0);
    }
    FenwickTreeOneBasedIndexing(vector <int> a) : 
        FenwickTreeOneBasedIndexing(a.size()) {
            for(int i = 0;i < n;i++) add(i, a[i]);
        }
    void add(int idx, int data) {
        for(++idx;idx < n;idx += (idx & -idx)) bit[idx] += data;
    }
    void rangeUpdate(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    int sum(int idx) {
        int ret = 0;
        for(++idx;idx > 0;idx -= (idx & -idx)) ret += bit[idx];
        return ret;
    }
    
};
int main() {
    vector<int> v = {1, 2, 3, 4, 5, 1, 2, 3};
    FenwickTreeOneBasedIndexing ft(v);
    cout << ft.sum(4) << endl;
}