# shakutori
```cpp
int l(0), r(0);
for (; l < ${1:n}; l++) {
  while (r < n && ${2:/*[l, r + 1)‚ª‘Ã“–*/}) {
    r++;
    ${3:/*[l, r + 1)‚ð–K–â*/};
  }
}
```
