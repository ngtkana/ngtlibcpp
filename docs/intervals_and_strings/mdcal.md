# mdcal
```cpp
vector<${1:int}> lis;
for (auto crr : ${2:‚¨‚È‚Ü‚¦}) {
  auto lb = lower_bound(lis.begin(), lis.end(), crr);
  if (lb == lis.end()) lis.push_back(crr);
  else *lb = crr;
}
```
