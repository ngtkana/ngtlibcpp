{ // debug
  int n = 0;
  if (n < (int)${1:name}.size()) n = $1.size();
  cout << setw(4) << "----"; for (int i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
  cout << setw(4) << ""; for (int i = 0; i < n; i++) cout << setw(4) << i; cout << endl;
  cout << setw(4) << "----"; for (int i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
  cout << setw(4) << "$1"; for (auto const& e : $1) cout << setw(4) << e; cout << endl;
  cout << setw(4) << "----"; for (int i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
} //
