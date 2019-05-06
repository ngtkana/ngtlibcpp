# sieve_of_eratosthenes
```cpp
struct sieve_of_eratosthenes {
  vector<bool> is_prime;
  vector<int> prime_numbers;
  vector<vector<int>> prime_divisors;
  vector<vector<int>> divisors;
  sieve_of_eratosthenes(int n)
    : is_prime(vector<bool>(n))
    , prime_numbers(vector<int>(0))
    , prime_divisors(vector<vector<int>>(n))
    , divisors(vector<vector<int>>(n))
  {
    for (int i = 1; i < n; i++) {
      if (is_prime[i] = divisors[i].size() == 1) prime_numbers.push_back(i);
      for (int j = i; j < n; j += i) {
        divisors[j].push_back(i);
        if (is_prime[i]) prime_divisors[j].push_back(i);
      }
    }
  }
  auto factorize (
    int x 
  ) -> map<int, int> 
  {
    map<int, int> mp;
    for (int p : prime_numbers) {
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
```
