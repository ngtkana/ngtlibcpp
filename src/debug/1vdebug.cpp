{ // debug
  int n = 0;
  if (n < (int)${1:name}.size()) n = $1.size();
  std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
  std::cout << std::setw(4) << ""; for (int i = 0; i < n; i++) std::cout << std::setw(4) << i; std::cout << std::endl;
  std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
  std::cout << std::setw(4) << "$1"; for (auto const& e : $1) std::cout << std::setw(4) << e; std::cout << std::endl;
  std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
} //
