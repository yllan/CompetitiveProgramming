/* [2, 2, 2, 2, 3, 11, 11, 11] -> [(2, 4), (5, 1), (11, 3)] */
template<typename T>
vector<pair<T, int>> rle_compress(vector<T> list) {
  bool first = true;
  T last;
  int count = 0;
  vector<pair<T, int>> result;
  
  for (auto e : list) {
    if (first) {
      last = e;
      count = 1;
      first = false;
    } else if (e == last) {
      count++;
    } else {
      result.push_back(make_pair(last, count));
      last = e;
      count = 1;
    }
  }
  if (!first) result.push_back(make_pair(last, count));
  return result;
}

/* [(A, 3), (B, 4)] -> [A, A, A, B, B, B, B] */
template<typename T> 
vector<T> rle_expand(vector<pair<T, int>> z) {
  vector<T> result;
  for (auto p : z) {
    for (int i = 0; i < p.second; i++) 
      result.push_back(p.first);
  }
  return result;
}
