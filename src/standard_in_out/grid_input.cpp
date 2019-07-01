int ${1:h}, ${2:w};
std::cin >> $1 >> $2;
std::vector<std::vector<int>> grd($1, std::vector<int>($2));
for (int i = 0; i < $1; i++) {
  for (int j = 0; j < $2; j++) {
    char c;
    std::cin >> c;
    grd[i][j] = c == '#';
  }
}