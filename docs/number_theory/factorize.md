# factorize
```cpp
auto factorize (
  int x
) -> map<int, int>
{
  map<int, int> mp;
  for (int p = 2; p * p <= x; p++) {
    while (!(x % p)) {
      mp[p]++;
      x /= p;
    }
  }
  if (x != 1) mp[x] = 1;
  return map;
}
```
