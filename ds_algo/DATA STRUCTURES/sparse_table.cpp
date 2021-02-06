#include <bits/stdc++.h>
#define MAXN 500
using namespace std;

// here total memory complexity O(nlog(n))
// total time complexity for building table O(nlog(n))
// query time complexity O(log(n))
// Range Minimum query RMQ is O(1) // idempotance operation
// to do associative operation in O(1) use sqrt or 
// disjoint sparse table ds

long long st[MAXN][50];
long long arr[MAXN];
long long N; // array size
long long range_sum_query(int L, int R) {
    long long K = log(MAXN);
    for(int i = 0;i < N;i++) st[i][0] = arr[i];
    for(int j = 1;j <= K;j++)
        for(int i = 0; i + (1 << j) <= N;i++) 
            st[i][j] = st[i][j-1] + st[i + (1 << (j - 1))][j-1];
    
    long long sum = 0;
    for(int j = K;j >= 0;j--) {
        if((1 << j) <= (R - L + 1)) {
            sum += st[L][j];
            L += (1 << j);
        }
    }
    return sum;
}
// precomputing logarithmic values
long long Log[MAXN + 1];
void precal_log() {
    Log[1] = 0;
    for(int i = 2; i <= MAXN;i++) Log[i] = Log[i / 2] + 1;
}

long long range_minimum_queries(int L, int R) {
    long long K = log(MAXN);
    for(int i = 0;i < N;i++) st[i][0] = arr[i];
    for(int j = 1;j <= K;j++)
        for(int i = 0; i + (1 << j) <= N;i++) 
            st[i][j] = min(st[i][j-1] , st[i + (1 << (j - 1))][j-1]);
    
    int j = Log[R - L + 1];
    int minimum = min(st[L][j], st[R - (1 << j) + 1][j]);
    return minimum;
}

int main() {
    cin >> N;
    for(int i = 0;i < N;i++) cin >> arr[i];
    precal_log();
    cout << range_sum_query(0, N -1) << endl;
    cout << range_minimum_queries(0, 4);
}