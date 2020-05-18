#include<vector>
#include<tuple>
#include<iostream>
using namespace std;

/* [2, 2, 2, 2, 3, 11, 11, 11] -> [(2, 4), (5, 1), (11, 3)] */
template<typename T>
vector<pair<T, int>> rle_compress(vector<T> list) {
  vector<pair<T, int>> r;
  for (auto e : list) {
    if (r.empty() || e != r.back().first) r.emplace_back(e , 1);
    else (r.end() - 1)->second++;
  }
  return r;
}

/* [(A, 3), (B, 4)] -> [A, A, A, B, B, B, B] */
template<typename T>
vector<T> rle_expand(vector<pair<T, int>> z) {
  vector<T> r;
  for (auto p : z) for (int i = 0; i < p.second; i++) r.push_back(p.first);
  return r;
}

int main() {
  vector<int> xs = {1,1,1,1,2,3,3,4};
  vector<pair<int, int>> ys = rle_compress(xs);
  for (auto y : ys) {
    cout << y.first << ":" << y.second << endl;
  }
}