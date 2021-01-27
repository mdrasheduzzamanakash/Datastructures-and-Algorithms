#include <bits/stdc++.h>
using namespace std;
int parent[100];
int Rank[100];

void make_set(int v)
{
   parent[v] = v;
   Rank[v] = 0;
}
int find_set(int v)
{
   if (v == parent[v])
       return v;
   return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b)
{
   a = find_set(a);
   b = find_set(b);
   if(a != b) {
       if(Rank[a] < Rank[b]) swap(a, b);
       parent[b] = a;
       if(Rank[a] == Rank[b]) Rank[a]++;
   }
}
int main()
{

}