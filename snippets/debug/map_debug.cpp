{ // debug
  for (auto ${2:it} = ${1:mp}.begin(); $2 != $1.end(); $2++) {
    std::cout << "mp[";
    std::cout << $0$2->first;
    std::cout << "] = ";
    std::cout << $2->second;
    std::cout << "" << (next($2) == $1.end() ? "\n" : ", ");
  }
} //
