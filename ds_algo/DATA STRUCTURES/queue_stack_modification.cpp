#include <bits/stdc++.h>
using namespace std;
// stack modification
// stack<pair<int,int>> st;
// deque<int> q;
// void add_element(int new_element) {
//     int new_min = st.empty() ? new_element : min(new_element, st.top().second);
//     st.push({new_element, new_min});
// }
// int remove_element() {
//     int removed_element = st.top().first;
//     st.pop();
// }
// int find_min_element() {
//     return st.top().second;
// }
// int queue_min() {
//     return q.front();
// }
// void queue_add(int new_element) {
//     while(!q.empty() and q.back() > new_element) q.pop_back();
//     q.push_back(new_element);
// }
// int queue_remove(int remove_element) {
//     if(!q.empty() and q.front() == remove_element) q.pop_front();
// }

// queue modification 3
// every operation is in O(1) complexity



stack <pair<int,int>> s1, s2;
void add_element(int new_element) {
    int minimum = s1.empty() ? new_element : min(s1.top().second, new_element);
    s1.push({new_element, minimum});
}
int remove_element() {
    if(s2.empty()) {
        while(!s1.empty()) {
            int element = s1.top().first;
            s1.pop();
            int minimum = s2.empty() ? element : min(element, s2.top().second);
            s2.push({element, minimum});
        }
    }
    int remove_element = s2.top().first;
    s2.pop();
    return remove_element;
}
int find_minimum() {
    if(s1.empty() or s2.empty()) {
        int minimum = s1.empty() ? s2.top().second : s1.top().second;
        return minimum;
    }else min(s1.top().second, s2.top().second);
}

int main() {
    
}