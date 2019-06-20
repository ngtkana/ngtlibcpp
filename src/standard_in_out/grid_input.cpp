int ${1:h}, ${2:w};
cin >> $1 >> $2;
vector<vector<int>> grd($1, vector<int>($2));
for (int i = 0; i < $1; i++) {
  for (int j = 0; j < $2; j++) {
    char c;
    cin >> c;
    grd[i][j] = c == '#';
  }
}