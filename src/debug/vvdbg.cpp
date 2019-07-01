{ // debug
  int h = ${1:name}.size(); int w = 0;
  int name_length = ${2:3}; int output_length = ${3:4};
  for (int i = 0; i < h; i++) if (w < (int)$1[i].size()) w = $1[i].size();
  std::cout << std::string(name_length, '-') << "--";
  for (int j = 0; j < w; j++) std::cout << std::setw(${3:output length}) << "----";
  std::cout << std::endl;
  std::cout << std::setw(name_length) << right << "$1" << "| ";
  for (int j = 0; j < w; j++) std::cout << std::setw(output_length) << right <<  j;
  std::cout << std::endl;
  std::cout << std::string(name_length, '-') << "+-";
  for (int j = 0; j < w; j++) std::cout << std::string(output_length, '-');
  std::cout << std::endl;
  for (int i = 0; i < h; i++) {
    std::cout << std::setw(name_length) << right << i << "| ";
    for (auto const& e : $1[i]) std::cout << std::setw(output_length) << right << (e == ${4:0} ? "0" : to_string(e));
    std::cout << std::endl;
  }
  std::cout << std::string(name_length, '-') << "--";
  for (int j = 0; j < w; j++) std::cout << std::string(output_length, '-');
  std::cout << std::endl;
} //