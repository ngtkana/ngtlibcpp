class gauss_jordan {
  const int h, w;
  int rk;
  std::vector<bool> ckd;
  std::vector<int> p, a;
  void init () {
    for (int j = 0; j < w; j++) {
      for (int pvt = 0; pvt < h; pvt++) {
        if (ckd[pvt]) continue;
        if (a[j] >> pvt & 1) {
          ckd[pvt] = true; rk++;
          int comb = a[j] ^ 1 << pvt;
          for (int i = 0; i < h; i++) if (p[i] >> pvt & 1) p[i] ^= comb;
          for (int k = j; k < w; k++) if (a[k] >> pvt & 1) a[k] ^= comb;
          break;
        }
      }
    }
  }
  inline int transform (int y) const {
    int z = 0;
    for (int i = 0; i < h; i++) {
      if (y >> i & 1) z |= p[i];
    }
    return z;
  }
  public:
    gauss_jordan (
        std::vector<int> a,
        int h
      ) :
      h(h), w(a.size()), rk(0),
      ckd(h, false),
      p([&]{
        std::vector<int> p(h); 
        for (int i = 0, x = 1; i < h; i++, x *= 2) p[i] = x;
        return p;
      }()),
      a(a)
      {
        init();
      }
    inline int rank () const {return rk;}
    inline int kernel () const {return w - rk;}
    inline int image () const {return h - rk;}
    inline bool solvable (int y) const {
      assert (!(y >> h));
      int acm = accumulate(a.begin(), a.end(), 0, [](int x, int y){return x | y;});
      int z = transform(y);
      return !(~acm & z);
    }
};