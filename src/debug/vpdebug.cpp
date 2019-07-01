{ // debug
  std::cout << "${1:name}: ";
  for (auto ${2:it} = $1.begin(); $2 != $1.end(); $2++) {
    std::cout << "(";
    std::cout << $2->first;
    std::cout << ", ";
    std::cout << $2->second;
    std::cout << ")" << (next($2) == $1.end() ? "\n" : ", ");
  }
  std::cout << std::endl;
} //
