# map_debug
```cpp
{ // debug
  for (auto ${2:it} = ${1:mp}.begin(); $2 != $1.end(); $2++) {
    cout << "mp[";
    cout << $0$2->first;
    cout << "] = ";
    cout << $2->second;
    cout << "" << (next($2) == $1.end() ? "\n" : ", ");
  }
} //
```
