# gcd
```cpp
template<typename T>
T gcd (T a, T b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  if (a < b) swap(a, b);
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}
```
