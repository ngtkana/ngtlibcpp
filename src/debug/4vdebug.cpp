{ // debug
  int n = 0;
  if (n < (int)${1:name}.size()) n = $1.size();
  if (n < (int)${2:name}.size()) n = $2.size();
  if (n < (int)${3:name}.size()) n = $3.size();
  std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
  std::cout << std::setw(4) << ""; for (int i = 0; i < n; i++) std::cout << std::setw(4) << i; std::cout << std::endl;
  std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
  std::cout << std::setw(4) << "$1"; for (auto const& e : $1) std::cout << std::setw(4) << e; std::cout << std::endl;
  std::cout << std::setw(4) << "$2"; for (auto const& e : $2) std::cout << std::setw(4) << e; std::cout << std::endl;
  std::cout << std::setw(4) << "$3"; for (auto const& e : $3) std::cout << std::setw(4) << e; std::cout << std::endl;
  std::cout << std::setw(4) << "$4"; for (auto const& e : $4) std::cout << std::setw(4) << e; std::cout << std::endl;
  std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
} //
