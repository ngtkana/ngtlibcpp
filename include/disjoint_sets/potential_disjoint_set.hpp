class potential_disjoint_set {
  public:
  std::vector<int> rank, prt, ptl;
  potential_disjoint_set (int size) {
    rank.resize(size);
    prt.resize(size);
    ptl.resize(size);
    for (int i = 0; i < size; i++) {
      prt[i] = i;
      rank[i] = 0;
      ptl[i] = 0;
    }
  }
  int find (int x) {
    if (x == prt[x]){
      return x;
    } else {
      int r = find(prt[x]);
      ptl[x] += ptl[prt[x]];
      return prt[x] = r;
    }
  }
  bool is_equiv (int x, int y) {
    return find(x) == find(y);
  }
  bool unite (int x, int y, int w) {
    if (find(x) == find(y)) {
      return false;
    }
    w += ptl[x];
    w -= ptl[y];
    x = find(x);
    y = find(y);
    if (rank[x] < rank[y]) {
      std::swap(x, y);
      w *= -1;
    }
    prt[y] = x;
    ptl[y] = w;
    if (rank[x] == rank[y]) {
      rank[x]++;
    }
    return true;
  }
  int diff (int x, int y) {
    find(x);
    find(y);
    return ptl[y] - ptl[x];
  }
};
