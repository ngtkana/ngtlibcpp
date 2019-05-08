# vpdebug
[prev](..\index.md)
```cpp
{ // debug
  cout << "${1:おなまえ}: ";
  for (auto $2 = $1.begin(); $2 != $1.end(); $2++) {
    cout << "(";
    cout << $2->first;
    cout << ", ";
    cout << $2->second;
    cout << ")" << (next($2) == $1.end() ? "\n" : ", ");
  }
  cout << endl;
} //
```
