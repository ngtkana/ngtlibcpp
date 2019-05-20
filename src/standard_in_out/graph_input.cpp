vector<vector<int>> grh(${1:n});
for (int i = 0; i < ${2:n - 1}; i++) {
  int s, t;
  cin >> s >> t;
  grh[${3:--}s].push_back($3t);
  grh[t].push_back(s);
}