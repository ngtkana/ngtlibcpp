priority_queue<
  ${1:pair<int, int>},
  vector<$1>,
  greater<$1>
> ${2:que};
$2.emplace($0);