#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const unsigned int MOD32 = 3489660929u;
const ull MOD64 = 10232178353385766913ull;
const ull G = 3ull;

inline bool is_2_power(unsigned int x) {
  return ((x != 0) && ((x & (~x + 1)) == x));
}

ull mod_power(ull n, ull p, ull mod) {
  ull ans = 1LL;
  for (; p > 0; n = n * n % mod, p >>= 1) if (p & 0x01) ans = ans * n % mod;
  return ans;
}

/* Number Theoretic Transform:
   Input: Polynomial a where a(x) = a[0] + a[1]x + a[2]x^2 + a[n - 1]x^(n-1)
   Output: [a(ω^0), a(ω^1), …, a(ω^(n-1))], where ω^n = 1.
 */
void naive_ntt(vector<unsigned int> &a) {
  assert(is_2_power(a.size()));
  int n = a.size();
  if (n <= 1) return;
  vector<unsigned int> odd;
  vector<unsigned int> even;
  for (size_t i = 0; i < n; i++) 
    (i % 2 ? odd : even).push_back(a[i]);
  
  unsigned int ω = (unsigned int)mod_power(G, (MOD32 - 1) / a.size(), MOD32);
  
  naive_ntt(odd);
  naive_ntt(even);

  for (size_t k = 0; k < n / 2; k++) {
    unsigned int ω_k = (unsigned int)mod_power(ω, k, MOD32);
    unsigned int ω_k_odd_k = (unsigned int)((ull)odd[k] * ω_k % MOD32);
    a[k] = (even[k] + ω_k_odd_k) % MOD32;
    a[k + n / 2] = ((ull)MOD32 + even[k] - ω_k_odd_k) % MOD32;
  }
}

void naive_intt(vector<unsigned int> &a) {
  naive_ntt(a);
  unsigned int inv_n = mod_power(a.size(), MOD32 - 2, MOD32);
  for (size_t i = 0; i < a.size(); i++) {
    a[i] = (ull)a[i] * inv_n % MOD32;
  }
  for (size_t i = 1; i < a.size() / 2; i++) 
    swap(a[i], a[a.size() - i]);
}

int main(int argc, char const *argv[])
{
  vector<unsigned> a = {1, 2, 0, 0};
  vector<unsigned> b = {3, 4, 0, 0};

  naive_ntt(a);
  naive_ntt(b);

  vector<unsigned> c(a.size());
  for (size_t i = 0; i < a.size(); i++) {
    c[i] = (ull)a[i] * b[i] % MOD32;
  }

  naive_intt(c);
  cout << c << endl;
  return 0;
}