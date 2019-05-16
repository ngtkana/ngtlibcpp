class gauss_jordan {
  const int h, w;
  int rk;
  vector<int> stk;
  vector<int> p;
  vector<int> a;
  public:
    gauss_jordan (
        const vector<int> input_matrix,
        const int bit_max
      ) :
      h(bit_max), w(input_matrix.size()), rk(0),
      stk([&](){
          vector<int> ret(h);
          for (int i = 0; i < h; i++) ret[i] = i;
          return ret;
        }()),
      p([&](){
          vector<int> ret(h); 
          for (int i = 0, val = 1; i < h; i++, val <<= 1) ret[i] = val;
          return ret;
        }()),
      a(input_matrix)
      {
        for (int j = 0; j < w; j++) {
          for (auto it = stk.begin(); it != stk.end(); it++) {
            int pvt = *it;
            if ((a[j] >> pvt) & 1) {
              stk.erase(it); rk++;
              int spr = a[j] ^ (1 << pvt);
              for (int i = 0; i < h; i++) if ((p[i] >> pvt) & 1) p[i] ^= spr;
              for (int k = j; k < w; k++) if ((a[k] >> pvt) & 1) a[k] ^= spr;
              break;
            }
          }
          if (stk.empty()) break;
        }
      }
    inline int translate (int y) const {
      int z = 0;
      for (int i = 0; i < h; i++) if ((y >> i) & 1) {
        z ^= p[i];
      }
      return z;
    }
    int rank () const {return rk;}
    auto result () const {return a;}
    bool solvable (int y) const {
      if (y >> h) return false;
      int acm = accumulate(a.begin(), a.end(), 0, [](int x, int y){return x | y;});
      int z = translate(y);
      return !(~acm & z);
    }
};