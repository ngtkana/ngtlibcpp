{ // debug
  int h = ${1:name}.size(); int w = 0;
  int name_length = ${2:3}; int output_length = ${3:4};
  for (int i = 0; i < h; i++) if (w < (int)$1[i].size()) w = $1[i].size();
  cout << string(name_length, '-') << "--";
  for (int j = 0; j < w; j++) cout << setw(${3:output length}) << "----";
  cout << endl;
  cout << setw(name_length) << right << "$1" << "| ";
  for (int j = 0; j < w; j++) cout << setw(output_length) << right <<  j;
  cout << endl;
  cout << string(name_length, '-') << "+-";
  for (int j = 0; j < w; j++) cout << string(output_length, '-');
  cout << endl;
  for (int i = 0; i < h; i++) {
    cout << setw(name_length) << right << i << "| ";
    for (auto const& e : $1[i]) cout << setw(output_length) << right << (e == ${4:0} ? "0" : to_string(e));
    cout << endl;
  }
  cout << string(name_length, '-') << "--";
  for (int j = 0; j < w; j++) cout << string(output_length, '-');
  cout << endl;
} //