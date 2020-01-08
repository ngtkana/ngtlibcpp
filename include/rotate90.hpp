template < class Value >
auto rotate90(std::vector< std::vector< Value > > const& a) {
  std::size_t h = a.size(), w = a.front().size();
  std::vector< std::vector< Value > > b(w, std::vector< Value >(h));
  for (std::size_t i = 0; i < h; i++) {
    for (std::size_t j = 0; j < w; j++) {
      b.at(w-1-j).at(i) = a.at(i).at(j);
    }
  }
  return b;
}
