#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include <array>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> pnt;
typedef pair<int, int> pii;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define REPI(i,n) for(int (i)=0;(i)<(int)(n);(i)++)

template <typename T, typename U>
inline std::ostream& operator<< (std::ostream& os, const std::pair<T, U>& v);
template <typename T>
inline std::ostream& operator<< (std::ostream& os, const std::vector<T>& v);

template <typename T, typename U>
inline std::ostream& operator<< (std::ostream& os, const std::pair<T, U>& v) {
  os << "(" << v.first << ", " << v.second << ")";
  return os;
}

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
  for (auto e : v) {
    os << e << " ";
  }
  // std::copy (v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
  return os;
}

// begin math library

/*
   n =     100,000   cost ~  0.0sec, max prime =   1,299,709
   n =   1,000,000   cost ~  1.7sec, max prime =  15,485,867
   n =  10,000,000   cost ~ 46.1sec, max prime = 179,424,673, ram ~ 40MB
*/
void generate_primes(int n, vi &primes) {
  primes.push_back(2); primes.push_back(3); primes.push_back(5);
  n -= 3;
  auto is_prime = [](int t, vi &primes) -> bool {
    for (auto p : primes) {
      if (p * p > t) break;
      if (t % p == 0) return false;
    }
    return true;
  };
  for (int six = 6; n > 0; six += 6) {
    if (is_prime(six + 1, primes)) primes.push_back(six + 1), n--;
    if (is_prime(six + 5, primes)) primes.push_back(six + 5), n--;
  }
}

/* return 2, 2, 2, 5, 7 for 2^3 * 5 * 7 */
vi factorize(int x, vi &primes) {
  vi factors;
  int bound = x;
  for (auto p : primes) {
    if (x == 1 || p * p > bound) break;
    for (; x % p == 0; x /= p) factors.push_back(p);
  }
  if (x != 1) factors.push_back(x);
  return factors;
}

ll power(ll n, int p) {
  ll ans = 1LL;
  for (; p > 0; n = n * n, p >>= 1) if (p & 0x01) ans *= n;
  return ans;
}

ll totient(ll n, vi &primes) {
  vector<pair<int, int>> fs = rle_compress(factorize(n, primes));
  ll phi = 1ll;
  for (int i = 0; i < fs.size(); i++) {
    int p = fs[i].first;
    int k = fs[i].second;
    phi *= power(p, k - 1) * (p - 1);
  }
  return phi;
}

ll choose(int n, int k) {
  k = min(k, n - k);
  __int128 ans = 1LL;
  for (int i = n - k + 1; i <= n; i++) ans *= i;
  for (int i = 1; i <= k; i++) ans /= i;
  return (ll)ans;
}

ll factorial(int n) {
  ll ans = 1LL;
  for (auto i = 2; i <= n; ans *= i, i++) ;
  return ans;
}

/****** 128-bit I/O ********/
inline __int128 INT128(const string &literal) {
  __int128 r = 0;
  for (int i = 0; i < literal.length(); i++) {
    r = r * 10 + (literal[i] - '0');
  }
  return r;
}

inline string to_string(__int128 n) {
  string sign = (n < 0) ? "-" : "";
  if (n == 0) return "0";
  stringstream rs;
  for (; n != 0; n /= 10) {
    rs << abs((int)(n % 10));
  }
  string r = rs.str();
  reverse((r).begin(), (r).end());
  return sign + r;
}

inline std::ostream& operator<< (std::ostream& os, const __int128 & v) {
  os << to_string(v);
  return os;
}

// end math library

int main(int argc, char* argv[])
{
  cout << power(3, 11) << endl;
  cout << factorial(10) << endl;
  cout << choose(6, 3) << endl;
  vi primes;
  ll b = clock();
  int bound = 100;
  generate_primes(bound, primes);
  cout << bound << " cost: " << clock() - b << endl;
  cout << "max prime: " << *(primes.end() - 1) << endl;

  vi factors = factorize(factorial(10), primes);  
  cout << factors << endl;
  
  __int128 t = INT128("170141183460469231731687303715884105727");
  t += 1;
  cout << t << endl;
  
  
  return 0;
}
