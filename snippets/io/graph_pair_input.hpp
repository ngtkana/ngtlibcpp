std::vector<std::vector<std::pair<${3:long long}, int>>> grh(${1:n});
for (int i = 0; i < ${2:m}; i++) {
  int s, t; $3 d;
  std::cin >> s >> t >> d;
  grh[${4:--}s].emplace_back(d, $4t);
  grh[t].emplace_back(d, s);
}