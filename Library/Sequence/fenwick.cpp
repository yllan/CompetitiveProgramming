/* Fenwick Tree (Binary Indexed Tree)

Mode:
  1. Point Update, Range Query
  2. Range Update, Point Query
  3. Range Update, Range Query

F[0] = A[0]
F[1] = A[0] + A[1]
F[2] = A[2]
F[3] = A[0] + A[1] + A[2] + A[3]
F[4] = A[4]
F[5] = A[4] + A[5]
F[6] = A[6]
F[7] = A[0] + A[1] + A[2] + A[3] + A[4] + A[5] + A[6] + A[7]
F[8] = A[8]
F[9] = A[8] + A[9]
F[10] = A[10]
F[11] = A[8] + A[9] + A[10] + A[11]
F[12] = A[12]
F[13] = A[12] + A[13]
F[14] = A[14]
F[15] = A[0] + A[1] + A[2] + A[3] + A[4] + A[5] + A[6] + A[7] + A[8] + A[9] + A[10] + A[11] + A[12] + A[13] + A[14] + A[15]

*/

#include <cstdio>

/**************************** BEGIN OF LIBRARY CODE ****************************/
#include <cstdlib>
#define UNSET_RIGHTMOST_BIT(n)  (n &= n - 1)

// sum the first n elements of original array (0 to n-1)
template <typename T>
T fenwick_prefix_sum(T* f, int n) {
  T sum = 0;
  for (; n > 0; UNSET_RIGHTMOST_BIT(n)) sum += f[n - 1];
  return sum;
}

// sum in [begin, end)
template <typename T>
T fenwick_range_sum(T* f, int begin, int end) {
  return fenwick_prefix_sum(f, end) - fenwick_prefix_sum(f, begin);
}

// update the fenwick tree for A[idx] += val, A.length = f_size
template <typename T>
void fenwick_inc_point(T* f, int f_size, int idx, T val) {
  for (; idx < f_size; idx |= (idx + 1)) f[idx] += val;
}

// Point Update, Range Query
template <typename T>
class PURQFenwick {
  T *f;
  int f_size;

public:
  PURQFenwick(int size): f_size(size), f{ (T*)calloc(size, sizeof(T)) } {}
  ~PURQFenwick() { free(f); }

  // sum of [0, n) (not including n)
  T sum(int n) { return fenwick_prefix_sum(f, n); }

  // sum of [begin, end) (not including end)
  T sum(int begin, int end) { return fenwick_range_sum(f, begin, end); }

  void update(int idx, T val) { fenwick_inc_point(f, f_size, idx, val); }
};

// Range Update, Point Query
// 把一次 Update([begin, end), val) 轉化成兩次 Update([begin, ∞), val), Update([end, ∞), -val)
// 則 A[i] 的值就相當於所有 Update([j, ∞), v) where j <= i 的加總
// 若我們想像有個陣列 U[i] 存 Update([begin, ∞), val)，則 A[i] 就相當於 U[0]+...+U[i]
// 因此用 PURQFenwick 來存 U, 要算 A[i] 就是 prefix_sum(i + 1).
template <typename T>
class RUPQFenwick {
  PURQFenwick<T> f;
public:
  RUPQFenwick(int size): f{ PURQFenwick<T>(size) } {}
  T at(int idx) { return f.sum(idx + 1); } 
  void update(int begin, int end, T val) {
    f.update(begin, val);
    f.update(end, -val);
  }
};

/* Range Update, Range Query
  假想一個 prefix array: P[k] = A[0] + ... + A[k - 1]

  一個 Update([begin, end), val), 對於 P[k] 有三種狀況：
  1. k <= begin,        |------sum---------k---(update)--
     這個 update 不影響 P[k], 貢獻為 0
  
  2. k > end,           |--sum---(update)--k-------------
     這個 update 對 P[k] 貢獻 (end - begin) * val,
     可以拆解為 Update([begin, ∞), -val * begin), Update([end, ∞), val * end)

  3. begin < k <= end,  |--sum----------(--k-update)----- 
     這個 update 對 P[k] 貢獻 (k - begin) * val,
     使用 case (2) 的拆解，發現 Update([end, ∞), val * end) 對於 P[k] 沒貢獻，
     因此需要修正量 k * val

  U[i] 存 Update([i, ∞), v)
  V[i] 存修正量 val

  P[k] = U[0]+...+U[k - 1]+ k * V[i]
*/
template <typename T>
class Fenwick {
  PURQFenwick<T> fu;
  RUPQFenwick<T> fv;
public:
  Fenwick(int size): fu{ PURQFenwick<T>(size) }, fv{ RUPQFenwick<T>(size) } {}

  void update(int begin, int end, T val) {
    fu.update(begin, -val * begin);
    fu.update(end, val * end);
    fv.update(begin, end, val);
  }

  T sum(int k) { return fu.sum(k) + k * fv.at(k - 1); }
  T sum(int begin, int end) { return sum(end) - sum(begin); }
};

/**************************** END OF LIBRARY CODE ****************************/

// --------- Test code ---------
long long brute_force_sum(long long *a, int b, int e) {
  long long sum = 0;
  for (int i = b; i < e; i++) sum += a[i];
  return sum;
}

int main() {
  #define N 987
  long long f[N], a[N];

  // random test
  for (int t = 0; t < 200; t++) {
    long long sum = 0;

    for (int i = 0; i < N; i++) a[i] = rand();
    for (int i = 0; i < N; i++) f[i] = 0;
    for (int i = 0; i < N; i++) fenwick_inc_point(f, N, i, a[i]);

    for (int i = 0; i < N; i++) {
      sum += a[i];
      if (sum != fenwick_prefix_sum(f, i + 1)) {
        fprintf(stderr, "prefix_sum error at %d\n", i);
        abort();
      }
    }

    for (int b = 0; b < N; b ++) {
      for (int e = b; e <= N; e++) {
        if (brute_force_sum(a, b, e) != fenwick_range_sum(f, b, e)) {
          fprintf(stderr, "range sum [%d, %d) failed!\n", b, e);
          abort();
        }
      }
    }
  }
  puts("* Basic function passed.");
  
  PURQFenwick<long long> purq(N);
  for (int i = 0; i < N; i++) purq.update(i, a[i]);

  for (int i = 0; i <= N; i++) {
    if (brute_force_sum(a, 0, i) != purq.sum(i)) {
      fprintf(stderr, "PURQFenwick,sum(%d) failed!\n", i);
      abort();
    }
  }
  puts("* PURQFenwick.sum(n) passed.");

  for (int b = 0; b < N; b++) {
    for (int e = b; e <= N; e++) {
      if (brute_force_sum(a, b, e) != purq.sum(b, e)) {
        fprintf(stderr, "PURQFenwick.sum(%d, %d) failed!\n", b, e);
        abort();
      }
    }
  }
  puts("* PURQFenwick.sum(b, e) passed.");

  RUPQFenwick<long long> rupq(N);
  for (int i = 0; i < N; i++) a[i] = 0;
  for (int t = 0; t < 500; t++) {
    int idx_a = rand() % N;
    int idx_b = idx_a + (rand() % (N + 1 - idx_a));
    long long v = (rand() % 98765) * (rand() % 2 ? 1 : -1);
    for (int i = idx_a; i < idx_b; i++) a[i] += v;
    rupq.update(idx_a, idx_b, v);
  }
  for (int i = 0; i < N; i++) {
    if (a[i] != rupq.at(i)) {
      fprintf(stderr, "RUPQFenwick.at(%d) failed!\n", i);
      abort();
    }
  }
  puts("* RUPQFenwick passed.");

  for (int repeat = 0; repeat < 50; repeat++) {
    Fenwick<long long> rurq(N);
    for (int i = 0; i < N; i++) a[i] = 0;
  
    for (int t = 0; t < 500; t++) {
      int idx_a = rand() % N;
      int idx_b = idx_a + (rand() % (N + 1 - idx_a));
      long long v = (rand() % 98765) * (rand() % 2 ? 1 : -1);
      for (int i = idx_a; i < idx_b; i++) a[i] += v;
      rurq.update(idx_a, idx_b, v);
    }
    for (int i = 0; i < N; i++) {
      for (int j = i; j <= N; j++) {
        if (brute_force_sum(a, i, j) != rurq.sum(i, j)) {
          fprintf(stderr, "Fenwick.sum(%d, %d) = %lld, answer is %lld. failed!\n", i, j, rurq.sum(i, j), brute_force_sum(a, i, j));
          for (int k = i; k < j; k++) {
            fprintf(stderr, "  a[%d]=%lld\n", k, a[k]);
          }
          abort();
        }
      }
    }
  }
  puts("* Fenwick passed.");
 }