{ // debug
  cout << "--------------------------------------" << endl;
  cout << setw(${5:5}) << left << "$1";
  for (int ${2:i} = 0; $2 < (int)${1:おなまえ}.size(); $2++) {
    if ($2 != 0) cout << setw($5) << " ";
    cout << "$2 = " << setw(2) << right << $2 << ": ";
    for (int ${3:j} = 0; $3 < (int)$1[$2].size(); $3++) {
      cout << setw(${4:4}) << right << $1[$2][$3];
      if ($3 != (int)$1[$2].size() - 1) cout << " ";
    }
    cout << endl;
  }
  cout << "--------------------------------------" << endl;
} //
