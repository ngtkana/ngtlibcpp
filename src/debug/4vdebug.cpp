{ // debug
  int n = 0;
  if (n < (int)${1:name}.size()) n = $1.size();
  if (n < (int)${2:name}.size()) n = $2.size();
  if (n < (int)${3:name}.size()) n = $3.size();
  cout << setw(4) << "----"; for (int i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
  cout << setw(4) << ""; for (int i = 0; i < n; i++) cout << setw(4) << i; cout << endl;
  cout << setw(4) << "----"; for (int i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
  cout << setw(4) << "$1"; for (int i = 0; i < n; i++) cout << setw(4) << $1[i]; cout << endl;
  cout << setw(4) << "$2"; for (int i = 0; i < n; i++) cout << setw(4) << $2[i]; cout << endl;
  cout << setw(4) << "$3"; for (int i = 0; i < n; i++) cout << setw(4) << $3[i]; cout << endl;
  cout << setw(4) << "$4"; for (int i = 0; i < n; i++) cout << setw(4) << $4[i]; cout << endl;
  cout << setw(4) << "----"; for (int i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
} //
