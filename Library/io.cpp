#include<iostream>
#include<vector>
#include<set>
#include<map>

using namespace std;

// Print Tuple
template <typename T, typename U>
inline ostream& operator<< (ostream& os, const pair<T, U>& v) { os << "(" << v.first << ", " << v.second << ")"; return os; }
template <typename T, typename U, typename V>
inline ostream& operator<< (ostream& os, const tuple<T, U, V>& t) { os << "("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")"; return os; }
// Print Vector
template <typename T>
inline ostream& operator<< (ostream& os, const vector<T>& v) {
    bool f = true; os << "["; for (const auto &e : v) { if (!f) os << ", "; f = false; os << e; }; os << "]";
    return os;
}
// Print Set
template <typename T>
inline ostream& operator<< (ostream& os, const set<T>& s) {
    bool f = true; os << "{"; for (const auto &e : s) { if (!f) os << ", "; f = false; os << e; }; os << "}";
    return os;
}
// Print Map
template <typename T, typename U>
inline ostream& operator<< (ostream& os, const map<T, U>& m) {
    bool f = true; os << "{"; for (const auto &e : m) { if (!f) os << ", "; f = false; os << e.first << ": " << e.second; }; os << "}";
    return os;
}


int main() {
    vector<pair<int, int>> xs = {{1, 0}, {2, 1}, {3, 3}};
    map<int, int> m;
    m[1] = 10;
    m[3] = 4;
    cerr << xs << endl;
    cerr << m << endl;
}