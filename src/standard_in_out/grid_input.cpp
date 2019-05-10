int ${1:h}, ${2:w}, ${3:si}, ${4:sj}, ${5:gi}, ${6:gj};
cin >> $1 >> $2 >> $3 >> $4 >> $5 >> $6;
$3--, $4--, $5--, $6--;
vector<vector<int>> ${7:grd}($1, vector<int>($2));
for (int i = 0; i < $1; i++) {
  for (int j = 0; j < $2; j++) {
    char c;
    cin >> c;
    $7[i][j] = c == '#';
  }
}