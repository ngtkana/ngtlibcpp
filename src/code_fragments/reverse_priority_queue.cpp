priority_queue<
  ${1:std::pair<int, int>},
  std::vector<$1>,
  greater<$1>
> ${2:que};
$2.emplace($0);