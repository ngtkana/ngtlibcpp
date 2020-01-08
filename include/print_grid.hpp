template < typename Grid >
auto print_grid(Grid const& grid) {
  int h = grid.size();
  int w = grid.front().size();
  for (auto i = 0; i < h; i++) {
    for(auto j = 0; j < w; j++) {
      std::cout << (grid.at(i).at(j) ? '#' : '.');
    }
    std::cout << std::endl;
  }
}
