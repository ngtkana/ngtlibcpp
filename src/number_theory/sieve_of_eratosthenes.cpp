class sieve_of_eratosthenes {
  const int n;
  std::vector<bool> is_prm;
  std::vector<int> prm;
  std::vector<std::vector<int>> pdv;
  std::vector<std::vector<int>> div;

  public:
    sieve_of_eratosthenes(
        int n
      ):
        n(n),
        is_prm(std::vector<bool>(n)),
        prm(std::vector<int>(0)), 
        pdv(std::vector<std::vector<int>>(n)),
        div(std::vector<std::vector<int>>(n))
      {
        for (int i = 1; i < n; i++) {
          if (is_prm[i] = div[i].size() == 1) prm.push_back(i);
          for (int j = i; j < n; j += i) {
            div[j].push_back(i);
            if (is_prm[i]) pdv[j].push_back(i);
          }
        }
      }
    
    bool is_prime (int x) const {assert(x < n); return is_prime[x];}
    auto prime_divisors (int x) const {assert(x < n); return pdv[x];}
    auto divisors (int x) const {assert(x < n); return div[x];}

    auto factorize (
      int x 
    ) -> map<int, int> 
    {
      map<int, int> mp;
      for (int p : prm) {
        while (!(x % p)) {
          mp[p]++;
          x /= p;
        }
        if (x == 1 || p * p > x) break;
      }
      if (x != 1) mp[x] = 1;
      return mp;
    }
};
