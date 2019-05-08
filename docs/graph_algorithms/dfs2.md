# dfs2
[prev](..\index.md)
```cpp
void ${1:dfs} (
  int crr
, vector<int>& ckd
, vector<vector<int>>& grh
) {
  ckd[crr] = true;
  for (int nxt : grh[crr]) if (!ckd[nxt]) {
    $1(nxt, ckd, grh);
  }
}
```
