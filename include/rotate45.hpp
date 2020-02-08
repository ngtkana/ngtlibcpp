template < typename Value >
auto rotate45(std::vector< std::vector< Value > > const& grid, Value def) {
    int h = grid.size();
    int w = grid.front().size();
    auto even = std::vector< std::vector < Value > >((h + w) / 2, std::vector< Value >((h + w) / 2, def));
    auto odd    = std::vector< std::vector < Value > >((h + w) / 2, std::vector< Value >((h + w) / 2, def));
    for (auto i = 0; i < h; i++) {
        for(auto j = 0; j < w; j++) {
            ((i + j) % 2 == 0 ? even : odd)
                .at((i + j) / 2)
                .at((h - 1 - i + j) / 2)
                = grid.at(i).at(j);
        }
    }
    return std::make_pair(even, odd);
}
