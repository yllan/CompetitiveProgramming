#include <iostream>
#include <tuple>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

/* find the smallest p such that p > 0 and 2^p >= x */
int lg(int x) {
  int ans = 1;
  while ((1ll << ans) < x) ans++;
  return ans;
}

/* array of index */
vector<int> suffix_array(string s)
{
  int l = s.length(), k;
  int ord[lg(l)][l];

  for (int i = 0; i < l; i++) ord[0][i] = s[i];
  
  for (k = 1; (1 << k) <= l; k++) {
    vector<tuple<int, int, int>> v;
    for (int i = 0; i < l; i++) {
      int next = i + (1 << (k - 1));
      if (next < l) {
        v.push_back(make_tuple(ord[k - 1][i], ord[k - 1][next], i));
      } else {
        v.push_back(make_tuple(ord[k - 1][i], -1, i));
      }
    }
    // can use radix-sort to improve the time-complexity here
    sort(v.begin(), v.end());

    for (int i = 0; i < l; i++) {
      if (i == 0) {
        ord[k][get<2>(v[i])] = 0;
      } else if (get<0>(v[i]) == get<0>(v[i - 1]) && get<1>(v[i]) == get<1>(v[i - 1])) {
        ord[k][get<2>(v[i])] = ord[k][get<2>(v[i - 1])];
      } else {
        ord[k][get<2>(v[i])] = i;
      }
    }
  }

  vector<pii> u;
  vector<int> result(l);

  for (int i = 0; i < l; i++) u.push_back(make_pair(ord[k - 1][i], i));
  sort(u.begin(), u.end());
  for (int i = 0; i < l; i++) 
    result[i] = u[i].second;
  return result;
}

int main()
{
  string s = "Hello, world. Many of them is just an one-off bubble.";
  for (auto idx : suffix_array(s)) {
    cout << idx << endl;
  }
}