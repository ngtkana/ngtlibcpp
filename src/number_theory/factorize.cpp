class factorize {
  int x;
  map<int, int> mp;
  vector<int> pdv;
  vector<int> pdv_m;

  public:
    factorize(
        const int x
      ) :
      x(x), mp(), pdv()
      {
        for (int p = 2; p * p <= x; p++) {
          while (!(x % p)) {
            mp[p]++;
            pdv.push_back(p);
            x /= p;
          }
        }
        if (x != 1) mp[x] = 1;
        pdv.push_back(x);
        pdv_m = pdv.resize(unique(pdv.begin(), pdv.end()) - pdv.begin());
      }
    
    const auto& factorize () const {return pdv;}
    const auto& prime_divisors () const {return pdv_m;}
    const auto& multiplicities () const {return mp;}
}